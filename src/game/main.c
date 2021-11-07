#include <ultra64.h>
#include <PR/gt.h>
#include <PR/gu.h>
#include "n64_defs.h"
#include "gtHelpers.h"
#include "camera.h"

extern Gfx clearCfb[];

OSTask tlist = {
    M_GFXTASK,                             /* task type                */
    OS_TASK_DP_WAIT,    /* task flags               */
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

Gfx dpGlobDPBlock[30] = {
    gsDPPipeSync(),
    gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),

    gsDPPipeSync(),
    gsDPSetColorImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, system_cfb),
    gsDPSetFillColor((GPACK_RGBA5551(64, 64, 255, 1) << 16 | GPACK_RGBA5551(64, 64, 255, 1))),
    gsDPFillRectangle(0, 0, SCREEN_WD, SCREEN_HT - 1),

    gsDPPipeSync(),
    gsDPEndDisplayList(),
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

gtGlobState dpGlobObjState2 = { 0xffff, /* perspNorm */
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
gtGlobState *ggsp2 = &(dpGlobObjState2);

u64 dram_stack[SP_DRAM_STACK_SIZE64]; /* used for matrix stack */

gtGfx *gtlistp;
Gfx *glistp; /* global for test case procs */

typedef struct {
    Mtx projection;
    Mtx viewing;
    Mtx identity;

    float projectionF[4][4];
    float viewingF[4][4];
    float identityF[4][4];

    gtState objState[512];


    gtGfx turboGfxBuffer[512];

    Gfx glist[GLIST_LEN];
} GameGFXState;

GameGFXState dynamic;

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
        gDPSetDepthImage(gptr++, OS_K0_TO_PHYSICAL(zbuffer));
        gDPSetCycleType(gptr++, G_CYC_FILL);
        gDPSetColorImage(gptr++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
                 OS_K0_TO_PHYSICAL(zbuffer));
        gDPSetFillColor(gptr++, (GPACK_ZDZ(G_MAXFBZ,0) << 16 | 
                       GPACK_ZDZ(G_MAXFBZ,0)));
        gDPFillRectangle(gptr++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
        gDPPipeSync(gptr++);

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
    gDPNoOp(gptr++);
    gDPNoOp(gptr++);
}

Vtx q0[5] __attribute__((aligned(16))) = {
    { -40, 40, 0, 0, 0, 0, 0xFF, 0, 0, 0xff },
    { 40, 40, 0, 0, (31 << 5), 0, 0, 0xff, 0, 0xff },
    { 40, -40, 0, 0, (31 << 5), (31 << 5), 0, 0xff, 0, 0xff },
    { -40, -40, 0, 0, 0, (31 << 5), 0xff, 0, 0, 0xff },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xff },
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
    gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, 1, 0, 0, 0, SHADE, 0, 0, 0, 1),
    gsDPSetEnvColor(0, 0, 255, 255),
    gsDPEndDisplayList(),
    gsDPEndDisplayList(),
    gsDPEndDisplayList(),
    gsDPEndDisplayList(),
};





extern gtTriN mario_tris[83 * 2];
extern Vtx test_Cube_mesh_vtx_0[182];

float yaw = 0;

extern gtState test64_State;
extern gtGfx test64_Gfx;

extern gtState test64bf_State;
extern gtGfx test64bf_Gfx;

typedef float Mtx4[4][4];

static void SetupViewing(void) {
    float mf1[4][4];
    Mtx tmp;
    guPerspectiveF(dynamic.projectionF, &(ggsp->sp.perspNorm), 33, 320.0 / 240.0,
                100, 2000, 1.0f);
    guMtxF2L(mf1, &dynamic.projection);

    CameraUpdate(&dynamic.viewing, dynamic.viewingF);

    float vp[4][4];
    float mvp[4][4];

    guMtxCatF(&dynamic.viewingF, &dynamic.projectionF, vp);

    Mtx4 M;
    guMtxL2F(M, &test64_State.sp.transform);
    guMtxCatF(M, vp, mvp);
    guMtxF2L(mvp, &test64_State.sp.transform);

    guMtxL2F(M, &test64bf_State.sp.transform);
    guMtxCatF(M, vp, mvp);
    guMtxF2L(mvp, &test64bf_State.sp.transform);
    
}

