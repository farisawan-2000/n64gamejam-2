#include <ultra64.h>
#include "n64_defs.h"

u64 bootStack[STACKSIZE / sizeof(u64)];

extern void gameloop(void *);

static OSThread idleThread;
static u64 idleThreadStack[STACKSIZE / sizeof(u64)];
static OSThread mainThread;
static u64 mainThreadStack[STACKSIZE / sizeof(u64)];

OSMesgQueue piMessageQ;
OSMesgQueue siMessageQ;
OSMesgQueue dmaMessageQ;
OSMesgQueue rspMessageQ;
OSMesgQueue rdpMessageQ;
OSMesgQueue retraceMessageQ;

static OSMesg piMessages[NUM_PI_MSGS];
static OSMesg siMessageBuf;
static OSMesg dmaMessageBuf;
static OSMesg rspMessageBuf;
static OSMesg rdpMessageBuf;
static OSMesg retraceMessageBuf;

OSIoMesg dmaIOMessageBuf;

OSContStatus contStatus[MAXCONTROLLERS];
OSContPad contPad[MAXCONTROLLERS];
u8 contExist;

void thread3_mainFunc(void *arg) {
    osCreateMesgQueue(&dmaMessageQ, &dmaMessageBuf, 1);
    osCreateMesgQueue(&rspMessageQ, &rspMessageBuf, 1);
    osCreateMesgQueue(&rdpMessageQ, &rdpMessageBuf, 1);
    osCreateMesgQueue(&siMessageQ, &siMessageBuf, 1);
    osCreateMesgQueue(&retraceMessageQ, &retraceMessageBuf, 1);

    osSetEventMesg(OS_EVENT_SP, &rspMessageQ, NULL);
    osSetEventMesg(OS_EVENT_DP, &rdpMessageQ, NULL);
    osSetEventMesg(OS_EVENT_SI, &siMessageQ, NULL);
    osViSetEvent(&retraceMessageQ, NULL, 1);

    osContInit(&siMessageQ, &contExist, contStatus);

    gameloop(arg);
}

static void idleFunc(void *arg) {
    osCreateViManager(OS_PRIORITY_VIMGR);
    switch (osTvType) {
        case 0:
            osViSetMode(&osViModeTable[OS_VI_PAL_LAN1]);
        case 1:
            osViSetMode(&osViModeTable[OS_VI_NTSC_LAN1]);
        case 2:
            osViSetMode(&osViModeTable[OS_VI_MPAL_LAN1]);
    }

    osCreatePiManager((OSPri) OS_PRIORITY_PIMGR, &piMessageQ, piMessages, NUM_PI_MSGS);

    crash_screen_init();
    osCreateThread(&mainThread, 3, thread3_mainFunc, arg, mainThreadStack + STACKSIZE / sizeof(u64), 10);
    osStartThread(&mainThread);
    osSetThreadPri(NULL, 0);

    while (1) {

    }
}

void boot(void) {
    osInitialize();
    osCreateThread(&idleThread, 1, idleFunc, (void *) 0, idleThreadStack + STACKSIZE / sizeof(u64), 10);
    osStartThread(&idleThread);
}
