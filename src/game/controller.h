#pragma once
#include "n64_defs.h"

typedef struct {
  u16 button;
  u16 held;
  s8 stickX;
  s8 stickY;
  f32 angle;
} Controller2639;

extern Controller2639 GameControllers[4];


