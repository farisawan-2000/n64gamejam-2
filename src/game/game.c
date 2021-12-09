#include <ultra64.h>
#include "n64_defs.h"
#include "memory.h"
#include "levels.h"

typedef enum {
    GAME_LOAD_TITLE = 0,
    GAME_TITLE,
    GAME_LOAD_LEVEL,
    GAME_LEVEL_LOOP,
    GAME_CREDITS,
} GameStates;

static GameStates sGameState = GAME_LOAD_TITLE;
static GameStates sGameNextState = GAME_LOAD_TITLE;
u32        sGameContext = 0; // arbitrary argument
u32        sGameTimer   = 0;

// Title options (GAME_TITLEs)
u32 sMenuChoice = 0; // sets to (1 for multip, 2 for singleplayer)

// GAME_LOAD_LEVEL options
u32 sDMAInProgress = 0;

typedef struct {
    volatile u32 *start;
    volatile u32 *end;
} File;

#define EXTERN_FILE(lv) \
    extern u32 _ ## lv ## SegmentRomStart[]; \
    extern u32 _ ## lv ## SegmentRomEnd[];

#define FILE(lv) \
    {_ ## lv ## SegmentRomStart, _ ## lv ## SegmentRomEnd}

#define FILEARG(lv) \
    _ ## lv ## SegmentRomStart, _ ## lv ## SegmentRomEnd

EXTERN_FILE(Title)
EXTERN_FILE(InGame)
EXTERN_FILE(TEXTURE)

File sLevels[] = {
    FILE(Title),
    FILE(InGame),
};

void GameLoadLevel(u32 levelID) {
    Mem_DMARead(SEG_LEVEL, sLevels[levelID].start, sLevels[levelID].end);
}

void drawLevel(void) {
    Level2639 *l = (volatile Level2639*)0x80100000;

    Object2639 **oList = l->objList;

    for (int i = 0; i < l->objCount; i++) {
        Object_Draw(oList[i]);
    }

    gCameraMode = l->camMode;

    if (sGameTimer <= 6) {
        VectorCopy(&sCameraSpot_Target, &l->camSpot);
        VectorCopy(&sCameraLook_Target, &l->camLook);
    }
}

extern u32 ReloadTitle;

void GameNextStateProc(void) {
    switch (sGameState) {
        case GAME_LOAD_TITLE:
            // no tlb lol
            // osMapTLB(0x02, OS_PM_1M, OS_K0_TO_PHYSICAL(SEG_LEVEL), -1, -1, -1);
                        // u32 oddpaddr, s32 asid);
            GameLoadLevel(0);
            Mem_DMARead(SEG_TEXTURES, FILEARG(TEXTURE));
            sGameNextState = GAME_TITLE;
            break;
        case GAME_TITLE:
            if (sMenuChoice != 0) {
                if (sGameTimer > 60) { // semblance of UX design
                    sGameNextState = GAME_LOAD_LEVEL;
                    sGameContext = 1;
                }
            } else {
                sGameTimer = 0;
            }

            drawLevel();

            break;
        case GAME_LOAD_LEVEL:
            // bzero(SEG_LEVEL, 0x100000);
            GameLoadLevel(sGameContext);
            sGameNextState = GAME_LEVEL_LOOP;
            // void bcopy(const void *src, void *dest, size_t n);
            // bcopy(0x80300000, 0x80300000 + 0x800, 0x800);
            break;
        case GAME_LEVEL_LOOP:
            drawLevel();
            if (ReloadTitle == 1) {
                sGameNextState = GAME_LOAD_TITLE;
                ReloadTitle = 0;
                sMenuChoice = 0;
            }
            break;
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
