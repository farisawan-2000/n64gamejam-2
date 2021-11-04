import sys, os

inVerts =False

inTris = False

vtxOffset = -32 # this assumption cannot go wrong
print("#include <ultra64.h>")
print("#include <gbi.h>")
print("#include <PR/gt.h>")
print("#include \"n64_defs.h\"");
print("#include \"gtHelpers.h\"")
with open(sys.argv[1]) as f:
    for line in f:
        if "Vtx" in line:
            inVerts = True

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
                vtxOffset += int(tokens[4])
            if tokens[0] == "gsSP1Triangle":
                print("    {%d, %d, %d, %d}," % (
                    int(tokens[1]) + vtxOffset,
                    int(tokens[2]) + vtxOffset,
                    int(tokens[3]) + vtxOffset,
                    int(tokens[4]) + vtxOffset
                ))
            if tokens[0] == "gsSP2Triangles":
                print("    {%d, %d, %d, %d}, {%d, %d, %d, %d}," % (
                    int(tokens[1]) + vtxOffset,
                    int(tokens[2]) + vtxOffset,
                    int(tokens[3]) + vtxOffset,
                    int(tokens[4]) + vtxOffset,
                    int(tokens[5]) + vtxOffset,
                    int(tokens[6]) + vtxOffset,
                    int(tokens[7]) + vtxOffset,
                    int(tokens[8]) + vtxOffset
                ))

        if "Gfx" in line:
            inTris = True
            print("gtTriN %s_tris[] __attribute__((aligned(8))) = {" % sys.argv[2])

        if line[:-1] == "};" and inTris:
            inTris = False
            print(line[:-1])
            break
