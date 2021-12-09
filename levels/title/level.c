#include <ultra64.h>
#include "n64_defs.h"
#include "levels.h"

EXTERN_OBJ(Title)
EXTERN_OBJ(Button1)
EXTERN_OBJ(Button2)

extern Object2639 *TitleObjList[];

static Level2639 ___ = {
    3,
    TitleObjList,
    CAMERA_STATIC,
    {0, 0, 0},
    {0, 0, 0},
};
Object2639 *TitleObjList[] = {
    &OBJ(Title),
    &OBJ(Button1),
    &OBJ(Button2),
};

