#include <ultra64.h>
#include <gbi.h>
#include <PR/gt.h>
#include "n64_defs.h"
#include "gtHelpers.h"

extern Vtx blok_Cube_mesh_vtx_0[57];
extern gtTriN test64_tris[] __attribute__((aligned(8)));
extern gtGfx test64_Gfx;
extern gtState test64_State;
extern u64 superTex[];

extern void obj_rotate(Object2639*);

Object2639 test64_Obj = {
    {0, -40, -150},
    {0, 0, 0},
    {0.25, 0.25, 0.25},

    1,
    &test64_Gfx,

    MATERIAL_TEXTURE,
    {G_IM_FMT_RGBA, G_IM_SIZ_16b, 64, 32},
    superTex,

    NULL,
    obj_rotate,

};

u64 superTex[] = {
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7ed73ec6fedf7e, 
    0xdf7ec6fed73edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7ed73e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xe77ecf3eae7ad73e, 
    0xd73eae7acf3ee77e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xd73edf7edf7edf7e, 
    0xdf7edf7ecf3ecefe, 0xcefecf3ed73ed73e, 0xdf7edf7edf7edf7e, 0xe77ee77edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7ec6fe9e38c6fe, 
    0xc6fe9e38c6fedf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7ee77ee77e, 0xdf7edf7edf7edf7e, 0xd73ed73ecf3ecefe, 0xcefecf3edf7edf7e, 
    0xdf7ed73ec6febebc, 0xb67ab6bcb6bcb6bc, 0xb6bcb6bcbebcc6fc, 0xcf3ed77edf7ee77e, 0xe77edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7eb6bc8db6bebc, 
    0xbebc8db6b6bcdf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7ee77e, 0xe77edf7ed77ecf3e, 0xc6fcbebcb6bcb6bc, 0xb6bcb6bcb6bcb67a, 0xbebcc6fed73edf7e, 
    0xdf7ec6feb6bca63a, 0x95f895f68db68574, 0x85748574857485b6, 0x95f6a63ab6bcc6fe, 0xd73ee77ee77ee77e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7eae7a7d74ae7a, 
    0xae7a7d74ae7adf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xe77ee77ee77ed73e, 0xc6feb6bca63a95f6, 0x85b6857485748574, 0x85748db695f695f8, 0xa63ab6bcc6fedf7e, 
    0xcf3eb6bca6388db6, 0x75326cf15c6f4c2b, 0x43eb43eb43eb43eb, 0x4c2d546d64af7532, 0x85b6a638bebcd73e, 0xdf7ee77ee77ee77e, 0xdf7edf7edf7edf7e, 0xd73ea63875329e38, 
    0x9e387532a638d73e, 0xdf7edf7edf7edf7e, 0xe77ee77ee77edf7e, 0xd73ebebca63885b6, 0x753264af546d4c2d, 0x43eb43eb43eb43eb, 0x4c2b5c6f6cf17532, 0x8db6a638b6bccf3e, 
    0xc6feae7a95f88574, 0x6cf1546f43eb3367, 0x3367336733673367, 0x2b272b252b252b27, 0x33673ba94c2d6cf2, 0x95b6ae7ac6fcd73e, 0xdf7ee77ee77edf7e, 0xc6fe95f664b18db6, 
    0x8db664b195f6c6fe, 0xdf7ee77ee77edf7e, 0xd73ec6fcae7a95b6, 0x6cf24c2d3ba93367, 0x2b272b252b252b27, 0x3367336733673367, 0x336743eb546f6cf1, 0x857495f8ae7ac6fe, 
    0xc6feb67aa6388db6, 0x753364b14c2d3ba9, 0x3ba93ba93b693367, 0x336733672b252b25, 0x2b252b252b253367, 0x43eb546d6cf08574, 0x95f8ae7abebcb6bc, 0xa67a8574546f7d33, 
    0x7d33546f8574a67a, 0xb6bcbebcae7a95f8, 0x85746cf0546d43eb, 0x33672b252b252b25, 0x2b252b2533673367, 0x33673b693ba93ba9, 0x3ba94c2d64b17533, 0x8db6a638b67ac6fe, 
    0xc6febebcae7a9e38, 0x8db67d3364b143eb, 0x3ba93ba93ba93ba9, 0x3b67336733673367, 0x33672b252b252b67, 0x2b672b6733a93beb, 0x4c2d546f64f17533, 0x6cf35caf43eb64b1, 
    0x64b143eb5caf6cf3, 0x753364f1546f4c2d, 0x3beb33a92b672b67, 0x2b672b252b253367, 0x3367336733673b67, 0x3ba93ba93ba93ba9, 0x43eb64b17d338db6, 0x9e38ae7abebcc6fe, 
    0xcf3ec6febefcb67a, 0x9e388db6753364b1, 0x43eb3ba93ba93ba9, 0x3ba93ba933673367, 0x3367336733691a1b, 0x090f090f115111d7, 0x1a9f33273bab3beb, 0x43eb3ba9336743a9, 
    0x43a933673ba943eb, 0x3beb3bab33271a9f, 0x11d71151090f090f, 0x1a1b336933673367, 0x336733673ba93ba9, 0x3ba93ba93ba943eb, 0x64b175338db69e38, 0xb67abefcc6fecf3e, 
    0xd73ecf3ecefebefc, 0xb67ca63a95f685b4, 0x6cf34c2b43eb43eb, 0x3ba93ba93ba93ba9, 0x3b693ba91a1b0001, 0x0001000100030005, 0x0001008711d72ae3, 0x33a933672b274beb, 
    0x4beb2b27336733a9, 0x2ae311d700870001, 0x0005000300010001, 0x00011a1b3ba93b69, 0x3ba93ba93ba93ba9, 0x43eb43eb4c2b6cf3, 0x85b495f6a63ab67c, 0xbefccefecf3ed73e, 
    0xd73ecf3ecf3ecefe, 0xc6febefcb6bcae7a, 0xa63a8db64c2d43eb, 0x43eb43eb43a93ba9, 0x3beb2b2300030001, 0x000700e90b7d0b3d, 0x00e7000500010047, 0x3b6743eb4c2bb67a, 
    0xb67a4c2b43eb3b67, 0x00470001000500e7, 0x0b3d0b7d00e90007, 0x000100032b233beb, 0x3ba943a943eb43eb, 0x43eb4c2d8db6a63a, 0xae7ab6bcbefcc6fe, 0xcefecf3ecf3ed73e, 
    0xcf3ed73ed73ed73e, 0xd73ed73ecf3ec6fe, 0xc6febefe95f84c2d, 0x43eb4beb43eb43eb, 0x442d19d700010001, 0x00af023f66bf667f, 0x023f00a700010001, 0x2219442d7d74e7be, 
    0xe7be7d74442d2219, 0x0001000100a7023f, 0x667f66bf023f00af, 0x0001000119d7442d, 0x43eb43eb4beb43eb, 0x4c2d95f8befec6fe, 0xc6fecf3ed73ed73e, 0xd73ed73ed73ecf3e, 
    0xd73edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7ed77edf7eb67a, 0x5c6f43eb4beb4c2b, 0x43ed090f00010057, 0x013f023f4dff4dff, 0x023f013700030001, 0x090f4c6fc6fce7be, 
    0xe7bec6fc4c6f090f, 0x000100030137023f, 0x4dff4dff023f013f, 0x00570001090f43ed, 0x4c2b4beb43eb5c6f, 0xb67adf7ed77edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7ed73e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7eefbe, 0xc6fc542d43eb4c2d, 0x43e90045000100a5, 0x017f01bf033f02ff, 0x01bf017f000d0001, 0x004795b4e7bedf7e, 
    0xdf7ee7be95b40047, 0x0001000d017f01bf, 0x02ff033f01bf017f, 0x00a50001004543e9, 0x4c2d43eb542dc6fc, 0xefbedf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xe7bec6fc74f04c2d, 0x3ba70003000100a9, 0x017f017f01bf01bf, 0x017f017f00170001, 0x0845cefce7bedf7e, 
    0xdf7ee7becefc0845, 0x00010017017f017f, 0x01bf01bf017f017f, 0x00a9000100033ba7, 0x4c2d74f0c6fce7be, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7ee7bedf7ebebc, 0x8d740045000100a7, 0x013f017f017f017f, 0x017f013f00110001, 0x0885d6fce7bedf7e, 
    0xdf7ee7bed6fc0885, 0x00010011013f017f, 0x017f017f017f013f, 0x00a7000100458d74, 0xbebcdf7ee7bedf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7eefbe, 0xdf7e19510001005b, 0x013f013f013f013f, 0x013f00f900050001, 0x110fd73ee77edf7e, 
    0xdf7ee77ed73e110f, 0x0001000500f9013f, 0x013f013f013f013f, 0x005b00011951df7e, 0xefbedf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7eefbe, 0xdf7e19510001005b, 0x013f013f013f013f, 0x013f00f900050001, 0x110fd73ee77edf7e, 
    0xdf7ee77ed73e110f, 0x0001000500f9013f, 0x013f013f013f013f, 0x005b00011951df7e, 0xefbedf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7ee77e, 0xdf7e2a1700010007, 0x00b5013f013f013f, 0x013f00ad00010001, 0x3259dfbee77edf7e, 
    0xdf7ee77edfbe3259, 0x0001000100ad013f, 0x013f013f013f00b5, 0x000700012a17df7e, 0xe77edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7ee77e, 0xdf7e3b2300010001, 0x000d00b500ff00ff, 0x00b5000d00010001, 0x53e9e7bedf7edf7e, 
    0xdf7edf7ee7be53e9, 0x00010001000d00b5, 0x00ff00ff00b5000d, 0x000100013b23df7e, 0xe77edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7ee77e, 0xd73e4c2d08cd0001, 0x0001000500150015, 0x000500010001010d, 0x85b6e7bedf7edf7e, 
    0xdf7edf7ee7be85b6, 0x010d000100010005, 0x0015001500050001, 0x000108cd4c2dd73e, 0xe77edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7ee77e, 0xdf7e64b122e30045, 0x0001000100010001, 0x0001000108cb3367, 0xb6bce7bedf7edf7e, 
    0xdf7edf7ee7beb6bc, 0x336708cb00010001, 0x0001000100010001, 0x004522e364b1df7e, 0xe77edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xe7bea63633a92ae3, 0x08cd000100010001, 0x0001115133697d74, 0xe77edf7edf7edf7e, 
    0xdf7edf7edf7ee77e, 0x7d74336911510001, 0x00010001000108cd, 0x2ae333a9a636e7be, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xe77edf7e64af3367, 0x3ba922e119d919d9, 0x22a13369542dd73e, 0xe77edf7edf7edf7e, 
    0xdf7edf7edf7ee77e, 0xd73e542d336922a1, 0x19d919d922e13ba9, 0x336764afdf7ee77e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7ee7bed73e4c2b, 0x2b25336733a93369, 0x2b674c2dc6fce7be, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xe7bec6fc4c2d2b67, 0x336933a933672b25, 0x4c2bd73ee7bedf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7ee7bec6fc, 0x7d32546d4beb5c6d, 0x8d74c6fce7bedf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7ee7bec6fc8d74, 0x5c6d4beb546d7d32, 0xc6fce7bedf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7ee7be, 0xe7bedf7ed73edf7e, 0xefbee7bedf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7ee7beefbe, 0xdf7ed73edf7ee7be, 0xe7bedf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7ee7be, 0xe7bedf7ed73edf7e, 0xefbee7bedf7edf7e, 0xdf7edf7edf7edf7e, 
    0xdf7edf7edf7edf7e, 0xdf7edf7ee7beefbe, 0xdf7ed73edf7ee7be, 0xe7bedf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 0xdf7edf7edf7edf7e, 
    
};

