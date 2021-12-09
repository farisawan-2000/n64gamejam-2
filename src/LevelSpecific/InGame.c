#include <ultra64.h>
#include "n64_defs.h"
#include "game/controller.h"

#define SECOND_COUNT 10

f32 B1PosTarget = 100;
void InGame_ButtonLLoop(Object2639 *o) {
    if (GameControllers[0].held & L_CBUTTONS) {
        B1PosTarget = 80;
    } else {
        B1PosTarget = 100;
    }

    FloatApproach(&o->move.y, &B1PosTarget, 0.2f);

}


f32 B2PosTarget = 100;
void InGame_ButtonRLoop(Object2639 *o) {
    if (GameControllers[0].held & R_CBUTTONS) {
        B2PosTarget = 80;
    } else {
        B2PosTarget = 100;
    }

    FloatApproach(&o->move.y, &B2PosTarget, 0.2f);

}


f32 B2AngleTarget = 0;
void InGame_LeverLoop(Object2639 *o) {
    if (GameControllers[0].held & Z_TRIG) {
        B2AngleTarget = -60;
    } else {
        B2AngleTarget = 0;
    }


    FloatApproach(&o->rotate.roll, &B2AngleTarget, 0.2f);
}

enum Turn {
    TURN_P1 = 0,
    TURN_P2
};
u32 gTurn = TURN_P1;

enum InGameStates {
    IG_STATE_RESET=0,
    IG_STATE_P1_DRAW,
    IG_STATE_P1_P2_TRANSITION,
    IG_STATE_P2_DRAW,

    IG_STATE_RESULTS,

};
static u32 sGameState = IG_STATE_RESET;
static u32 sGameNextState = IG_STATE_RESET;
static u32 sStateTimer = 0;


u32 ReloadTitle = 0;
u32 elapsedSamples = 0;
static void NextStateProc(void) {
    switch (sGameState) {
        case IG_STATE_RESET:
            gTurn = TURN_P1;
            elapsedSamples = 0;
            sGameNextState = IG_STATE_P1_DRAW;
            break;
        case IG_STATE_P1_DRAW:
            if (sStateTimer > (60 * SECOND_COUNT)) {
                sGameNextState = IG_STATE_P1_P2_TRANSITION;
            }
            break;
        case IG_STATE_P1_P2_TRANSITION:
            gTurn = TURN_P2;
            elapsedSamples = 0;
            sGameNextState = IG_STATE_P2_DRAW;
            break;
        case IG_STATE_P2_DRAW:
            if (sStateTimer > (60 * SECOND_COUNT * 2)) {
                sGameNextState = IG_STATE_RESULTS;
            }
            break;
        case IG_STATE_RESULTS:
            elapsedSamples = 0;
            if (GameControllers[0].button & START_BUTTON) {
                sGameNextState = IG_STATE_RESET;
            }
            if (GameControllers[0].button & B_BUTTON) {
                ReloadTitle = 1;
            }
            break;
    }
}

void InGame_Loop(Object2639 *o) {
    if (sGameNextState != sGameState) {
        sStateTimer = 0;
    }
    sGameState = sGameNextState;

    NextStateProc();

    sStateTimer++;
}

#define LEFT_SIGN   200
#define DELTA       225
#define RIGHT_SIGN -200


f32 P1PosT = RIGHT_SIGN;
void InGame_SignP1Loop(Object2639 *o) {
    if (gTurn) {
        P1PosT = RIGHT_SIGN - DELTA;
    } else {
        P1PosT = RIGHT_SIGN;
    }

    FloatApproach(&o->move.x, &P1PosT, 0.2f);
}

f32 P2PosT = RIGHT_SIGN;
void InGame_SignP2_1Loop(Object2639 *o) {
    if (gTurn) {
        P2PosT = RIGHT_SIGN - DELTA;
    } else {
        P2PosT = RIGHT_SIGN;
    }

    FloatApproach(&o->move.x, &P2PosT, 0.2f);
}

f32 P2PosT2 = LEFT_SIGN;
void InGame_SignP2_2Loop(Object2639 *o) {
    if (gTurn==0) {
        P2PosT2 = LEFT_SIGN + DELTA;
    } else {
        P2PosT2 = LEFT_SIGN;
    }

    FloatApproach(&o->move.x, &P2PosT2, 0.2f);
}

f32 PassPosT = LEFT_SIGN;
void InGame_SignPassLoop(Object2639 *o) {
    if (gTurn==0) {
        PassPosT = LEFT_SIGN + DELTA;
    } else {
        PassPosT = LEFT_SIGN;
    }

    FloatApproach(&o->move.x, &PassPosT, 0.2f);
}

