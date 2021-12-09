#include <ultra64.h>
#include <gbi.h>
#include <PR/gt.h>
#include "n64_defs.h"
#include "gtHelpers.h"
extern Object2639 Canvas_Obj;
Object2639 *Canvas_objp = &Canvas_Obj;
static
Vtx canvas_Cube_mesh_vtx_0[24] = {
	{{{600, 600, 150},0, {624, 496},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-600, 600, 150},0, {880, 496},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-600, -600, 150},0, {880, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{600, -600, 150},0, {624, 240},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{600, -600, -150},0, {368, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{600, -600, 150},0, {624, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-600, -600, 150},0, {624, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-600, -600, -150},0, {368, -16},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-600, -600, -150},0, {368, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-600, -600, 150},0, {624, 1008},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-600, 600, 150},0, {624, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-600, 600, -150},0, {368, 752},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-600, 600, -150},0, {112, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{600, 600, -150},0, {368, 496},{0x0, 0x0, 0x81, 0xFF}}},
	{{{600, -600, -150},0, {368, 240},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-600, -600, -150},0, {112, 240},{0x0, 0x0, 0x81, 0xFF}}},
	{{{600, 600, -150},0, {368, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{600, 600, 150},0, {624, 496},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{600, -600, 150},0, {624, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{600, -600, -150},0, {368, 240},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-600, 600, -150},0, {368, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{-600, 600, 150},0, {624, 752},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{600, 600, 150},0, {624, 496},{0x0, 0x7F, 0x0, 0xFF}}},
	{{{600, 600, -150},0, {368, 496},{0x0, 0x7F, 0x0, 0xFF}}},
};
gtTriN Canvas_tris_0[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {0, 2, 3, 0},
    {4, 5, 6, 0}, {4, 6, 7, 0},
    {8, 9, 10, 0}, {8, 10, 11, 0},
    {12, 13, 14, 0}, {12, 14, 15, 0},
    {16, 17, 18, 0}, {16, 18, 19, 0},
    {20, 21, 22, 0}, {20, 22, 23, 0},
};
gtState Canvas_State = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    24, // vtxCount  8
    0, // vtxV0 9
    12, // triCount a
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


gtGfx Canvas_GfxList[] = {
    {
        NULL,
        (gtState *)&Canvas_State,
        canvas_Cube_mesh_vtx_0+0,
        Canvas_tris_0,
    },
};

OFUN(InGame_CanvasLoop);
Object2639 Canvas_Obj = {
    {100, 350, 1100},
    {0, 0, 0},
    {0.25, 0.25, 0.25},

    1, // gfxlist count
    &Canvas_GfxList, // gfxlist name

    MATERIAL_TEXTURE,
    PARAM_PACK(G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 16),
    WHT_Tex,

    NULL,
    InGame_CanvasLoop,
};

