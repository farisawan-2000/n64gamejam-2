#pragma once


#define gtFinish(gt_pointer) { \
	gtGfx *_g = gt_pointer; \
	_g->obj.gstatep = (gtGlobState *) NULL; \
    _g->obj.statep = (gtState *) NULL; /* signal end of object list */ \
    _g->obj.vtxp = (Vtx *) NULL; \
    _g->obj.trip = (gtTriN *) NULL; \
}


#define gtDraw(gt_pointer, globstate, state, vtx, tri) { \
	gtGfx *_g = gt_pointer; \
	_g->obj.gstatep = globstate; \
    _g->obj.statep = state; \
    _g->obj.vtxp = (Vtx *) vtx; \
    _g->obj.trip = (gtTriN *) tri; \
}

