#include <ultra64.h>

#include "memory.h"

extern OSPiHandle *carthandle;

// an actual DMA copy
void dma_copy(OSPiHandle *handle, u32 physAddr, u32 vAddr, u32 size, u8 direction) {
    OSIoMesg dmaIoMesg;

    if (direction == OS_WRITE) {
        osWritebackDCache((void*)vAddr, size);
    } else {
        osInvalDCache((void*)vAddr, size);
    }
    dmaIoMesg.hdr.pri = 0;
    dmaIoMesg.hdr.retQueue = &dmaMessageQ;
    dmaIoMesg.size = 0x10000;
    while (size >= 0x10001) {
        dmaIoMesg.dramAddr = (void*)vAddr;
        dmaIoMesg.devAddr = physAddr;
        if (osEPiStartDma(handle, &dmaIoMesg, direction) == -1) {
            *(vs8*)0=0;
        }
        osRecvMesg(&dmaMessageQ, NULL, OS_MESG_BLOCK);
        size -= 0x10000;
        physAddr += 0x10000;
        vAddr += 0x10000;
    }
    if (size != 0) {
        dmaIoMesg.dramAddr = (void*)vAddr;
        dmaIoMesg.devAddr = physAddr;
        dmaIoMesg.size = size;
        if (osEPiStartDma(handle, &dmaIoMesg, direction) == -1) {
            *(vs8*)0=0;
        }
        osRecvMesg(&dmaMessageQ, NULL, OS_MESG_BLOCK);
    }
}

void Mem_DMARead(void *vAddr, unsigned long start, unsigned long end) {
    osWritebackDCache((void*)vAddr, end - start);
    dma_copy(carthandle, start, (u32)vAddr, end - start, OS_READ);
    osInvalDCache((void*)vAddr, end - start);
}

// void dma_write_s(void *vAddr, unsigned long physAddr, unsigned long size) {
//     dma_copy(carthandle, physAddr, (u32)vAddr, size, OS_WRITE);
// }
