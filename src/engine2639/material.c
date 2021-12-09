// The material allocator; use this for assigning both static and dynamic materials

#include <ultra64.h>
#include <PR/gt.h>
#include "n64_defs.h"
#include "game/memory.h"

#define static
// 64kb buffer so that we can segment
static Gfx sT3DMatBuffer[8192] ALIGNED16;
static Gfx *sT3DMatGfxPtr = &sT3DMatBuffer[0];

void MatAlloc_Init(gtGlobState *g) {
    g->sp.segBases[T3D_SEG_MATERIAL] = (u32)&sT3DMatBuffer[0];
    g->sp.segBases[T3D_SEG_TEXTURE] = SEG_TEXTURES;
    sT3DMatGfxPtr = &sT3DMatBuffer[0];

    bzero(sT3DMatBuffer, sizeof sT3DMatBuffer);
}

u32 MatAlloc_AllocNoDL(u32 *texture, u32 params) {
    u32 ret = (T3D_SEG_MATERIAL << 24) + ((u32)sT3DMatGfxPtr - (u32)sT3DMatBuffer);

    u8 fmt =    (params >> 24) & 0xFF;
    u8 size =   (params >> 16) & 0xFF;
    u8 width =  (params >>  8) & 0xFF;
    u8 height = (params      ) & 0xFF;

    gDPPipeSync(sT3DMatGfxPtr++);
    gDPSetCombineLERP(sT3DMatGfxPtr++,
        0, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 1
    );

    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);

    sT3DMatGfxPtr = (Gfx*)ALIGN64((u32)sT3DMatGfxPtr);

    return ret;
}

u32 MatAlloc_AllocRedDL(u32 *texture, u32 params) {
    u32 ret = (T3D_SEG_MATERIAL << 24) + ((u32)sT3DMatGfxPtr - (u32)sT3DMatBuffer);

    u8 fmt =    (params >> 24) & 0xFF;
    u8 size =   (params >> 16) & 0xFF;
    u8 width =  (params >>  8) & 0xFF;
    u8 height = (params      ) & 0xFF;

    gDPPipeSync(sT3DMatGfxPtr++);
    gDPSetCombineLERP(sT3DMatGfxPtr++,
        0, 0, 0, ENVIRONMENT, 0, 0, 0, 1,
        0, 0, 0, ENVIRONMENT, 0, 0, 0, 1
    );
    gDPSetEnvColor(sT3DMatGfxPtr++,
        255, 0,0,255
    );

    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);

    sT3DMatGfxPtr = (Gfx*)ALIGN64((u32)sT3DMatGfxPtr);

    return ret;
}

u32 MatAlloc_AllocTextureDL(u32 *texture, u32 params) {
    u32 ret = (T3D_SEG_MATERIAL << 24) + ((u32)sT3DMatGfxPtr - (u32)sT3DMatBuffer);

    u8 fmt =    (params >> 24) & 0xFF;
    u8 size =   (params >> 16) & 0xFF;
    u8 width =  (params >>  8) & 0xFF;
    u8 height = (params      ) & 0xFF;

    gDPPipeSync(sT3DMatGfxPtr++);
    gDPSetCombineLERP(sT3DMatGfxPtr++,
        0, 0, 0, TEXEL0, 0, 0, 0, 1,
        0, 0, 0, TEXEL0, 0, 0, 0, 1
    );

    switch (size) {
        case G_IM_SIZ_8b:
            gDPLoadTextureBlock(sT3DMatGfxPtr++,
                texture,
                fmt, G_IM_SIZ_8b, width, height, 0,
                G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
            );
            break;
        case G_IM_SIZ_16b:
            gDPLoadTextureBlock(sT3DMatGfxPtr++,
                texture,
                fmt, G_IM_SIZ_16b, width, height, 0,
                G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
                G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD
            );
            break;
    }
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);

    sT3DMatGfxPtr = (Gfx*)ALIGN64((u32)sT3DMatGfxPtr);

    return ret;
    // gDPSetCombineLERP(sT3DMatGfxPtr++, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, SHADE, 0, 0, 0, 0, ENVIRONMENT);
    // gDPTileSync(sT3DMatGfxPtr++);
    // gDPSetTextureImage(sT3DMatGfxPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, texture);
    // gDPSetTile(sT3DMatGfxPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 7, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0);
    // gDPLoadSync(sT3DMatGfxPtr++);
    // gDPLoadBlock(sT3DMatGfxPtr++, 7, 0, 0, 2047, 128);
    // gDPPipeSync(sT3DMatGfxPtr++);
    // gDPSetTile(sT3DMatGfxPtr++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 16, 0, 0, 0, G_TX_WRAP | G_TX_NOMIRROR, 5, 0, G_TX_WRAP | G_TX_NOMIRROR, 6, 0);
    // gDPSetTileSize(sT3DMatGfxPtr++, 0, 0, 0, 252, 124);
}

u32 MatAlloc_AllocTextureDL_4b(u32 *texture, u32 params) {
    u32 ret = (T3D_SEG_MATERIAL << 24) + ((u32)sT3DMatGfxPtr - (u32)sT3DMatBuffer);

    u8 fmt =    (params >> 24) & 0xFF;
    u8 palette =   (params >> 16) & 0xFF;
    u8 width =  (params >>  8) & 0xFF;
    u8 height = (params      ) & 0xFF;

    gDPPipeSync(sT3DMatGfxPtr++);
    gDPSetCombineLERP(sT3DMatGfxPtr++, 0, 0, 0, 1, 0, 0, 0, TEXEL0, 0, 0, 0, 1, 0, 0, 0, TEXEL0);

    gDPLoadTextureBlock_4b(sT3DMatGfxPtr++,
        texture,
        fmt,
        width, height,
        palette,
        G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR,
        G_TX_NOMASK, G_TX_NOMASK,
        G_TX_NOLOD, G_TX_NOLOD
    );
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);
    gDPEndDisplayList(sT3DMatGfxPtr++);


    sT3DMatGfxPtr = (Gfx*)ALIGN64((u32)sT3DMatGfxPtr);
    return ret;
}

