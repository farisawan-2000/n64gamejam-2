#pragma once

#define	SCREEN_WD	320
#define	SCREEN_HT	240
#define SCREEN_WIDTH SCREEN_WD
#define SCREEN_HEIGHT SCREEN_HT

#define RDPFIFO_SIZE    (8*1024/sizeof(u64))
#define GLIST_LEN       2048

#define SP_BOOT_UCODE_SIZE      0x00d0  /*  rspboot size */

#define	NUM_PI_MSGS	8		/* PI Message Queue      */
#define	STACKSIZE	0x2000		/* Thread stack size */

#define	STATIC_SEGMENT	1
#define CFB_SEGMENT     2
#define CFB_ADDRESS     0x80300000
#define RSPBUF_ADDRESS  0x803a0000      /* If no define, then after cfb */

#ifdef _LANGUAGE_C
extern	OSMesgQueue	piMessageQ;
extern	OSMesgQueue	siMessageQ;
extern	OSMesgQueue	dmaMessageQ;
extern	OSIoMesg	dmaIOMessageBuf;
extern	OSMesgQueue	rspMessageQ;
extern	OSMesgQueue	rdpMessageQ;
extern	OSMesgQueue	retraceMessageQ;
extern	OSContStatus	contStatus[MAXCONTROLLERS];
extern	OSContPad	_controllers_internal[MAXCONTROLLERS];
extern	u8		contExist;

extern	u16		system_cfb[2][SCREEN_WD*SCREEN_HT];
extern  u16   zbuffer[SCREEN_WD*SCREEN_HT];
extern  u64             system_rdpfifo[];
extern  u64             system_rspyield[];

#define A_COUNT(a) (sizeof((a)) / sizeof((a[0])))

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

typedef struct {
  u16 button;
  u16 held;
  s8 stickX;
  s8 stickY;
  f32 angle;
} Controller2639;

typedef float Mtx4[4][4];


/*
 *  Print macro for DEBUG
 */
#ifdef	DEBUG
#  define	osSyncPrintf	osSyncPrintf
#else
#  define	osSyncPrintf	if (0) osSyncPrintf
#endif

#endif	/* _LANGUAGE_C */
