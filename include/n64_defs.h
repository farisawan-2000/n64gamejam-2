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
#define CFB_ADDRESS     0x80300000
#define RSPBUF_ADDRESS  0x803a0000

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

extern  u16 system_cfb[2][SCREEN_WD*SCREEN_HT];
extern  u16 zbuffer[SCREEN_WD*SCREEN_HT];
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

    // gtState objState[512];


    gtGfx turboGfxBuffer[512];

    Gfx glist[GLIST_LEN];
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
        struct {
            u8 fmt;
            u8 siz;
            u8 wd;
            u8 ht;
        } matParamTexProps;
    };
    void *matPtr;

    void (*init)(struct Object2639 *o);
    void (*loop)(struct Object2639 *o);
} Object2639;

#define ALIGN16(x) (((x) + 0xF) & -0x10)
#define ALIGN8(x) (((x) + 7) & -8)
#define ALIGN4(x) (((x) + 3) & -4)


enum T3DSegments {
    T3D_SEG_MATERIAL = 1,
    T3D_SEG_LEVEL,

};

#define ALIGN16(x) (((x) + 0xF) & -0x10)
#define ALIGN8(x) (((x) + 7) & -8)
#define ALIGN4(x) (((x) + 3) & -4)

#define ALIGNED16 __attribute__((aligned(16)))

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

#endif  /* _LANGUAGE_C */
