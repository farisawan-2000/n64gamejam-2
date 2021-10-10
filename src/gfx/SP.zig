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
    @cInclude("gbi.h");
    @cInclude("PR/gt.h");
});




pub inline void Segment(_g: *gfx.Gfx, segment: u32, ptr: *c_ushort) {
    _g.*.words.w0 = 
              (@intCast(u32, c.G_MOVEWORD) << 24)
            | (@intCast(u32, c.G_MW_SEGMENT) << 16)
            | ((segment >> 24) * 4);
    _g.*.words.w1 = @ptrToInt(ptr);

    _g.* = @intToPtr(*gfx.Gfx, @ptrToInt(_g) + 8);

}


