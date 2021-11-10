#include <ultra64.h>
#include <PR/gu.h>
#include "n64_defs.h"
#include "gtHelpers.h"


void Object_MatrixApply(Object2639 *o) {
    Mtx Tr, Ro, Scl, SRT;

    extern gtState test64_State;

    guScale(&Scl, o->scale.x, o->scale.y, o->scale.z);
    guRotateRPY(&Ro, o->rotate.roll, o->rotate.pitch, o->rotate.yaw++);
    guTranslate(&Tr, o->move.x, o->move.y, o->move.z);

    guMtxCatL(&Scl, &Ro, &SRT);
    guMtxCatL(&SRT, &Tr, &SRT);

    guMtxCatL(&SRT, &dynamic.VP, &o->modelList[0].obj.statep->sp.transform);
    // guMtxCatL(&SRT, &dynamic.VP, &test64_State.sp.transform);

}


void Object_Draw(Object2639 *o) {
    Object_MatrixApply(o);

    u32 statesPushed = 0;

    for (int i = 0; i < o->segmentCount; i++) {
        gtDrawStatic(gTurboGfxPtr++, o->modelList[i]);
    }
}


