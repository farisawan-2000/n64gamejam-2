import sys, os

inVerts =False

inTris = False

vtxOffset = 0
shouldAddNow = False

countTris = 0
countVtx = 0

# renderstate is 0x2202
gtStateTemplate = """\
gtState %s_State = {
    %s, // renderState 0
    0x0, // textureState 4
    %d, // vtxCount  8
    0, // vtxV0 9
    %d, // triCount a
    0x0, // some_flag b
    NULL, // c
    gsDPClearOtherMode(), // 10
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

gtGfx %s_Gfx = {
    NULL,
    &%s_State,
    %s,
    %s,
};

"""
vtxName = ""

flag_fuzzer = 0

listOfVtxLoads = []
numTriLoads = 0

print("#include <ultra64.h>")
print("#include <gbi.h>")
print("#include <PR/gt.h>")
print("#include \"n64_defs.h\"");
print("#include \"gtHelpers.h\"")
with open(sys.argv[1]) as f:
    for line in f:
        if "Vtx" in line:
            inVerts = True
            countVtx = int(line.split("[")[1].split("]")[0])
            vtxName = line.split()[1].split("[")[0]
            # vtxOffset = -countVtx

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
                if shouldAddNow:
                    vtxOffset += int(tokens[4])
                else:
                    shouldAddNow = True
            if tokens[0] == "gsSP1Triangle":
                countTris += 1
                print("    {%d, %d, %d, %d}," % (
                    int(tokens[1]) + vtxOffset,
                    int(tokens[2]) + vtxOffset,
                    int(tokens[3]) + vtxOffset,
                    int(tokens[4]) + vtxOffset
                ))
            if tokens[0] == "gsSP2Triangles":
                countTris += 2
                print("    {%d, %d, %d, 0}, {%d, %d, %d, 0}," % (
                    int(tokens[1]) + vtxOffset,
                    int(tokens[2]) + vtxOffset,
                    int(tokens[3]) + vtxOffset,
                    # int(tokens[4]) + vtxOffset,
                    int(tokens[5]) + vtxOffset,
                    int(tokens[6]) + vtxOffset,
                    int(tokens[7]) + vtxOffset,
                    # int(tokens[8]) + vtxOffset
                ))
                flag_fuzzer += 2

        if "Gfx" in line:
            inTris = True
            print("gtTriN %s_tris_%d[] __attribute__((aligned(8))) = {" % (sys.argv[2], numTriLoads))
            numTriLoads+=1

        if line[:-1] == "};" and inTris:
            inTris = False
            print(line[:-1])
            break

print(gtStateTemplate % (
    sys.argv[2],
    countVtx,
    countTris,
    sys.argv[2],
    sys.argv[2],
    vtxName,
    "%s_tris" % sys.argv[2]
    ))


gtGfxStart = "gtGfx %s_GfxList[] = {"

gtGfxTemplate = """\
    {
        NULL,
        NULL,
        %s,
        %s,
    },"""

gtGfxEnd = "};"

print(gtGfxStart % sys.argv[2])
for i, x in enumerate(listOfVtxLoads):
    print(gtGfxTemplate % (
        listOfVtxLoads[i],
        "%s_tris_%d" % (sys.argv[2], i)
        )

    )

print(gtGfxEnd)