Vtx texturetru_Cube_mesh_vtx_0[60] = {
        {{{-400, -100, 400},0, {2032, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
        {{{400, -100, 400},0, {2032, 323},{0x0, 0xA6, 0x5A, 0xFF}}},
        {{{400, 100, 400},0, {662, 323},{0x1F, 0x32, 0x71, 0xFF}}},
        {{{-400, 100, 400},0, {662, 1008},{0xAA, 0x26, 0x56, 0xFF}}},
        {{{0, 199, 400},0, {-16, 665},{0x0, 0x31, 0x75, 0xFF}}},
        {{{200, 151, 400},0, {309, 494},{0x1B, 0x32, 0x72, 0xFF}}},
        {{{-200, 151, 400},0, {309, 837},{0xE5, 0x32, 0x72, 0xFF}}},
        {{{-400, -100, -400},0, {-16, 1008},{0xB7, 0xB7, 0xB7, 0xFF}}},
        {{{-400, -100, 400},0, {1354, 1008},{0xB7, 0xB7, 0x49, 0xFF}}},
        {{{-400, 100, 400},0, {1354, 323},{0xAA, 0x26, 0x56, 0xFF}}},
        {{{-400, 100, -400},0, {-16, 323},{0xAA, 0x26, 0xAA, 0xFF}}},
        {{{-400, 199, 0},0, {669, -16},{0x8B, 0x31, 0x0, 0xFF}}},
        {{{-400, 151, 200},0, {1012, 147},{0x8E, 0x32, 0x1B, 0xFF}}},
        {{{-400, 151, -200},0, {327, 147},{0x8E, 0x32, 0xE5, 0xFF}}},
        {{{-400, -100, -400},0, {-16, 1008},{0xB7, 0xB7, 0xB7, 0xFF}}},
        {{{400, -100, -400},0, {2032, 1008},{0x0, 0xA6, 0xA6, 0xFF}}},
        {{{400, -100, 400},0, {2032, -16},{0x0, 0xA6, 0x5A, 0xFF}}},
        {{{-400, -100, 400},0, {-16, -16},{0xB7, 0xB7, 0x49, 0xFF}}},
        {{{400, -100, -400},0, {2032, 1008},{0x0, 0xA6, 0xA6, 0xFF}}},
        {{{-400, -100, -400},0, {2032, 323},{0xB7, 0xB7, 0xB7, 0xFF}}},
        {{{-400, 100, -400},0, {662, 323},{0xAA, 0x26, 0xAA, 0xFF}}},
        {{{400, 100, -400},0, {662, 1008},{0x1F, 0x32, 0x8F, 0xFF}}},
        {{{0, 199, -400},0, {-16, 665},{0x0, 0x31, 0x8B, 0xFF}}},
        {{{-200, 151, -400},0, {309, 494},{0xE5, 0x32, 0x8E, 0xFF}}},
        {{{200, 151, -400},0, {309, 837},{0x1B, 0x32, 0x8E, 0xFF}}},
        {{{0, 199, -400},0, {2032, 73},{0x0, 0x31, 0x8B, 0xFF}}},
        {{{-200, 151, -400},0, {2325, 169},{0xE5, 0x32, 0x8E, 0xFF}}},
        {{{-200, 351, -200},0, {2608, 243},{0xC0, 0x59, 0xC0, 0xFF}}},
        {{{0, 463, -200},0, {1008, 196},{0x0, 0x61, 0xAF, 0xFF}}},
        {{{200, 151, -400},0, {1739, 169},{0x1B, 0x32, 0x8E, 0xFF}}},
        {{{200, 351, -200},0, {1456, 243},{0x40, 0x59, 0xC0, 0xFF}}},
        {{{0, 615, 0},0, {1008, 496},{0x0, 0x7F, 0x0, 0xFF}}},
        {{{-200, 463, 0},0, {708, 496},{0xAF, 0x61, 0x0, 0xFF}}},
        {{{-200, 351, -200},0, {560, 243},{0xC0, 0x59, 0xC0, 0xFF}}},
        {{{-400, 199, 0},0, {407, 496},{0x8B, 0x31, 0x0, 0xFF}}},
        {{{-400, 151, -200},0, {372, 354},{0x8E, 0x32, 0xE5, 0xFF}}},
        {{{-200, 151, -400},0, {277, 169},{0xE5, 0x32, 0x8E, 0xFF}}},
        {{{-400, 100, -400},0, {338, 260},{0xAA, 0x26, 0xAA, 0xFF}}},
        {{{-400, 151, 200},0, {372, 638},{0x8E, 0x32, 0x1B, 0xFF}}},
        {{{-200, 351, 200},0, {560, 749},{0xC0, 0x59, 0x40, 0xFF}}},
        {{{-400, 100, 400},0, {338, 732},{0xAA, 0x26, 0x56, 0xFF}}},
        {{{-200, 151, 400},0, {277, 823},{0xE5, 0x32, 0x72, 0xFF}}},
        {{{0, 463, 200},0, {1008, 796},{0x0, 0x61, 0x51, 0xFF}}},
        {{{0, 199, 400},0, {-16, 919},{0x0, 0x31, 0x75, 0xFF}}},
        {{{200, 463, 0},0, {1308, 496},{0x51, 0x61, 0x0, 0xFF}}},
        {{{400, 151, -200},0, {1644, 354},{0x4C, 0x5A, 0xD0, 0xFF}}},
        {{{400, 199, 0},0, {1609, 496},{0x60, 0x53, 0x0, 0xFF}}},
        {{{200, 351, 200},0, {1456, 749},{0x40, 0x59, 0x40, 0xFF}}},
        {{{0, 199, 400},0, {2032, 919},{0x0, 0x31, 0x75, 0xFF}}},
        {{{200, 151, 400},0, {1739, 823},{0x1B, 0x32, 0x72, 0xFF}}},
        {{{400, 151, 200},0, {1644, 638},{0x4C, 0x5A, 0x30, 0xFF}}},
        {{{400, 100, 400},0, {1678, 732},{0x1F, 0x32, 0x71, 0xFF}}},
        {{{400, 100, -400},0, {1678, 260},{0x1F, 0x32, 0x8F, 0xFF}}},
        {{{400, -100, 400},0, {-102, 1008},{0x7F, 0x0, 0x0, 0xFF}}},
        {{{400, -100, -400},0, {2139, 1008},{0x7F, 0x0, 0x0, 0xFF}}},
        {{{400, 100, -400},0, {2139, 323},{0x7F, 0x0, 0x0, 0xFF}}},
        {{{400, 100, 400},0, {-102, 323},{0x7F, 0x0, 0x0, 0xFF}}},
        {{{400, 199, 0},0, {1019, -16},{0x7F, 0x0, 0x0, 0xFF}}},
        {{{400, 151, -200},0, {1579, 147},{0x7F, 0x0, 0x0, 0xFF}}},
        {{{400, 151, 200},0, {458, 147},{0x7F, 0x0, 0x0, 0xFF}}},
};
gtTriN test64_tris_0[] __attribute__((aligned(8))) = {
    {0, 1, 2, 0}, {3, 0, 2, 0},
    {2, 4, 3, 0}, {2, 5, 4, 0},
    {4, 6, 3, 0}, {7, 8, 9, 0},
    {10, 7, 9, 0}, {9, 11, 10, 0},
    {9, 12, 11, 0}, {11, 13, 10, 0},
    {14, 15, 16, 0}, {14, 16, 17, 0},
    {18, 19, 20, 0}, {21, 18, 20, 0},
    {20, 22, 21, 0}, {20, 23, 22, 0},
    {22, 24, 21, 0}, {25, 26, 27, 0},
    {25, 27, 28, 0}, {29, 25, 28, 0},
    {29, 28, 30, 0}, {30, 28, 31, 0},
    {28, 32, 31, 0}, {28, 33, 32, 0},
    {33, 34, 32, 0}, {33, 35, 34, 0},
    {36, 35, 33, 0}, {36, 37, 35, 0},
    {32, 34, 38, 0}, {32, 38, 39, 0},
    {39, 38, 40, 0}, {39, 40, 41, 0},
    {42, 39, 41, 0}, {42, 41, 43, 0},
    {31, 39, 42, 0}, {31, 32, 39, 0},
    {44, 31, 42, 0}, {30, 31, 44, 0},
    {45, 30, 44, 0}, {45, 44, 46, 0},
    {46, 44, 47, 0}, {44, 42, 47, 0},
    {47, 42, 48, 0}, {47, 48, 49, 0},
    {50, 47, 49, 0}, {50, 49, 51, 0},
    {46, 47, 50, 0}, {52, 29, 30, 0},
    {52, 30, 45, 0}, {53, 54, 55, 0},
    {56, 53, 55, 0}, {55, 57, 56, 0},
    {55, 58, 57, 0}, {57, 59, 56, 0},
};
gtState test64_State = {
    (GT_CULL_BACK | GT_SHADING_SMOOTH | GT_TEXTURE | GT_ZBUFFER), // renderState 0
    0x0, // textureState 4
    60, // vtxCount  8
    0, // vtxV0 9
    54, // triCount a
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

gtGfx test64_Gfx = {
    NULL,
    &test64_State,
    texturetru_Cube_mesh_vtx_0,
    test64_tris_0,
};
