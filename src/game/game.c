#include <ultra64.h>
#include "n64_defs.h"

typedef enum {
    GAME_TITLE=0,
    GAME_LOAD_LEVEL,
    GAME_SINGLEPLAYER,
    GAME_MULTIPLAYER,
    GAME_CREDITS,
} GameStates;

GameStates sGameState = GAME_TITLE;
GameStates sGameNextState = GAME_TITLE;
u32        sGameContext = 0; // arbitrary argument
u32        sGameTimer   = 0;

// Title options (GAME_TITLEs)
u32 sMenuChoice = 0; // sets to playercount (1 for singlep, 2 for multip)

// GAME_LOAD_LEVEL options
u32 sDMAInProgress = 0;


void GameLoadLevel(u32 levelID) {
    Mem_DMARead();
}


void GameNextStateProc(void) {
    switch (sGameState) {
        case GAME_TITLE:
            if (sMenuChoice != 0) {
                sGameNextState = GAME_LOAD_LEVEL;
                sGameContext = sMenuChoice;
            }
            break;
        case GAME_LOAD_LEVEL:
            GameLoadLevel(sGameContext);
    }
}


void GameTick(void) {
    if (sGameState != sGameNextState) {
        sGameTimer = 0;
    }
    sGameState = sGameNextState;

    GameNextStateProc();


    sGameTimer++;
}