u32 gRCPTimer = 0;


void gameloop(void *arg) {
    Gfx *gp;

    Mtx4 Sc, Ro, ScRo, Tr, Ident;

    guMtxIdent(&Ident);

    // InitRsp(1);

    while (1) {
        osRecvMesg(&retraceMessageQ, NULL, OS_MESG_BLOCK);

        ControllerUpdate();



        InitRsp(1);
        gtlistp = &(dynamic.turboGfxBuffer[0]);
        gp = &dynamic.glist;

        gtDraw(gtlistp++, ggsp, &dpInitClearObj, NULL, NULL);

        #define SCL 0.25f
        #define TRSL 400
        Mtx4 tmp;
        gtStateSetOthermode(&(ggsp2->sp.rdpOthermode), GT_RENDERMODE, (G_RM_ZB_OPA_SURF | G_RM_ZB_OPA_SURF2));
        gtStateSetOthermode(&(ggsp2->sp.rdpOthermode), GT_CYCLETYPE, G_CYC_1CYCLE);
        guScaleF(Sc, SCL, SCL, SCL);
        guRotateRPYF(Ro, 0, yaw++, 0);
        guMtxCatF(Sc, Ro, ScRo);

        guTranslateF(Tr, 0, -40, -TRSL);
        guMtxCatF(ScRo, Tr, tmp);
        guMtxF2L(tmp, &test64_State.sp.transform);

        guTranslateF(Tr, 0, 0, TRSL);
        guMtxCatF(ScRo, Tr, tmp);
        guMtxF2L(tmp, &test64bf_State.sp.transform);

        // test64_State.sp.rdpCmds = rdpComdsEpic;
        // test64bf_State.sp.rdpCmds = rdpComdsEpic;

        gtStateSetOthermode(&(test64_State.sp.rdpOthermode), GT_RENDERMODE, (G_RM_ZB_OPA_SURF | G_RM_ZB_OPA_SURF2));
        gtStateSetOthermode(&(test64_State.sp.rdpOthermode), GT_CYCLETYPE, G_CYC_1CYCLE);
        gtStateSetOthermode(&(test64bf_State.sp.rdpOthermode), GT_RENDERMODE, (G_RM_ZB_OPA_SURF | G_RM_ZB_OPA_SURF2));
        gtStateSetOthermode(&(test64bf_State.sp.rdpOthermode), GT_CYCLETYPE, G_CYC_1CYCLE);
        
        SetupViewing();
        // test64_Gfx.obj.gstatep = ggsp2;
        gtDrawStatic(gtlistp++, test64_Gfx);
        gtDrawStatic(gtlistp++, test64bf_Gfx);

        // start_mathutil_task();
        // start_turbo3d_task();
        gtDraw(gtlistp++, NULL, &dpFinalObj, NULL, NULL);
        gtFinish(gtlistp++);
        tlist.t.data_size = (u32)((gtlistp - dynamic.turboGfxBuffer) * sizeof(gtGfx));
        tlist.t.data_ptr = dynamic.turboGfxBuffer;
        osWritebackDCache(&dynamic, sizeof(dynamic));
        osSpTaskStart(&tlist);

        while (1) {
            if (osRecvMesg(&rspMessageQ, NULL, OS_MESG_NOBLOCK) == 0) {
                gRCPTimer = 0;
                break;
            }
            if (osRecvMesg(&rdpMessageQ, NULL, OS_MESG_NOBLOCK) == 0) {
                gRCPTimer = 0;
                break;
            }
            gRCPTimer++;
            if (gRCPTimer > 5) *(vs8*)0=0;
        }
        crash_screen_print(10,10, "%d (%.2f %.2f %.2f), (%.2f %.2f %.2f)",
            gTimer,
            sCameraSpot.x, sCameraSpot.y, sCameraSpot.z, 
            sCameraRPY.roll, sCameraRPY.pitch, sCameraRPY.yaw
        );
        osViSwapBuffer(system_cfb[gRenderedFramebuffer]);
        gRenderedFramebuffer ^= 1;
        gTimer++;
    }
}
