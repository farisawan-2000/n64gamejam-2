#include <ultra64.h>
#include <PR/gt.h>
#include <PR/gu.h>
#include "n64_defs.h"
#include "gtHelpers.h"

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

Gfx finalDP[] = { /* rdpCmds */
                  gsDPFullSync(), gsDPEndDisplayList()
};

gtState dpFinalObj = { 0x0,                  // renderState 0
                       0x0,                  // textureState 4
                       0,                    // vtxCount  8
                       0,                    // vtxV0 9
                       0,                    // triCount a
                       0x0,                  // pad1 b
                       (Gfx *) &finalDP,     // c
                       gsDPClearOtherMode(), // 10
                       {
                           /* integer portion: */
                           0x00010000,
                           0x00000000, /* transform */
                           0x00000001,
                           0x00000000,
                           0x00000000,
                           0x00010000,
                           0x00000000,
                           0x00000001,
                           /* fractional portion: */
                           0x00000000,
                           0x00000000,
                           0x00000000,
                           0x00000000,
                           0x00000000,
                           0x00000000,
                           0x00000000,
                           0x00000000,
                       } };

gtState dpInitClearObj =
{
    0x0,    /* renderState */
    0x0,    /* textureState */
    0,      /* vtxCount */
    0,      /* vtxV0 */
    0,      /* triCount */
    0x0, 0x0,   /* pad1, pad2 */
    gsDPClearOtherMode(),               /* rdpOthermode */
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
    },
};

Gfx dpGlobDPBlock[] = {
    gsDPPipeSync(),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),

    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, system_cfb),
    gsDPSetFillColor((GPACK_RGBA5551(64, 64, 255, 1) << 16 | GPACK_RGBA5551(64, 64, 255, 1))),
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

gtGlobState dpGlobObjState = { 0xffff, /* perspNorm */
                               0x0,
                               0x0,                                      /* pad0, pad1 */
                               gsDPClearOtherMode(),                     /* rdpOthermode */
                               { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, /* segBases */
                                 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 },
                               {
                                   // viewport
                                   SCREEN_WD * 2,
                                   SCREEN_HT * 2,
                                   G_MAXZ / 2,
                                   0,
                                   SCREEN_WD * 2,
                                   SCREEN_HT * 2,
                                   G_MAXZ / 2,
                                   0,
                               },
                               &(dpGlobDPBlock[0]) };
gtGlobState *ggsp = &(dpGlobObjState);

u64 dram_stack[SP_DRAM_STACK_SIZE64]; /* used for matrix stack */

gtGfx *gtlistp;
Gfx *glistp; /* global for test case procs */

typedef struct {
    Mtx AA;
    Mtx BB;

    Mtx projection;

    Mtx RotationX;
    Mtx RotationY;

    Mtx Translation;

    Mtx TranslateIn;
    Mtx TranslateOut;

    gtState objState[216 + 1];

    Mtx viewing;
    Mtx identity;

    gtGfx gtlist[512];

    Gfx glist[GLIST_LEN];
} Dynamic;

Dynamic dynamic;

static void InitRsp(int clearScreen) {
    static Vp vp;
    Gfx *gptr;

    vp.vp.vscale[0] = SCREEN_WD * 2;
    vp.vp.vscale[1] = SCREEN_HT * 2;
    vp.vp.vscale[2] = G_MAXZ / 2;
    vp.vp.vscale[3] = 0;
    vp.vp.vtrans[0] = SCREEN_WD * 2;
    vp.vp.vtrans[1] = SCREEN_HT * 2;
    vp.vp.vtrans[2] = G_MAXZ / 2;
    vp.vp.vtrans[3] = 0;

    /* handle variable viewport based on screen size: */
    bcopy((char *) &(vp.vp), (char *) &(ggsp->sp.viewport), sizeof(Vp_t));

    /* init global state: */
    ggsp->sp.segBases[0] = 0x0; /* physical mapping */

    /* set rendermode and cycletype for clear object: */
    gtStateSetOthermode(&(ggsp->sp.rdpOthermode), GT_RENDERMODE, (G_RM_OPA_SURF | G_RM_OPA_SURF2));
    gtStateSetOthermode(&(ggsp->sp.rdpOthermode), GT_CYCLETYPE, G_CYC_FILL);

    gptr = (Gfx *) &(ggsp->sp.rdpCmds[0]);
    gDPPipeSync(gptr++);
    if (clearScreen) {
        gDPSetScissor(gptr++, G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT);
        gDPSetCombineMode(gptr++, G_CC_SHADE, G_CC_SHADE);
        gDPPipeSync(gptr++);
        gDPSetColorImage(gptr++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
                         system_cfb[gRenderedFramebuffer ^ 1]);
        gDPSetFillColor(gptr++,
                        (GPACK_RGBA5551(64, 64, 255, 1) << 16 | GPACK_RGBA5551(64, 64, 255, 1)));
        gDPFillRectangle(gptr++, 0, 0, SCREEN_WD, SCREEN_HT - 1);

        gDPPipeSync(gptr++);
    }
    gDPEndDisplayList(gptr++);
}

