// The material allocator; use this for assigning both static and dynamic materials

#include <ultra64.h>
#include <PR/gt.h>
#include "n64_defs.h"

#define static
// 64kb buffer so that we can segment
static Gfx sT3DMatBuffer[8192];
static Gfx *sT3DMatGfxPtr = &sT3DMatBuffer[0];

void MatAlloc_Init(gtGlobState *g) {
    g->sp.segBases[T3D_SEG_MATERIAL] = (u32)&sT3DMatBuffer[0];
    sT3DMatGfxPtr = &sT3DMatBuffer[0];
}

u32 MatAlloc_AllocTextureDL_RGBA16_64x32(u32 *texture) {
    u32 ret = (T3D_SEG_MATERIAL << 24) + ((u32)sT3DMatGfxPtr - (u32)sT3DMatBuffer);

    gDPPipeSync(sT3DMatGfxPtr++);
    gDPSetCombineLERP(sT3DMatGfxPtr++,
        TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT,
        TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT
    );
    gDPTileSync(sT3DMatGfxPtr++);
    gDPSetTextureImage(sT3DMatGfxPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 1, texture);
    gDPSetTile(sT3DMatGfxPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b_LOAD_BLOCK, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0);
    gDPLoadSync(sT3DMatGfxPtr++);
    gDPLoadBlock(sT3DMatGfxPtr++, 7, 0, 0, 2047, 128);
    gDPPipeSync(sT3DMatGfxPtr++);
    gDPSetTile(sT3DMatGfxPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0);
    gDPSetTileSize(sT3DMatGfxPtr++, 0, 0, 0, 252, 124);
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);

    sT3DMatGfxPtr = ALIGN16((u32)sT3DMatGfxPtr);

    return ret;
}

