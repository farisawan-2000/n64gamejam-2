# DEPRECATED bc fast64 better
import sys, os


vtxVisited = False
faceVisited = False

def FTOFIX16(x):
    return int(x * (1 << 5))

class Vtx():
    def __init__(self, v1, v2, v3):
        self.v1 = int(float(v1));
        self.v2 = int(float(v2));
        self.v3 = int(float(v3));
    def __str__(self):
        return "%d, %d, %d" % (self.v1, self.v2, self.v3)

class VtxNml(Vtx):
    pass

class VtxCoord():
    def __init__(self, s, t):
        self.s = float(s);
        self.t = float(t);
    def __str__(self):
        return "%d, %d" % (FTOFIX16(self.s), FTOFIX16(self.t))

class Triangle():
    def __init__(self, v1, v2, v3):
        self.v1 = v1
        self.v2 = v2
        self.v3 = v3

VtxList = []
VtxCoordList = []
VtxNmlList = []
TriList = []





with open(sys.argv[1]) as f:
    for line in f:
        print(line[:-1])
        tokens = line.split()
        if line[0:2] == "vt":
            VtxCoordList.append(VtxCoord(tokens[1], tokens[2]))
        elif line[0:2] == "vn":
            VtxNmlList.append(VtxNml(tokens[1], tokens[2], tokens[3]))
        elif line[0] == "v":
            VtxList.append(Vtx(tokens[1], tokens[2], tokens[3]))
        elif line[0] == "f":
            TriList.append(Triangle(
                tokens[0].split("/"),
                tokens[1].split("/"),
                tokens[2].split("/")
                ))



print("Vtx %s_verts = {"% sys.argv[2])
for i, x in enumerate(VtxList):
    print("    {%s, 0, %s, %s, 0xFF}," % (
        x.v1,
        x.v2,
        x.v3
        ))
print("};")
print("gtTriN %s_tris __attribute__((aligned(8))) = {" % sys.argv[1])

