#include <ultra64.h>
#include "n64_defs.h"
#include "game/controller.h"

s32 butonChoice = 0;

extern u32 sMenuChoice;
f32 B1ScaleTarget = 0.05f;
void Title_Button1Loop(Object2639 *o) {
    if (butonChoice == 0) {
        B1ScaleTarget = 0.07f;
    } else {
        B1ScaleTarget = 0.05f;
    }

    VectorFullApproach(&o->scale, &B1ScaleTarget, 0.2f);

}


f32 B2ScaleTarget = 0.05f;
void Title_Button2Loop(Object2639 *o) {
    if (butonChoice == 1) {
        B2ScaleTarget = 0.07f;
    } else {
        B2ScaleTarget = 0.05f;
    }

    VectorFullApproach(&o->scale, &B2ScaleTarget, 0.2f);

}


void Title_Loop(Object2639 *o) {
    if (GameControllers[0].stickX < -14) {
        butonChoice --;
        if (butonChoice < 0) butonChoice = 0;
    }

    if (GameControllers[0].stickX > 14) {
        butonChoice++;
        if (butonChoice > 1) butonChoice = 1;
    }

    if (GameControllers[0].button & A_BUTTON) {
        sMenuChoice = butonChoice + 1;
    }
}

