#include <ultra64.h>
#include <PR/gu.h>
#include "n64_defs.h"
#include "gtHelpers.h"
#include <ps1.h>

static u32 *sGfxAllocPtr;
extern u16 gRenderedFramebuffer;


/**
 * THEORY
 * -create ST bounding box
 * 
 * */


int max3(int a, int b, int c) {
    if (b > a) a = b;
    if (c > a) a = c;
    return a;
}

int min3(int a, int b, int c) {
    if (b > a) a = b;
    if (c > a) a = c;
    return a;
}

void getBoundingBox(SVECTOR *uv0, SVECTOR *uv1, SVECTOR *uv2, u32 *ul, u32 *lr) {
    *ul = (min3(uv0->vx, uv1->vx, uv2->vx) << 16) | (min3(uv0->vy, uv1->vy, uv2->vy) << 16);
    *lr = (max3(uv0->vx, uv1->vx, uv2->vx) << 16) | (max3(uv0->vy, uv1->vy, uv2->vy) << 16);
}

void gfxAlloc_Init(gtGlobState *g) {
    g->sp.segBases[T3D_SEG_GFX] = (u32)&gfxAlloc[gRenderedFramebuffer];
    sGfxAllocPtr = &gfxAlloc[gRenderedFramebuffer];
}

u32 qd_alloc(u32 size, u32 *virt) {
    u32 ret = (T3D_SEG_GFX << 24) + ((u32)sGfxAllocPtr - (u32)gfxAlloc[gRenderedFramebuffer]);
    *virt = sGfxAllocPtr;

    // bzero(virt, size);

    sGfxAllocPtr = (Gfx*)ALIGN64((u32)sGfxAllocPtr + size);

    return ret;
}

gtState *allocState(gtState *vptr) {
    return qd_alloc(sizeof(gtState), vptr);
}

gtStateL *allocStateL(gtStateL *vptr) {
    return qd_alloc(sizeof(gtStateL), vptr);
}

// 800023c4
Vtx *convVtx(TMESH mesh[], u32 len) {
    Vtx *vtxBuffer;
    Vtx *ret = qd_alloc(len * sizeof(Vtx), &vtxBuffer);
    for (int i = 0; i < len; i++) {
        vtxBuffer[i].v.ob[0] = mesh->v[i].vx;
        vtxBuffer[i].v.ob[1] = mesh->v[i].vy;
        vtxBuffer[i].v.ob[2] = mesh->v[i].vz;

        vtxBuffer[i].v.flag = 0;

        vtxBuffer[i].v.tc[0] = mesh->u[i].vx;
        vtxBuffer[i].v.tc[0] = mesh->u[i].vy;

        vtxBuffer[i].v.cn[0] = mesh->c[i].r;
        vtxBuffer[i].v.cn[1] = mesh->c[i].g;
        vtxBuffer[i].v.cn[2] = mesh->c[i].b;
        vtxBuffer[i].v.cn[3] = 0xFF;
    }

    return vtxBuffer;
}

gtTriN *convTris(int index[], u32 len) {
    gtTriN *triBuffer;

    gtTriN *ret = qd_alloc(len * sizeof(gtTriN), &triBuffer);

    for (int i = 0, t = 0; i < len; i++, t += 3) {
        triBuffer[i].v0 = index[t    ];
        triBuffer[i].v1 = index[t + 1];
        triBuffer[i].v2 = index[t + 2];
        triBuffer[i].flag = 0;
    }

    return triBuffer;
}

int count_vertices(int index[], int len) {
    int ret = -1;
    for (int i = 0; i < len; i++) {
        if (index[i] > ret) {
            ret = index[i];
        }
    }

    return ret + 1;
}

Gfx normalRender[] = {
    gsDPSetOtherMode(
        G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
        G_AC_NONE | G_ZS_PIXEL
    ),
    gsDPEndDisplayList(),
};

static Vector move = {0, 0, 0};
static Vector turn = {90, 180, 0};
static Vector scale = {1.0, 1.0, 1.0};

