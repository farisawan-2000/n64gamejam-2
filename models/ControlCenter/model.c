#include <ultra64.h>
#include <gbi.h>
#include <PR/gt.h>
#include "n64_defs.h"
#include "gtHelpers.h"
extern Object2639 ControlCenter_Obj;
Object2639 *ControlCenter_objp = &ControlCenter_Obj;
Vtx control_Cube_mesh_vtx_0[24] = {
	{{{161, -364, -1400},0, {1264, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{161, -364, 1400},0, {1264, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-161, -364, 1400},0, {1776, 240},{0x0, 0x81, 0x0, 0xFF}}},
	{{{-161, -364, -1400},0, {1776, 496},{0x0, 0x81, 0x0, 0xFF}}},
	{{{161, 585, 1400},0, {-16, 7},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-161, 364, 1400},0, {1950, -16},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-161, -364, 1400},0, {1075, 429},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{161, -364, 1400},0, {1047, 453},{0x0, 0x0, 0x7F, 0xFF}}},
	{{{-161, 364, 1400},0, {8157, -1611},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-161, 364, -1400},0, {-6141, -1611},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-161, -364, -1400},0, {-6141, 3307},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-161, -364, 1400},0, {8157, 3307},{0x81, 0x0, 0x0, 0xFF}}},
	{{{-161, 364, -1400},0, {-6141, -1611},{0xB8, 0x69, 0x0, 0xFF}}},
	{{{-161, 364, 1400},0, {8157, -1611},{0xB8, 0x69, 0x0, 0xFF}}},
	{{{161, 585, 1400},0, {8157, -3106},{0xB8, 0x69, 0x0, 0xFF}}},
	{{{161, 585, -1400},0, {-6141, -3106},{0xB8, 0x69, 0x0, 0xFF}}},
	{{{161, 585, -1400},0, {135, 810},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{161, 585, 1400},0, {-16, 7},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{161, -364, 1400},0, {1047, 453},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{161, -364, -1400},0, {1098, 466},{0x7F, 0x0, 0x0, 0xFF}}},
	{{{-161, 364, -1400},0, {1950, 1008},{0x0, 0x0, 0x81, 0xFF}}},
	{{{161, 585, -1400},0, {135, 810},{0x0, 0x0, 0x81, 0xFF}}},
	{{{161, -364, -1400},0, {1098, 466},{0x0, 0x0, 0x81, 0xFF}}},
	{{{-161, -364, -1400},0, {1096, 446},{0x0, 0x0, 0x81, 0xFF}}},
};
gtTriN ControlCenter_tris_0[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {0, 2, 3, 0},
    {4, 5, 6, 0}, {4, 6, 7, 0},
    {8, 9, 10, 0}, {8, 10, 11, 0},
    {12, 13, 14, 0}, {12, 14, 15, 0},
    {16, 17, 18, 0}, {16, 18, 19, 0},
    {20, 21, 22, 0}, {20, 22, 23, 0},
};
gtState ControlCenter_State = {
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


gtGfx ControlCenter_GfxList[] = {
    {
        NULL,
        (gtState *)&ControlCenter_State,
        control_Cube_mesh_vtx_0+0,
        ControlCenter_tris_0,
    },
};


OFUN(InGame_Loop);
Object2639 ControlCenter_Obj = {
    {0, 0, 1000},
    {0, -90, 0},
    {0.25, 0.25, 0.25},

    1, // gfxlist count
    &ControlCenter_GfxList, // gfxlist name

    MATERIAL_TEXTURE,
    PARAM_PACK(G_IM_FMT_I, G_IM_SIZ_8b, 64, 32),
    control_steel_i8,

    NULL,
    InGame_Loop,
};

