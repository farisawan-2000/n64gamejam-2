OUTPUT_ARCH (mips)
#define __LINKER__
#include "n64_defs.h"

#define BEGIN_SEG(name, addr) \
    _##name##SegmentStart = ADDR(.name); \
    _##name##SegmentRomStart = __romPos; \
    .name addr : AT(__romPos)

#define END_SEG(name) \
    _##name##SegmentEnd = ADDR(.name) + SIZEOF(.name); \
    _##name##SegmentRomEnd = __romPos + SIZEOF(.name); \
    __romPos += SIZEOF(.name);

#define BEGIN_NOLOAD(name) \
    _##name##SegmentBssStart = ADDR(.name.noload); \
    .name.noload (NOLOAD) :

#define END_NOLOAD(name) \
    _##name##SegmentBssEnd = ADDR(.name.noload) + SIZEOF(.name.noload); \
    _##name##SegmentBssSize = SIZEOF(.name.noload);

#define MODEL(path) path(.data*)

SECTIONS
{
   __romPos = 0;

   BEGIN_SEG(boot, 0x04000000)
   {
      BUILD_DIR/asm/rom_header.o(.text); /* ROM Header */
      BUILD_DIR/boot.6102.o(.data); /* CIC 6102 bootcode */
   }
   END_SEG(boot)
   

   BEGIN_SEG(code, 0x80000400) SUBALIGN(16)
   {
#ifndef CRASH_SCREEN_DBG
parse_map = 0x80345678;
find_function_in_stack = 0x80345678;
draw_disasm = 0x80345678;
#endif
      BUILD_DIR/asm/entry.o(.start);
      KEEP(BUILD_DIR/src*.o(.text));

      */libultra_rom.a:*.o(.text);
      */libgcc.a:*.o(.text);

      /usr/lib/n64/PR/rspboot.o(.text);
      /usr/lib/n64/PR/gspF3DEX2.fifo.o(.text);
      gspTurbo3D_fifoTextStart = .;
      BUILD_DIR/turbo3d_text.o(.data);

      /* data */
      MODEL(BUILD_DIR/models/clearCFB/model.o);
      BUILD_DIR/src*.o(.data*);
      */libultra_rom.a:*.o(.data*);

      /usr/lib/n64/PR/gspF3DEX2.fifo.o(.data*);
      /usr/lib/n64/PR/rspboot.o(.data*);
      gspTurbo3D_fifoDataStart = .;
      BUILD_DIR/turbo3d_data.o(.data);
      /* rodata */
      BUILD_DIR/src*.o(.*rodata*);

      */libultra_rom.a:*.o(.*rodata*);
      */libgcc.a:*.o(.*rodata*);
   }
   END_SEG(code)
   BEGIN_NOLOAD(code)
   {
      BUILD_DIR/src/game*.o(.*bss*);
      BUILD_DIR/src/engine2639*.o(.*bss*);
      BUILD_DIR/src/LevelSpecific*.o(.*bss*);

      */libultra_rom.a:*.o(COMMON);
      */libultra_rom.a:*.o(.scommon);
      */libultra_rom.a:*.o(.*bss*);
   }
   END_NOLOAD(code)

   ASSERT((SIZEOF(.code) < 0x100000), "please make mainseg smaller")
   
   . = CFB_ADDRESS;

   BEGIN_NOLOAD(system_cfb)
   {
      BUILD_DIR/src/buffers/system_cfb.o(.bss*);
   }
   END_NOLOAD(system_cfb)
#ifdef RSPBUF_ADDRESS
   . = RSPBUF_ADDRESS;
#endif
   BEGIN_NOLOAD(system_rspbuf)
   {
      BUILD_DIR/src/buffers/system_rspbuf.o(.bss*);
      end_bss = .;
   }
   END_NOLOAD(system_rspbuf)


   /*MODEL SPACE*/

   /*LEVEL_TITLE*/
   BEGIN_SEG(Title, 0x80100000) {
      MODEL(BUILD_DIR/levels/title/level.o);

      MODEL(BUILD_DIR/models/JamTitle/model.o);
      MODEL(BUILD_DIR/models/button1/model.o);
      MODEL(BUILD_DIR/models/button2/model.o);
      . = ALIGN(16);
   }
   END_SEG(Title)

   /* in game */
   BEGIN_SEG(InGame, 0x80100000) {
      MODEL(BUILD_DIR/levels/ingame/level.o);

      MODEL(BUILD_DIR/models/ControlCenter/model.o);
      MODEL(BUILD_DIR/models/CButtonRight/model.o);
      MODEL(BUILD_DIR/models/CButtonLeft/model.o);
      MODEL(BUILD_DIR/models/lever/model.o);

      MODEL(BUILD_DIR/models/signP1/model.o);
      MODEL(BUILD_DIR/models/signP2_1/model.o);
      MODEL(BUILD_DIR/models/signP2_2/model.o);
      MODEL(BUILD_DIR/models/signPAss/model.o);

      MODEL(BUILD_DIR/models/canvas/model.o);

      MODEL(BUILD_DIR/models/cursor/model.o);
      MODEL(BUILD_DIR/models/paint/model.o);
      . = ALIGN(16);
   }
   END_SEG(InGame)

   BEGIN_SEG(TEXTURE, 0x03000000) {
      BUILD_DIR/src/game/textures.o(TEXTURE);
      . = ALIGN(16);
   }
   END_SEG(TEXTURE)




   /* Discard everything not specifically mentioned above. */
   /DISCARD/ :
   {
      *(*);
   }
}

