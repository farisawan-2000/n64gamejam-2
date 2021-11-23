#include <ultra64.h>
#include <gbi.h>
#include <PR/gt.h>
#include "n64_defs.h"
#include "gtHelpers.h"
extern Object2639 bookModel_Obj;
Object2639 *bookModel_objp = &bookModel_Obj;
Vtx testI4_Plane_mesh_vtx_0[4] = {
	{{{-195, 0, 100},0, {-16, 2032},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{195, 0, 100},0, {4080, 2032},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{195, 0, -100},0, {4080, -16},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-195, 0, -100},0, {-16, -16},{0x0, 0x7F, 0x0, 0xFF}}},
};
gtTriN bookModel_tris_0[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {0, 2, 3, 0},
};
gtState bookModel_State = {
    (GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    4, // vtxCount  8
    0, // vtxV0 9
    2, // triCount a
    0x0, // some_flag b
    NULL, // c
    gsDPSetOtherMode(
        G_AD_NOISE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TL_TILE | G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
        G_AC_NONE | G_ZS_PIXEL
    ), // 10
    {
    // integer portion:
        0x00010000, 0x00000000,
        0x00000001, 0x00000000,
        0x00000000, 0x00010000,
        0x00000000, 0x00000001,
    // fractional portion:
        0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000000, 0x00000000,
        0x00000000, 0x00000000,
    }
};


gtGfx bookModel_GfxList[] = {
    {
        NULL,
        (gtState *)&bookModel_State,
        testI4_Plane_mesh_vtx_0+0,
        bookModel_tris_0,
    },
};

extern u64 i4SuperTex[];

Object2639 bookModel_Obj = {
    {0, 0, 0},
    {0, 0, 0},
    {1.0, 1.0, 1.0},

    1, // gfxlist count
    &bookModel_GfxList, // gfxlist name

    MATERIAL_4B_TEXTURE,
    {G_IM_FMT_I, 0, 128, 64},
    i4SuperTex,

    NULL,
    NULL,
};

