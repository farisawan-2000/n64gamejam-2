#include <ultra64.h>
#include "n64_defs.h"
#include "controller.h"


Controller2639 GameControllers[4];


void ControllerUpdate(void) {
    osContStartReadData(&siMessageQ);
    osRecvMesg(&siMessageQ, NULL, OS_MESG_BLOCK);

    osContGetReadData(_controllers_internal);


    for (int i = 0; i < 4; i++) {
        // thanks kirby 64
        GameControllers[i].button =
            (_controllers_internal[i].button ^ GameControllers[i].held)
            & _controllers_internal[i].button
        ;
        GameControllers[i].held = _controllers_internal[i].button;
        
        GameControllers[i].stickX = _controllers_internal[i].stick_x;
        GameControllers[i].stickY = _controllers_internal[i].stick_y;
    }

}