Vtx q0[5] __attribute__((aligned(16))) = {
    { -40, 40, 0, 0, 0, 0, 0xFF, 0, 0, 0xff },
    { 40, 40, 0, 0, (31 << 5), 0, 0, 0xff, 0, 0xff },
    { 40, -40, 0, 0, (31 << 5), (31 << 5), 0, 0xff, 0, 0xff },
    { -40, -40, 0, 0, 0, (31 << 5), 0xff, 0, 0, 0xff },
    { 0, 0, 0, 0, 0, 0, 0xff, 0xff, 0xff, 0xff },
};

gtTriN tris[] __attribute__((aligned(8))) = {
    {
        0,
        1,
        2,
        0,
    },
    {
        0,
        2,
        3,
        0,
    },
    {
        0,
        1,
        2,
        0,
    },
    {
        0,
        2,
        3,
        0,
    },
};

Gfx VertexColored[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(SHADE, 0, ENVIRONMENT, 0, 0, 0, 0, 1,
        SHADE, 0, ENVIRONMENT, 0, 0, 0, 0, 1),

    gsDPSetEnvColor(0, 255, 255, 255),
    gsDPEndDisplayList(),
};

gtState triangle_obj = { 0x0,                  // renderState 0
                         0x0,                  // textureState 4
                         A_COUNT(q0),          // vtxCount  8
                         0,                    // vtxV0 9
                         A_COUNT(tris),        // triCount a
                         0x0,                  // pad1 b
                         VertexColored,                 // c
                         gsDPClearOtherMode(), // 10
                         {
                             /* integer portion: */
                             0x00010000, 0x00000000,
                             0x00000001, 0x00000000,
                             0x00000000, 0x00010000,
                             0x00000000, 0x00000001,
                             /* fractional portion: */
                             0x00000000, 0x00000000,
                             0x00000000, 0x00000000,
                             0x00000000, 0x00000000,
                             0x00000000, 0x00000000,
                         } };

gtGfx thing = {
    NULL,
    &triangle_obj,
    q0,
    tris,
};

float yaw = 0;

static void SetupViewing(void) {
    guPerspective(&dynamic.projection, &(ggsp->sp.perspNorm), 33, 320.0 / 240.0,
                1, 2000, 1.0);
    guLookAt(&dynamic.viewing,
        160, 120, 400,
        0, 0, 0,
        0, 1, 0
    );
  guMtxCatL(&dynamic.viewing, &dynamic.projection, &dynamic.viewing);
}

void Main(void *arg) {
    Gfx *gp;

    Mtx Sc, Ro, Tr, Ident;

    guMtxIdent(&Ident);

    // InitRsp(1);

    while (1) {
        InitRsp(1);
        osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);

        gtlistp = &(dynamic.gtlist[0]);
        gp = &dynamic.glist;

        gtDraw(gtlistp++, ggsp, &dpInitClearObj, NULL, NULL);

        guRotateRPY(&triangle_obj.sp.transform, 0, 0, yaw++);
        gtDraw(gtlistp++, NULL, &triangle_obj, q0, tris);
        gtDraw(gtlistp++, NULL, &dpFinalObj, NULL, NULL);

        gtFinish(gtlistp++);

        tlist.t.data_size = (u32)((gtlistp - dynamic.gtlist) * sizeof(gtGfx));

        tlist.t.data_ptr = (u64 *) &(dynamic.gtlist[0]);

        //  Write back dirty cache lines that need to be read by the RCP 
        osWritebackDCache(&dynamic, sizeof(dynamic));
        osSpTaskStart(&tlist);

        osRecvMesg(&rspMessageQ, NULL, OS_MESG_BLOCK);
        osRecvMesg(&rdpMessageQ, NULL, OS_MESG_BLOCK);


        crash_screen_print(50, 100, "hello world xd");

        osViSwapBuffer(system_cfb[gRenderedFramebuffer]);
        gRenderedFramebuffer ^= 1;
        gTimer++;
    }
}
