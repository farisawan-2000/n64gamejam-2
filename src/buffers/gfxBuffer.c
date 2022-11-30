#include <ultra64.h>
#include "n64_defs.h"

// 16kb per buffer ought to be enough for everyone
u16 gfxAlloc[3][GFX_SIZE] __attribute__((aligned(64)));

