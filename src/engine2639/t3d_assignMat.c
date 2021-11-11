// The material allocator; use this for assigning both static and dynamic materials

#include <ultra64.h>
#include <PR/gt.h>

// 64kb buffer so that we can segment
// Gfx sT3DMatBuffer[8192];

void t3d_assignMat(gtState *p, Gfx *mat) {
    p->sp.rdpCmds = mat;
}

void t3d_parseOthermode(gtState *p, Gfx *dl) {
    // turn a dl of othermode commands into one othermode
    Gfx othermode;

    while (dl->words.w0 != 0) {
        
        
        dl++;
    }

    p->sp.rdpOthermode = othermode;
}

