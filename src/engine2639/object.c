#include <ultra64.h>
#include <PR/gu.h>
#include "n64_defs.h"
#include "gtHelpers.h"

u32 gTrisRendered = 0;

void obj_rotate(Object2639 *this) {
    this->rotate.yaw += 1.0f;
}

void Object_MaterialApply(Object2639 *o) {

    gtStateSetOthermode(&(o->modelList[0].obj.statep->sp.rdpOthermode), GT_RENDERMODE, (G_RM_ZB_OPA_SURF | G_RM_ZB_OPA_SURF2));
    gtStateSetOthermode(&(o->modelList[0].obj.statep->sp.rdpOthermode), GT_CYCLETYPE, G_CYC_1CYCLE);

    switch (o->matType) {
        case MATERIAL_TEXTURE:
            o->modelList[0].obj.statep->sp.rdpCmds = MatAlloc_AllocTextureDL(o->matPtr, o->matParamWord);
            break;
        case MATERIAL_4B_TEXTURE:
            o->modelList[0].obj.statep->sp.rdpCmds = MatAlloc_AllocTextureDL_4b(o->matPtr, o->matParamWord);
            break;
    }
}

void Object_MatrixApply(Object2639 *o) {
    Mtx Tr, Ro, Scl, SRT;

    extern gtState test64_State;

    guScale(&Scl, o->scale.x, o->scale.y, o->scale.z);
    guRotateRPY(&Ro, o->rotate.roll, o->rotate.pitch, o->rotate.yaw);
    guTranslate(&Tr, o->move.x, o->move.y, o->move.z);

    guMtxCatL(&Scl, &Ro, &SRT);
    guMtxCatL(&SRT, &Tr, &SRT);

    guMtxCatL(&SRT, &dynamic.VP, &o->modelList[0].obj.statep->sp.transform);
    // guMtxCatL(&SRT, &dynamic.VP, &test64_State.sp.transform);

}


void Object_Draw(Object2639 *o) {

    if (o->init != NULL) {
        o->init(o);
        o->init = NULL;
    }
    if (o->loop != NULL) {
        o->loop(o);
    }

    Object_MatrixApply(o);

    Object_MaterialApply(o);

    for (int i = 0; i < o->segmentCount; i++) {
        gtDrawStatic(gTurboGfxPtr++, o->modelList[i]);

        if (o->modelList[i].obj.statep)
            gTrisRendered += o->modelList[i].obj.statep->sp.triCount;
    }
}


