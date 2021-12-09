#pragma once
#include "n64_defs.h"

extern Vector sCameraLook;
extern Vector sCameraSpot;
extern Vector sCameraRPY;

extern Vector sCameraLook_Target;
extern Vector sCameraSpot_Target;
extern Vector sCameraRPY_Target;

enum CameraModes {
    CAMERA_STATIC = 0,
    CAMERA_FREEMOVE,
    CAMERA_PLAYER,
    CAMERA_CUTSCENE,
    CAMERA_OBJECTMOVE,
};

extern u32 gCameraMode;

void VectorCopy(Vector * restrict dest, Vector * restrict src);
void VectorFullApproach(Vector *dest, f32 *src, f32 multiplier);
