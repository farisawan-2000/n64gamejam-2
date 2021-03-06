#include <ultra64.h>
#include "n64_defs.h"
#include "game/controller.h"
#include "game/camera.h"

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

#define LEFT_SIGN   200
#define DELTA       225
#define RIGHT_SIGN -200

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
#define SAMPLES_PER_SEX 8

s16 DN_BufferX[2][SECOND_COUNT * SAMPLES_PER_SEX];
s16 DN_BufferY[2][SECOND_COUNT * SAMPLES_PER_SEX];

u32 ReloadTitle = 0;
u32 elapsedSamples = 0;
u32 EXPOSED_State = 0;
u32 EXPOSED_Timer = 0;
u32 maxSamples = 0;

#include <PR/gt.h>

gtState PaintStateArray[2][SECOND_COUNT * SAMPLES_PER_SEX * 2];
Object2639 PaintObjectArray[2][SECOND_COUNT * SAMPLES_PER_SEX * 2];
gtGfx PaintGFXArray[2][SECOND_COUNT * SAMPLES_PER_SEX * 2];
extern Object2639 Paint_Obj;

extern gtState Paint_State;
extern gtGfx Paint_GfxList;

static void NextStateProc(void) {
    EXPOSED_State = sGameState;
    EXPOSED_Timer = sStateTimer;
    switch (sGameState) {
        case IG_STATE_RESET:
            gTurn = TURN_P1;
            elapsedSamples = 0;
            sGameNextState = IG_STATE_P1_DRAW;
            break;
        case IG_STATE_P1_DRAW:
            // *(vs8*)0=0;
            if (sStateTimer >= (60 * SECOND_COUNT) - 50) {
                sGameNextState = IG_STATE_P1_P2_TRANSITION;
                for (int i = 0; i < elapsedSamples; i++) {
                    PaintObjectArray[TURN_P1][i].move.x -= DELTA;
                }
            }
            break;
        case IG_STATE_P1_P2_TRANSITION:
            // bzero(DN_BufferX, sizeof DN_BufferX);
            // bzero(DN_BufferY, sizeof DN_BufferY);
            gTurn = TURN_P2;
            elapsedSamples = 0;


            if (sStateTimer > 300) {
                sGameNextState = IG_STATE_P2_DRAW;
            }
            break;
        case IG_STATE_P2_DRAW:
            if (sStateTimer > (60 * SECOND_COUNT) - 50) {
                sGameNextState = IG_STATE_RESULTS;
            }
            break;
        case IG_STATE_RESULTS:
            elapsedSamples = 0;
            if (GameControllers[0].button & START_BUTTON) {
                sGameNextState = IG_STATE_RESET;
            }
            if (GameControllers[0].button & B_BUTTON) {
                sGameNextState = IG_STATE_RESET;
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




f32 P1PosT = RIGHT_SIGN;
void InGame_SignP1Loop(Object2639 *o) {
    if (gTurn) {
        P1PosT = RIGHT_SIGN - DELTA;
    } else {
        P1PosT = RIGHT_SIGN;
    }

    FloatApproach(&o->move.x, &P1PosT, 0.2f);
}

f32 P2PosT = LEFT_SIGN;
void InGame_SignP2_1Loop(Object2639 *o) {
    if (gTurn==0) {
        P2PosT = LEFT_SIGN + DELTA;
    } else {
        P2PosT = LEFT_SIGN;
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


extern u32 sMenuChoice ;

f32 PassPosT = LEFT_SIGN;
void InGame_SignPassLoop(Object2639 *o) {
    if (sMenuChoice == 2) {
        o->move.x = -1000;
        return;
    }
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






void SetElapsed(void) {
    elapsedSamples = sStateTimer / (60 / SAMPLES_PER_SEX);

    if (gTurn == TURN_P1) {
        maxSamples = elapsedSamples;
    }
}

u32 gScore = 0;
void SamplePaintSplotch(Object2639 *o) {
    // if (gTurn == TURN_P1) {
        DN_BufferX[gTurn][elapsedSamples] = o->move.x;
        DN_BufferY[gTurn][elapsedSamples] = o->move.y;
    // }

    PaintStateArray[gTurn][elapsedSamples] = Paint_State;

    bzero(&PaintGFXArray[gTurn][elapsedSamples], sizeof(Object2639));
    PaintGFXArray[gTurn][elapsedSamples] = Paint_GfxList;
    PaintGFXArray[gTurn][elapsedSamples].obj.statep = &PaintStateArray[gTurn][elapsedSamples];

    bzero(&PaintObjectArray[gTurn][elapsedSamples], sizeof(Object2639));
    PaintObjectArray[gTurn][elapsedSamples] = Paint_Obj;
    PaintObjectArray[gTurn][elapsedSamples].move.x = o->move.x;
    PaintObjectArray[gTurn][elapsedSamples].move.y = o->move.y;
    switch (sGameState) {
        case IG_STATE_P1_DRAW:
            if (GameControllers[0].held & A_BUTTON) {
                PaintObjectArray[gTurn][elapsedSamples].matType = MATERIAL_NONE;
            } else {
                PaintObjectArray[gTurn][elapsedSamples].matType = MATERIAL_COLOR;
                PaintObjectArray[gTurn][elapsedSamples].matParamWord = 0xFFFFFFFF;
                PaintObjectArray[gTurn][elapsedSamples].move.z = 4000;
            }
            break;
        case IG_STATE_P2_DRAW:
            if (GameControllers[0].held & R_TRIG) {
                PaintObjectArray[gTurn][elapsedSamples].matType = MATERIAL_COLOR;
                PaintObjectArray[gTurn][elapsedSamples].matParamWord = 0xFF0000FF;
                PaintObjectArray[gTurn][elapsedSamples].move.z = 890;
            } else {
                PaintObjectArray[gTurn][elapsedSamples].matType = MATERIAL_COLOR;
                PaintObjectArray[gTurn][elapsedSamples].matParamWord = 0xFFFFFFFF;
                PaintObjectArray[gTurn][elapsedSamples].move.z = 4000;
            }
    }
    PaintObjectArray[gTurn][elapsedSamples].modelList = &PaintGFXArray[gTurn][elapsedSamples];

    if (gTurn == TURN_P2) {
        // u32 r = 0;
        // skip this splotch if uncounted
        if (PaintObjectArray[TURN_P2][elapsedSamples].move.z < 3000) {
            for (int i = 0; i < elapsedSamples; i++) {
                // skip uncounted splotches
                if (PaintObjectArray[0][i].move.z < 3000) continue;

                // check if current sample ever hits something from P1
                if ((abs((DN_BufferX[TURN_P1][i] - 0xC8) - DN_BufferX[TURN_P2][elapsedSamples]) < 100)
                    && (abs((DN_BufferY[TURN_P1][i]) - DN_BufferY[TURN_P2][elapsedSamples]) < 100)
                ) {
                    gScore += 5;
                }
            }
        }
        // gScore = r;
    } else {
        gScore = 0;
    }
}

void Draw_PaintSplotch(void) {
    u32 *drawptr = 0;

    // u32 score = 0;

    if (sGameState == IG_STATE_P2_DRAW) {
        for (int i = 0; i < maxSamples; i++) {
            if (PaintObjectArray[TURN_P1][i].move.z < 3000) {
                Object_Draw(&PaintObjectArray[TURN_P1][i]);
            }
        }
    }
    for (int i = 0; i < elapsedSamples; i++) {
        // PaintObjectArray[i].move.x = DN_BufferX[elapsedSamples];
        // PaintObjectArray[i].move.y = DN_BufferY[elapsedSamples];
        if (PaintObjectArray[TURN_P1][i].move.z < 3000) {
            Object_Draw(&PaintObjectArray[gTurn][i]);
        }
    }

    // gScore = score;
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
f32 gYaw = 0;

// extern u8 
void InGame_CursorLoop(Object2639 *o) {

    if (sGameState == IG_STATE_RESULTS) {
        return; // cant move if game over
    }

    if (sGameState == IG_STATE_P1_P2_TRANSITION) {
        o->move.x = -DELTA;
        o->move.y = 0;
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
    if (sGameState != IG_STATE_P1_P2_TRANSITION) {
        SamplePaintSplotch(o);
        prevS = elapsedSamples;
        Draw_PaintSplotch();
    }
    else 
    {
        for (int i = 0; i < maxSamples; i++) {

            Object_Draw(&PaintObjectArray[TURN_P1][i]);
        }
    }

    if (gTurn == TURN_P1) {
        o->rotate.yaw = 0;
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
            o->rotate.yaw += CURSPD*2;
        }
        if (GameControllers[0].held & L_CBUTTONS) {
            o->rotate.yaw -= CURSPD*2;
        }

        if (GameControllers[0].held & Z_TRIG) {
            o->move.x += 2.0f * (cosf(M_DTOR * (o->rotate.yaw + 90)));
            o->move.y += 2.0f * (sinf(M_DTOR * (o->rotate.yaw + 90)));
        }
        gYaw = o->rotate.yaw;
    }

    // if (gTurn == )

}





