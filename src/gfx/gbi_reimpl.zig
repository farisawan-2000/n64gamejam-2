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

// comptime {
//     @export(SP.Segment, .{ .name = "gSPSegment", .linkage = .Strong });
//     @export(setupTaskStructure, .{ .name = "setupTaskStructure", .linkage = .Strong });
// }





