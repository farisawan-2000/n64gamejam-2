#include <ultra64.h>
#include <gbi.h>
#include <PR/gt.h>
#include "n64_defs.h"
#include "gtHelpers.h"
extern Object2639 Cursor_Obj;
Object2639 *Cursor_objp = &Cursor_Obj;
static
Vtx cursor_Cone_mesh_vtx_cull[8] = {
	{{{-92, -65, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-92, -65, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-92, 65, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{-92, 65, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{92, -65, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{92, -65, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{92, 65, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
	{{{92, 65, 0},0, {-16, -16},{0x0, 0x0, 0x0, 0x0}}},
};
static
Vtx cursor_Cone_mesh_vtx_0[3] = {
	{{{0, 65, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-92, -65, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{92, -65, 0},0, {-16, 1008},{0x0, 0x0, 0x7F, 0xFF}}},
};
gtTriN Cursor_tris_0[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0},
};
gtState Cursor_State = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    3, // vtxCount  8
    0, // vtxV0 9
    1, // triCount a
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


gtGfx Cursor_GfxList[] = {
    {
        NULL,
        (gtState *)&Cursor_State,
        cursor_Cone_mesh_vtx_0+0,
        Cursor_tris_0,
    },
};
OFUN(InGame_CursorLoop);
Object2639 Cursor_Obj = {
    {0, 0, 900},
    {0, 0, 0},
    {0.25, 0.25, 0.25},

    1, // gfxlist count
    &Cursor_GfxList, // gfxlist name

    MATERIAL_TEXTURE,
    PARAM_PACK(G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32),
    CButton_tex,

    NULL,
    InGame_CursorLoop,
};

