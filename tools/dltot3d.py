import sys, os

inVerts =False

inTris = False

vtxOffset = 0
shouldAddNow = False

countTris = 0
countVtx = 0

# renderstate is 0x2202
# (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER)
gtStateTemplate = """\
gtState %s_State = {
    %s, // renderState 0
    0x0, // textureState 4
    %d, // vtxCount  8
    0, // vtxV0 9
    %d, // triCount a
    0x0, // some_flag b
    NULL, // c
    gsDPSetOtherMode(
        G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
        G_AC_NONE | G_ZS_PIXEL
    ), // 10
    {
    // integer portion:
        0x00010000, 0x00000000,
        0x00000001, 0x00000000,
        0x00000000, 0x00010000,
        0x00000000, 0x00000001,
    // fractional portion:
        0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000000, 0x00000000,
    }
};

"""

gtStateLTemplate = """\
gtStateL %s = {
    %s, // renderState 0
    0x0, // textureState 4
    %d, // vtxCount  8
    0, // vtxV0 9
    %d, // triCount a
    GT_FLAG_NOMTX, // some_flag b
    NULL, // c
    gsDPNoOp(), // 10
};

"""

object2639_Template = """\
Object2639 %s_Obj = {
    {0, 0, 0},
    {0, 0, 0},
    {1.0, 1.0, 1.0},

    %d, // gfxlist count
    &%s, // gfxlist name

    MATERIAL_TEXTURE,
    {G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32},
    NULL,

    NULL,
    NULL,
};
"""


vtxName = ""

flag_fuzzer = 0

listOfVtxLoads = []
numTriLoads = 0

stateList = []

needMoreTris = False
triLoadCount = -1

print("#include <ultra64.h>")
print("#include <gbi.h>")
print("#include <PR/gt.h>")
print("#include \"n64_defs.h\"")
print("#include \"gtHelpers.h\"")

print("extern Object2639 %s_Obj;" % sys.argv[2])
print("Object2639 *%s_objp = &%s_Obj;" % (sys.argv[2], sys.argv[2]))



with open(sys.argv[1]) as f:
    for line in f:
        if "Vtx" in line:
            inVerts = True
            countVtx = int(line.split("[")[1].split("]")[0])
            vtxName = line.split()[1].split("[")[0]

        if inVerts:
            print(line[:-1])

        if line[:-1] == "};" and inVerts:
            inVerts = False

        if inTris:
            tokens = line.replace("(", " ")\
                         .replace(")", " ")\
                         .replace(",", " ")\
                         .split()

            if tokens[0] == "gsSPVertex":
                vtxName = ''.join(tokens[1:4])
                # if triLoadCount >= 0:
                stateList.append([
                    int(tokens[4]),
                    0,
                ])
                if len(stateList) == 2:
                    stateList[0][1] = countTris
                if countTris != 0:
                    stateList[-1][1] = countTris
                countTris = 0

                if triLoadCount >= 0:
                    print("};")
                needMoreTris = True
                triLoadCount += 1
                listOfVtxLoads.append(vtxName)
            if tokens[0] == "gsSP1Triangle":
                if needMoreTris:
                    print("gtTriN %s_tris_%d[] __attribute__((aligned(8))) = {" % (sys.argv[2], triLoadCount))
                    needMoreTris = False
                countTris += 1
                print("    {%d, %d, %d, %d}," % (
                    int(tokens[1]) + vtxOffset,
                    int(tokens[2]) + vtxOffset,
                    int(tokens[3]) + vtxOffset,
                    int(tokens[4]) + vtxOffset
                ))
            if tokens[0] == "gsSP2Triangles":
                if needMoreTris:
                    print("gtTriN %s_tris_%d[] __attribute__((aligned(8))) = {" % (sys.argv[2], triLoadCount))
                    needMoreTris = False
                countTris += 2
                print("    {%d, %d, %d, 0}, {%d, %d, %d, 0}," % (
                    int(tokens[1]) + vtxOffset,
                    int(tokens[2]) + vtxOffset,
                    int(tokens[3]) + vtxOffset,

                    int(tokens[5]) + vtxOffset,
                    int(tokens[6]) + vtxOffset,
                    int(tokens[7]) + vtxOffset,
                ))
                flag_fuzzer += 2

        if "Gfx" in line:
            inTris = True
            numTriLoads+=1

        if line[:-1] == "};" and inTris:
            inTris = False
            print(line[:-1])
            break



stateList[-1][1] = countTris
for i, x in enumerate(stateList):
    if i == 0:
        print(gtStateTemplate % (
            sys.argv[2],
            "(GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER)",
            x[0],
            x[1],
        ))
    else:
        print(gtStateLTemplate % (
            "%s_StateL_%d" % (sys.argv[2], i - 1),
            "(GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER)",
            x[0],
            x[1],
        ))

gtGfxStart = "gtGfx %s_GfxList[] = {"

gtGfxTemplate = """\
    {
        NULL,
        (gtState *)%s,
        %s,
        %s,
    },"""

gtGfxEnd = "};"

print(gtGfxStart % sys.argv[2])
for i, x in enumerate(listOfVtxLoads):
    stateName = "&%s_StateL_%d" % (sys.argv[2], i - 1)
    if i == 0:
        stateName = "&%s_State" % sys.argv[2]
    print(gtGfxTemplate % (
        stateName,
        str(listOfVtxLoads[i]),
        "%s_tris_%d" % (sys.argv[2], i)
        )

    )

print(gtGfxEnd)

print(object2639_Template % (
    sys.argv[2],
    len(listOfVtxLoads) + 1,
    "%s_GfxList" % sys.argv[2]
))

