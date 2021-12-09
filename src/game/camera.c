#include <ultra64.h>
#include "n64_defs.h"
#include "camera.h"
#include "controller.h"

#define MV_SPD 6.0f
#define ANG_CLMP 180.0f
#define clampA(x) if ((x) > ANG_CLMP) {(x) = ANG_CLMP;}
#define clampAN(x) if ((x) < -ANG_CLMP) {(x) = -ANG_CLMP;}
#define clampZ(x) if ((x) < 0) {(x) = 0;}

Vector sCameraLook = {0, 0, 0};
Vector sCameraLook_Target = {0, 0, 0};
Vector sCameraSpot = {0, 0, 0};
Vector sCameraSpot_Target = {0, 0, 0};
Vector sCameraRPY  = {0, 0, 0};
Vector sCameraRPY_Target  = {0, 0, 0};
Vector sOrigin = {0,0,0};

u32 gCameraMode = CAMERA_FREEMOVE;

void VectorSubtract (Vector *dest, Vector *v1, Vector *v2) {
    dest->x = v1->x - v2->x;
    dest->y = v1->y - v2->y;
    dest->z = v1->z - v2->z;
}

void FloatApproach(f32 *dest, f32 *src, f32 multiplier) {
    *dest = *dest + (*src - *dest) * multiplier;
}

void VectorFullApproach(Vector *dest, f32 *src, f32 multiplier) {
    dest->x = dest->x + (*src - dest->x) * multiplier;
    dest->y = dest->y + (*src - dest->y) * multiplier;
    dest->z = dest->z + (*src - dest->z) * multiplier;
}

void VectorNormalize (Vector *dest, Vector *src) {
    f32 vecMag = sqrtf((src->x * src->x) + (src->y * src->y) + (src->z * src->z));
    if (vecMag == 0.0f) {
        return 0.0f;
    }
    dest->x *= 1.0f / vecMag;
    dest->y *= 1.0f / vecMag;
    dest->z *= 1.0f / vecMag;
    return vecMag;
}

void VectorApproach(Vector *dest, Vector *src, f32 multiplier) {
    dest->x = dest->x + (src->x - dest->x) * multiplier;
    dest->y = dest->y + (src->y - dest->y) * multiplier;
    dest->z = dest->z + (src->z - dest->z) * multiplier;
}

void VectorAngleApproach(Vector *dest, Vector *src, f32 speed) {
    Vector subResult;
    Vector approachResult;

    VectorSubtract(&subResult, dest, src);
    VectorApproach(&approachResult, &subResult, speed);
    VectorSubtract(&dest, &dest, &approachResult);
}

void VectorCopy(Vector * restrict dest, Vector * restrict src) {
    *dest = *src;
}

void VectorExtend(Vector *dest, Vector *src, f32 dist, f32 pitch, f32 yaw) {
    dest->x = src->x + dist * cosf(pitch) * sinf(yaw);
    dest->y = src->y + dist * sinf(pitch);
    dest->z = src->z + dist * cosf(pitch) * cosf(yaw);
}

void CameraApproach(void) {
    VectorApproach(&sCameraSpot, &sCameraSpot_Target, 0.2f);
    VectorApproach(&sCameraLook, &sCameraLook_Target, 0.2f);
    VectorApproach(&sCameraRPY, &sCameraRPY_Target, 0.2f);
}


void CameraApply_RPY(void) {
    VectorExtend(&sCameraLook_Target, &sCameraSpot, 500.0f, sCameraRPY.pitch * (M_PI / 180.0f),
        (M_PI / 180.0f) * (sCameraRPY.yaw)
    );
    CameraApproach();
}

void CameraPosApply(Vector *v, f32 dist, f32 yaw, f32 pitch) {
    VectorExtend(v, v, dist, 0,
        (M_PI / 180.0f) * yaw
    );
}

static void CameraUpdate_Free(void) {
    if (abs(GameControllers[0].stickX) >= 14) {
        if (GameControllers[0].stickX > 0) {
            CameraPosApply(&sCameraSpot_Target, -MV_SPD, sCameraRPY.yaw + 90, sCameraRPY.pitch);
        } else {
            CameraPosApply(&sCameraSpot_Target, MV_SPD, sCameraRPY.yaw + 90, sCameraRPY.pitch);
        }
    }
    if (abs(GameControllers[0].stickY) >= 14) {
        if (GameControllers[0].stickY > 0) {
            CameraPosApply(&sCameraSpot_Target, MV_SPD, sCameraRPY.yaw, sCameraRPY.pitch);
        } else {
            CameraPosApply(&sCameraSpot_Target, -MV_SPD, sCameraRPY.yaw, sCameraRPY.pitch);
        }
    }

    // #define CAM_YAW (45)
    if (GameControllers[0].held & R_CBUTTONS) {
        sCameraRPY_Target.yaw -= 2;
    }
    if (GameControllers[0].held & L_CBUTTONS) {
        sCameraRPY_Target.yaw += 2;
    }
    if (GameControllers[0].held & U_CBUTTONS) {
        sCameraRPY_Target.pitch -= 2;
    }
    if (GameControllers[0].held & D_CBUTTONS) {
        sCameraRPY_Target.pitch += 2;
    }

    if (GameControllers[0].held & A_BUTTON) {
        sCameraSpot_Target.y += 2;
    }
    if (GameControllers[0].held & B_BUTTON) {
        sCameraSpot_Target.y -= 2;
    }

    clampA(sCameraRPY_Target.yaw);
    clampAN(sCameraRPY_Target.yaw);
    clampA(sCameraRPY_Target.pitch);
    clampAN(sCameraRPY_Target.pitch);

    clampA(sCameraRPY.yaw);
    clampAN(sCameraRPY.yaw);
    clampA(sCameraRPY.pitch);
    clampAN(sCameraRPY.pitch);



    CameraApply_RPY();
}

void CameraUpdate(Mtx *lookat, f32 mf[4][4]) {

    switch (gCameraMode) {
        case CAMERA_STATIC: CameraApply_RPY(); break;
        case CAMERA_FREEMOVE: CameraUpdate_Free(); break;
        case CAMERA_CUTSCENE: break;

        // something else is setting the lookat matrix so we dont care
        case CAMERA_OBJECTMOVE: break;
    }

    // Scrapped feature: camera rotation/shake

    // Vector upVec;
    // VectorExtend(&upVec, &sOrigin, 1.0f, sCameraRPY.pitch, sCameraRPY.yaw);

    guLookAtF(mf,
        sCameraSpot.x, sCameraSpot.y, sCameraSpot.z,
        sCameraLook.x, sCameraLook.y, sCameraLook.z,
        0,1,0
    );
    guMtxF2L(mf, lookat);
}

