#include <ultra64.h>
#include <PR/gt.h>


void t3d_assignMat(gtState *p, Gfx *mat) {
    p->rdpCmds = mat;
}

void t3d_parseOthermode(gtState *p, Gfx *dl) {
    // turn a dl of othermode commands into one othermode
    Gfx othermode;

    while (dl->words.w0 != 0) {
        
        
        dl++;
    }

    p->rdpOthermode = othermode;
}

