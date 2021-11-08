#pragma once

#include <ultra64.h>


enum RMUMtxOps {
	RMU_MTX_MUL = 0,
	RMU_MTX_SCALE,
	RMU_MTX_ROTATERPY,
	RMU_MTX_TRANSLATE,
	RMU_MTX_PERSPECTIVE,
	RMU_MTX_ORTHO,
	RMU_MTX_LOOKAT,
	RMU_MTX_COMMIT,
	RMU_MTX_FINISH
};

// up to 64 packets are allowed
// #define RMU_MAX_PKT 64
// typedef struct RMUPacket {
// 	u8 command;
// 	u8 siz;
// 	union {
// 		u8 data[];
// 		u16 data16[];
// 		u32 data32[];
// 		u32 *dataPtr[];
// 	};
// } RMUPacket;


// #define rmuMulMtx(pkt, mtx) {\
// 	RMUPacket *_p = pkt; \
// 	_p->command = RMU_MTX_MUL; \
// 	_p->data = mtx;\
// }

// #define rmuCommitMtx(pkt, finalLoc) {\
// 	RMUPacket *_p = pkt; \
// 	_p->command = RMU_MTX_COMMIT; \
// 	_p->data = finalLoc; \
// }


// #define rmuFinish(pkt) {\
// 	RMUPacket *_p = pkt; \
// 	_p->command = RMU_MTX_FINISH; \
// }


