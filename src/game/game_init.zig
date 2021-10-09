const c = @cImport({
    @cDefine("_FINAL_ROM", "1");
    @cDefine("TARGET_N64", "1");
    @cDefine("F3DEX_GBI_2", "1");
    @cDefine("_LANGUAGE_C", "1");
    @cInclude("ultra64.h");
    @cInclude("n64_defs.h");
});

const gfx = @cImport({
    @cDefine("_FINAL_ROM", "1");
    @cDefine("TARGET_N64", "1");
    @cDefine("F3DEX_GBI_2", "1");
    @cDefine("_LANGUAGE_C", "1");
    @cInclude("PR/gt.h");
});

// comptime {
//     @import(comptime path: []u8) type
// }
const boot = @import("boot.zig");



pub fn GameMain() void {
    var draw_frame: u8 = 0;
    // var gp: ?*gfx.Gfx = null;

    while(true) {
        _ = c.osRecvMesg(@ptrCast([*c]c.OSMesgQueue, &boot.retraceMessageQ), null, c.OS_MESG_BLOCK);

        var i : u32 = 0;
        var j : u32 = 0;
        while (i < c.SCREEN_WD) {
            while (j < c.SCREEN_HT / 2) {
                c.system_cfb[draw_frame][(i * c.SCREEN_WD) + j] = 0xFFFF;
            }
        }
        
        c.osViSwapBuffer(@ptrCast(*c_void, &c.system_cfb[draw_frame]));
        draw_frame ^= 1;
    }
}