f32 PassCanvasT = 100;
void InGame_CanvasLoop(Object2639 *o) {
    if (gTurn) {
        PassCanvasT = 100 - DELTA;
    } else {
        PassCanvasT = 100;
    }

    FloatApproach(&o->move.x, &PassCanvasT, 0.2f);
}


#define SAMPLES_PER_SEX 4

u16 DN_BufferX[SECOND_COUNT * SAMPLES_PER_SEX];
u16 DN_BufferY[SECOND_COUNT * SAMPLES_PER_SEX];

#include <PR/gt.h>

gtState PaintStateArray[SECOND_COUNT * SAMPLES_PER_SEX];
Object2639 PaintObjectArray[SECOND_COUNT * SAMPLES_PER_SEX];
gtGfx PaintGFXArray[SECOND_COUNT * SAMPLES_PER_SEX];
extern Object2639 Paint_Obj;

extern gtState Paint_State;
extern gtGfx Paint_GfxList;

void SetElapsed(void) {
    elapsedSamples = sStateTimer / (60 / SAMPLES_PER_SEX);
}

void SamplePaintSplotch(Object2639 *o) {
    if (gTurn == TURN_P1) {
        DN_BufferX[elapsedSamples] = o->move.x;
        DN_BufferY[elapsedSamples] = o->move.y;
    }

    PaintStateArray[elapsedSamples] = Paint_State;

    bzero(&PaintGFXArray[elapsedSamples], sizeof(Object2639));
    PaintGFXArray[elapsedSamples] = Paint_GfxList;
    PaintGFXArray->obj.statep = &PaintStateArray[elapsedSamples];

    bzero(&PaintObjectArray[elapsedSamples], sizeof(Object2639));
    PaintObjectArray[elapsedSamples] = Paint_Obj;
    PaintObjectArray[elapsedSamples].move.x = o->move.x;
    PaintObjectArray[elapsedSamples].move.y = o->move.y;
    PaintObjectArray[elapsedSamples].init = 0;
    PaintObjectArray[elapsedSamples].loop = 0;
    PaintObjectArray[elapsedSamples].modelList = &PaintGFXArray[elapsedSamples];
}

void Draw_PaintSplotch(void) {
    u32 *drawptr = 0;
    for (int i = 0; i < elapsedSamples; i++) {
        PaintObjectArray[i].move.x = DN_BufferX[elapsedSamples];
        PaintObjectArray[i].move.y = DN_BufferY[elapsedSamples];
        Object_Draw(&PaintObjectArray[i]);
    }
}

#define CURSPD 2
f32 XL = 200;
f32 XR = -20;
f32 YU = 450;
f32 YD = 225;


// #define SET_TURN(f) \
//     if (gTurn) {
//         f += DELTA;
//     }

static u32 prevS = 0;
void InGame_CursorLoop(Object2639 *o) {

    if (sGameState == IG_STATE_RESULTS) {
        return; // cant move if game over
    }

    if (o->move.x < XR) {
        o->move.x = XR;
    }
    if (o->move.x > XL) {
        o->move.x = XL;
    }
    if (o->move.y > YU) {
        o->move.y = YU;
    }
    if (o->move.y < YD) {
        o->move.y = YD;
    }

    #define DELTA2 200
    if (gTurn == TURN_P2) {
        XL = 200 - DELTA2;
        XR = -20 - DELTA2;
    } else {
        XL = 200;
        XR = -20;
    }

    SetElapsed();
    if (prevS != elapsedSamples) {
        SamplePaintSplotch(o);
        Draw_PaintSplotch();
        prevS = elapsedSamples;
    }

    if (gTurn == TURN_P1) {
        o->rotate.pitch = 0;
        if (abs(GameControllers[0].stickX) > 14) {
            if (GameControllers[0].stickX > 0)
                o->move.x -= CURSPD;
            else
                o->move.x += CURSPD;
        }

        if (abs(GameControllers[0].stickY) > 14) {
            if (GameControllers[0].stickY > 0)
                o->move.y += CURSPD;
            else
                o->move.y -= CURSPD;
        }
    } else {
        if (GameControllers[0].held & R_CBUTTONS) {
            o->rotate.pitch += CURSPD;
        }
        if (GameControllers[0].held & L_CBUTTONS) {
            o->rotate.pitch -= CURSPD;
        }

        if (GameControllers[0].held & Z_TRIG) {
            o->move.x += CURSPD * (cosf(o->rotate.pitch));
            o->move.y += CURSPD * (sinf(o->rotate.pitch));
        }
    }

    // if (gTurn == )

}