void Matrix_Apply(Mtx *Output) {
    Mtx4 Tr, Ro, Scl, SRT;

    turn.yaw++;
    turn.roll++;
    turn.pitch++;

    extern gtState test64_State;

    guScaleF(Scl, scale.x, scale.y, scale.z);
    guRotateRPYF(Ro, turn.roll, turn.pitch, turn.yaw);
    guTranslateF(Tr, move.x, move.y, move.z);

    guMtxCatF(Scl, Ro, SRT);
    guMtxCatF(SRT, Tr, SRT);

    Mtx Final;
    guMtxF2L(SRT, &Final);
    guMtxCatL(&Final, &dynamic.VP, Output);
    // guMtxCatL(&SRT, &dynamic.VP, &test64_State.sp.transform);
}


void MakeVertex(Vtx *v, TMESH *mesh, int index[], int i) {
    v->v.ob[0] = mesh->v[index[i]].vx;
    v->v.ob[1] = mesh->v[index[i]].vy;
    v->v.ob[2] = mesh->v[index[i]].vz;

    v->v.flag = 0;
    v->v.tc[0] = mesh->u[i].vx;
    v->v.tc[1] = mesh->u[i].vy;

    v->v.cn[0] = mesh->c[i].r;
    v->v.cn[1] = mesh->c[i].g;
    v->v.cn[2] = mesh->c[i].b;
    v->v.cn[3] = 0xFF;
}

void MakeTri(gtTriN *t, int v0, int v1, int v2) {
    t->v0 = v0;
    t->v1 = v1;
    t->v2 = v2;
    t->flag = 0;
}

void MakeOneTriangleState(TMESH *mesh, int index[], int i, u64 *texture) {
    gtGfx *p = gTurboGfxPtr++;

    qd_alloc(sizeof(Vtx)*3, &p->obj.vtxp);
    qd_alloc(sizeof(gtTriN) * 1, &p->obj.trip);


    MakeTri(&p->obj.trip[0], 0, 1, 2);

    MakeVertex(&p->obj.vtxp[0], mesh, index, i + 0);
    MakeVertex(&p->obj.vtxp[1], mesh, index, i + 1);
    MakeVertex(&p->obj.vtxp[2], mesh, index, i + 2);

    gtState *s;
    allocState(&p->obj.statep);
    s = p->obj.statep;
    if (i != 0) {
        s->sp.flag |= GT_FLAG_NOMTX;
    }
    s->sp.vtxCount = 3;
    s->sp.vtxV0 = 0;
    s->sp.textureState = 0;
    s->sp.triCount = 1;
    s->sp.renderState = (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER);
    gDPSetOtherMode(&s->sp.rdpOthermode,
        G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
        G_AC_NONE | G_ZS_PIXEL
    );

    u32 ul = 0;
    u32 lr = 0;
    getBoundingBox(&mesh->u[i + 0], &mesh->u[i + 1], &mesh->u[i + 2],
        &ul, &lr
    );

    s->sp.rdpCmds = (Gfx*)MatAlloc_AllocTextureTileDL(
        texture,
        PARAM_PACK(G_IM_FMT_RGBA, G_IM_SIZ_16b, 128, 128),
        ul, lr
    );

    if (i == 0) {
        guMtxIdent(&s->sp.transform);
        // guMtxCatL(&s->sp.transform, &dynamic.VP, &s->sp.transform);
        Matrix_Apply(&s->sp.transform);
    }
}


void TMESH_Draw(TMESH *mesh, int index[], u64 *texture) {
    for (int i = 0; i < mesh->len; i++) {
        MakeOneTriangleState(mesh, index, i*3, texture);
    }
}

// void TMESH_Draw(TMESH *mesh, int index[], u64 *texture) {
//     gtGfx *p = gTurboGfxPtr++;
//     int vlen = count_vertices(index, mesh->len * 3);

//     p->obj.vtxp = convVtx(mesh, vlen);
//     p->obj.trip = convTris(index, mesh->len);

//     gtState *s;
//     allocState(&s);
//     p->obj.statep = s;
//     s->sp.vtxCount = vlen;
//     s->sp.vtxV0 = 0;
//     s->sp.textureState = 0;
//     s->sp.triCount = mesh->len;
//     s->sp.renderState = (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER);
//     gDPSetOtherMode(&s->sp.rdpOthermode,
//         G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
//         G_AC_NONE | G_ZS_PIXEL
//     );
//     s->sp.rdpCmds = (Gfx*)NULL;


//     guMtxIdent(&s->sp.transform);
//     // guMtxCatL(&s->sp.transform, &dynamic.VP, &s->sp.transform);
//     Matrix_Apply(&s->sp.transform);
// }

