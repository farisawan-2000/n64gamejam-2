#include <ultra64.h>
#include "n64_defs.h"

u16 system_cfb[3][SCREEN_WD * SCREEN_HT] __attribute__((aligned(64)));

unsigned short  zbuffer[SCREEN_WD*SCREEN_HT] __attribute__((aligned(64)));

