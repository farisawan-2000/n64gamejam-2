#pragma once

extern Vector sCameraLook;
extern Vector sCameraSpot;
extern Vector sCameraRPY;

enum CameraModes {
    CAMERA_STATIC = 0,
    CAMERA_FREEMOVE,
    CAMERA_PLAYER,
    CAMERA_CUTSCENE,
    CAMERA_OBJECTMOVE,
};

