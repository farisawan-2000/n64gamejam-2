#include <ultra64.h>
#include "n64_defs.h"
#include "levels.h"

EXTERN_OBJ(ControlCenter)
EXTERN_OBJ(CButton_Right)
EXTERN_OBJ(CButton_Left)
EXTERN_OBJ(Lever)
EXTERN_OBJ(SignP1)
EXTERN_OBJ(SignP2)
EXTERN_OBJ(SignP2_2)
EXTERN_OBJ(SignPass)
EXTERN_OBJ(Canvas)
EXTERN_OBJ(Cursor)


extern Object2639 *GameObjList[];

static Level2639 ___ = {
    10,
    GameObjList,
    CAMERA_STATIC,
    {0, 256, 50},
    {0, 0, 0},
};

Object2639 *GameObjList[] = {
    &OBJ(ControlCenter),
    &OBJ(CButton_Right),
    &OBJ(CButton_Left),
    &OBJ(Lever),
    &OBJ(SignP1),
    &OBJ(SignP2),
    &OBJ(SignP2_2),
    &OBJ(SignPass),
    &OBJ(Canvas),
    &OBJ(Cursor),
};

