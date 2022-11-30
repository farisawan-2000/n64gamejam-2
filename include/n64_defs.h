#pragma once
#include <PR/gt.h>
#include "engine2639/material.h"


#define SCREEN_WD   320
#define SCREEN_HT   240
#define SCREEN_WIDTH SCREEN_WD
#define SCREEN_HEIGHT SCREEN_HT

#define RDPFIFO_SIZE    (8*1024/sizeof(u64))
#define GLIST_LEN       2048

#define SP_BOOT_UCODE_SIZE 0x00d0

#define NUM_PI_MSGS 8
#define STACKSIZE 0x2000

#define STATIC_SEGMENT  1
#define CFB_SEGMENT     2
#define CFB_ADDRESS     0x80200000
#define RSPBUF_ADDRESS  0x802a0000

#ifdef _LANGUAGE_C
extern  OSMesgQueue piMessageQ;
extern  OSMesgQueue siMessageQ;
extern  OSMesgQueue dmaMessageQ;
extern  OSIoMesg dmaIOMessageBuf;
extern  OSMesgQueue rspMessageQ;
extern  OSMesgQueue rdpMessageQ;
extern  OSMesgQueue retraceMessageQ;
extern  OSContStatus contStatus[MAXCONTROLLERS];
extern  OSContPad _controllers_internal[MAXCONTROLLERS];
extern  u8 contExist;

extern  u16 system_cfb[3][SCREEN_WD*SCREEN_HT];
extern  u16 zbuffer[SCREEN_WD*SCREEN_HT];
#define GFX_SIZE 65536
extern  u16 gfxAlloc[3][GFX_SIZE];
extern  u64 system_rdpfifo[];
extern  u64 system_rspyield[];

#define A_COUNT(a) (sizeof((a)) / sizeof((a[0])))

typedef struct {
    Mtx projection;
    Mtx viewing;
    Mtx VP;
    Mtx identity;

    float projectionF[4][4];
    float viewingF[4][4];
    float identityF[4][4];

    gtGfx turboGfxBuffer[2048];
} GameGFXState;
extern GameGFXState dynamic;

typedef struct {
  union {
    f32 x;
    f32 roll;
  };
  union {
    f32 y;
    f32 pitch;
  };
  union {
    f32 z;
    f32 yaw;
  };
} Vector;

typedef struct Object2639 {
    Vector move;
    Vector rotate;
    Vector scale;

    // modelList[0] has the only transform in this chain
    //  also sentinel terminated lists are cringe
    u32 segmentCount;
    gtGfx *modelList;

    enum Material matType;
    // general purpose, might just be a texture pointer and params
    union{
        u32 matParamWord;
        // struct {
        //     u8 fmt;
        //     u8 siz;
        //     u8 wd;
        //     u8 ht;
        // } matParamTexProps;
    };
    volatile void *matPtr;

    void (*init)(struct Object2639 *o);
    void (*loop)(struct Object2639 *o);
} Object2639;
#define PARAM_PACK(fm, sz, w, h) \
    (fm << 24) | \
    (sz << 16) | \
    (w << 8) | \
    (h)

#define ALIGN64(x) (((x) + 0x40) & ~0x3F)
#define ALIGN16(x) (((x) + 0x10) & ~0xF)
#define ALIGN8(x) (((x) + 0x8) & ~7)
#define ALIGN4(x) (((x) + 0x4) & ~3)


enum T3DSegments {
    T3D_SEG_MATERIAL = 1,
    T3D_SEG_LEVEL,
    T3D_SEG_TEXTURE,
    T3D_SEG_GFX,
};

#define ALIGNED16 __attribute__((aligned(16)))
#define ALIGNED(x) __attribute__((aligned((x))))
#define TEX __attribute__ ((section ("TEXTURE")))
#include "game/textures.h"
typedef float Mtx4[4][4];

extern gtGfx *gTurboGfxPtr;

/*
 *  Print macro for DEBUG
 */
#ifdef  DEBUG
#  define   osSyncPrintf    osSyncPrintf
#else
#  define   osSyncPrintf    if (0) osSyncPrintf
#endif

#define EXTERN_OBJ(o) extern Object2639 o ## _Obj;
#define OBJ(o) o ## _Obj

#define OFUN(x) extern void (x)(Object2639 *);

#include <ps1.h>
void TMESH_Draw(TMESH *mesh, int index[], u64 *texture);

#endif  /* _LANGUAGE_C */
