#pragma once
#include <ultra64.h>

typedef struct {
    OSThread thread;
    u64 stack[0x800 / sizeof(u64)];
    OSMesgQueue mesgQueue;
    OSMesg mesg;
    u16 *framebuffer;
    u16 *framebuffer2;
    u16 *framebuffer3;
    u16 width;
    u16 height;
} CrashScreen;
extern CrashScreen gCrashScreen;

