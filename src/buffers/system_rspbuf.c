#include <ultra64.h>
#include "n64_defs.h"

u64 system_rdpfifo[RDPFIFO_SIZE];
u64 system_rspyield[OS_YIELD_DATA_SIZE / sizeof(u64)];
