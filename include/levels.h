#pragma once
#include "n64_defs.h"
#include "game/camera.h"

typedef struct _Level2639 {
    u32 objCount;
    Object2639 **objList;
    u32 camMode;
    Vector camSpot;
    Vector camLook;
} Level2639;