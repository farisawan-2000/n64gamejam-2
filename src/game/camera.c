#include <ultra64.h>
#include "n64_defs.h"
#include "controller.h"

Vector sCameraLook = {160, 120, 400};
Vector sCameraLook_Target = {0, 0, 0};
Vector sCameraSpot = {0, 0, 0};
Vector sCameraSpot_Target = {0, 0, 0};
Vector sCameraRPY  = {0, 0, 0};
Vector sCameraRPY_Target  = {0, 0, 0};


enum CameraModes {
    CAMERA_STATIC = 0,
    CAMERA_PLAYER,
    CAMERA_CUTSCENE,
};

u32 gCameraMode = CAMERA_PLAYER;

void VectorApproach(Vector *dest, Vector *src, f32 multiplier) {
    dest->x = dest->x + (src->x - dest->x) * multiplier;
    dest->y = dest->y + (src->y - dest->y) * multiplier;
    dest->z = dest->z + (src->z - dest->z) * multiplier;
}

void VectorCopy(Vector * restrict dest, Vector * restrict src) {
    *dest = *src;
}

void VectorExtend(Vector *dest, Vector *src, f32 dist, f32 pitch, f32 yaw) {
    dest->x = src->x + dist * cosf(pitch) * sinf(yaw);
    dest->y = src->y + dist * sinf(pitch);
    dest->z = src->z + dist * cosf(pitch) * cosf(yaw);
}


void CameraApply(void) {
    VectorExtend(&sCameraLook_Target, &sCameraSpot, 500.0f, sCameraRPY.pitch * (M_PI / 180.0f),
        (M_PI / 180.0f) * sCameraRPY.yaw
    );

    VectorApproach(&sCameraSpot, &sCameraSpot_Target, 0.2f);
    VectorApproach(&sCameraLook, &sCameraLook_Target, 0.2f);
    VectorApproach(&sCameraRPY, &sCameraRPY_Target, 0.2f);
}

void CameraPosApply(Vector *v, f32 dist, f32 yaw, f32 pitch) {
    VectorExtend(v, v, dist, 0,
        (M_PI / 180.0f) * yaw
    );
}


// TODO: look at player
#define MV_SPD 6.0f
#define ANG_CLMP 180.0f
#define clampA(x) if ((x) > ANG_CLMP) {(x) = -ANG_CLMP;}
#define clampAN(x) if ((x) < -ANG_CLMP) {(x) = ANG_CLMP;}

static void CameraUpdate_Player(void) {
    if (GameControllers[0].stickX != 0) {
        if (GameControllers[0].stickX > 0) {
            CameraPosApply(&sCameraSpot_Target, -MV_SPD, sCameraRPY.yaw + 90, sCameraRPY.pitch);
        } else {
            CameraPosApply(&sCameraSpot_Target, MV_SPD, sCameraRPY.yaw + 90, sCameraRPY.pitch);
        }
    }
    if (GameControllers[0].stickY != 0) {
        if (GameControllers[0].stickY > 0) {
            CameraPosApply(&sCameraSpot_Target, MV_SPD, sCameraRPY.yaw, sCameraRPY.pitch);
        } else {
            CameraPosApply(&sCameraSpot_Target, -MV_SPD, sCameraRPY.yaw, sCameraRPY.pitch);
        }
    }

    if (GameControllers[0].button & R_CBUTTONS) {
        sCameraRPY_Target.yaw -= 1;
    }
    if (GameControllers[0].button & L_CBUTTONS) {
        sCameraRPY_Target.yaw += 1;
    }
    if (GameControllers[0].button & U_CBUTTONS) {
        sCameraRPY_Target.pitch -= 1;
    }
    if (GameControllers[0].button & D_CBUTTONS) {
        sCameraRPY_Target.pitch += 1;
    }

    if (GameControllers[0].button & A_BUTTON) {
        sCameraSpot_Target.y += 2;
    }
    if (GameControllers[0].button & B_BUTTON) {
        sCameraSpot_Target.y -= 2;
    }

    clampA(sCameraRPY.yaw);
    clampAN(sCameraRPY.yaw);
    clampA(sCameraRPY.pitch);
    clampAN(sCameraRPY.pitch);


    CameraApply();
}



void CameraUpdate(Mtx *lookat, f32 mf[4][4]) {

    switch (gCameraMode) {
        case CAMERA_STATIC: break;
        case CAMERA_PLAYER: CameraUpdate_Player(); break;
        case CAMERA_CUTSCENE: break;
    }


    guLookAtF(mf,
        sCameraSpot.x, sCameraSpot.y, sCameraSpot.z,
        sCameraLook.x, sCameraLook.y, sCameraLook.z,
        0, 1, 0
    );
    guMtxF2L(mf, lookat);
}

