#include <ultra64.h>
#include <PR/gt.h>
#include "n64_defs.h"

extern Gfx clearCfb[];

OSTask tlist = {
    M_GFXTASK,                             /* task type                */
    OS_TASK_DP_WAIT | OS_TASK_LOADABLE,    /* task flags               */
    (u64 *) &rspbootTextStart,             /* boot ucode ptr           */
    SP_BOOT_UCODE_SIZE,                    /* boot ucode size          */
    (u64 *) &gspTurbo3D_fifoTextStart,     /* ucode ptr                */
    SP_UCODE_SIZE,                         /* ucode size               */
    (u64 *) &gspTurbo3D_fifoDataStart,     /* ucode data ptr           */
    SP_UCODE_DATA_SIZE,                    /* ucode data size          */
    NULL,                                  /* dram stack      (unused) */
    0,                                     /* dram stack size (unused) */
    (u64 *) system_rdpfifo,                /* fifo buffer top          */
    (u64 *) system_rdpfifo + RDPFIFO_SIZE, /* fifo buffer bottom       */
    NULL,                                  /* data ptr      (set later) */
    NULL,                                  /* data size     (unneeded) */
    (u64 *) system_rspyield,               /* yield data ptr           */
    OS_YIELD_DATA_SIZE,                    /* yield data size          */
};

Gfx glist[GLIST_LEN];

u32 gTimer = 0;

u16 gRenderedFramebuffer = 0;

Gfx finalDP[] =
{               /* rdpCmds */
    gsDPFullSync(),
    gsDPEndDisplayList()
};

gtState dpFinalObj =
{
    0x0,    // renderState 0
    0x0,    // textureState 4
    0,      // vtxCount  8
    0,      // vtxV0 9
    0,      // triCount a
    0x0,    // pad1 b
    (Gfx *)&finalDP, // c
    gsDPClearOtherMode(),               // 10
    {   /* integer portion: */
    0x00010000, 0x00000000,         /* transform */
    0x00000001, 0x00000000,
    0x00000000, 0x00010000,
    0x00000000, 0x00000001,
    /* fractional portion: */
    0x00000000, 0x00000000,
    0x00000000, 0x00000000,
    0x00000000, 0x00000000,
    0x00000000, 0x00000000,
    }
};

Gfx dpGlobDPBlock[] = {
    gsDPPipeSync(),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),

    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, system_cfb),
    gsDPSetFillColor(
        (GPACK_RGBA5551(64, 0, 64, 1) << 16 | GPACK_RGBA5551(64, 0, 64, 1))),
    gsDPFillRectangle(0, 0, SCREEN_WD, SCREEN_HT - 1),

    gsDPPipeSync(),
    gsDPEndDisplayList(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
    gsDPNoOp(),
};

gtGlobState dpGlobObjState = {0xffff, /* perspNorm */
                              0x0,
                              0x0,                  /* pad0, pad1 */
                              gsDPClearOtherMode(), /* rdpOthermode */
                              {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
                               0x0, /* segBases */
                               0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0},
                              {
                                  SCREEN_WD * 2,
                                  SCREEN_HT * 2,
                                  G_MAXZ / 2,
                                  0, /* viewport */
                                  SCREEN_WD * 2,
                                  SCREEN_HT * 2,
                                  G_MAXZ / 2,
                                  0,
                              },
                              &(dpGlobDPBlock[0])};
gtGlobState *ggsp = &(dpGlobObjState);

u64 dram_stack[SP_DRAM_STACK_SIZE64]; /* used for matrix stack */

gtGfx *gtlistp;
Gfx *glistp; /* global for test case procs */

typedef struct {
  Mtx   AA;
  Mtx   BB;

  Mtx   projection;

  Mtx   RotationX;
  Mtx   RotationY;

  Mtx   Translation;

  Mtx   TranslateIn;
  Mtx   TranslateOut;
  
#if 0
  Mtx   modeling1[MAXBLOCKS+1];
  Mtx   modeling2[MAXBLOCKS+1];
  Mtx   modeling3[MAXBLOCKS+1];
  Mtx   modeling4[MAXBLOCKS+1];
#endif

  gtState   objState[216+1];

  Mtx   viewing;
  Mtx   identity;

  gtGfx gtlist[512];

  Gfx   glist[GLIST_LEN];
} Dynamic;

Dynamic dynamic;
Dynamic *dynamicp;

void Main(void *arg) {
    Gfx *gp;


    while (1) {
        osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);

        gtlistp->obj.gstatep = (gtGlobState *)NULL;
        gtlistp->obj.statep = &dpFinalObj;
        gtlistp->obj.vtxp = (Vtx *)NULL;
        gtlistp->obj.trip = (gtTriN *)NULL;
        gtlistp++;

        gtlistp->obj.gstatep = (gtGlobState *)NULL;
        gtlistp->obj.statep = (gtState *)NULL; /* signal end of object list */
        gtlistp->obj.vtxp = (Vtx *)NULL;
        gtlistp->obj.trip = (gtTriN *)NULL;
        gtlistp++;

        tlist.t.data_size = (u32)((gtlistp - dynamicp->gtlist) * sizeof(gtGfx));

        /* Write back dirty cache lines that need to be read by the RCP */
        osWritebackDCache(&dynamic, sizeof(dynamic));
        osSpTaskStart(&tlist);

        osRecvMesg(&rspMessageQ, NULL, OS_MESG_BLOCK);
        osRecvMesg(&rdpMessageQ, NULL, OS_MESG_BLOCK);

        osViSwapBuffer(system_cfb[gRenderedFramebuffer]);
        gRenderedFramebuffer ^= 1;
        gTimer++;
    }
}

/*======== End of main.c ========*/
