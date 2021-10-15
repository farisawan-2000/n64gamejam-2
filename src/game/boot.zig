// const c = @cImport({
//     @cDefine("_FINAL_ROM", "1");
//     @cDefine("TARGET_N64", "1");
//     @cDefine("F3DEX_GBI_2", "1");
//     @cDefine("_LANGUAGE_C", "1");
//     @cInclude("ultra64.h");
//     @cInclude("n64_defs.h");
// });

// extern fn GameMain() void;

// comptime {
//     @export(zigboot, .{ .name = "boot", .linkage = .Strong });
//     @export(zigidle, .{ .name = "idle", .linkage = .Strong });
//     @export(zigmain, .{ .name = "main", .linkage = .Strong });
//     @export(retraceMessageQ, .{ .name = "retraceMessageQ", .linkage = .Strong });
//     @export(rspMessageQ, .{ .name = "rspMessageQ", .linkage = .Strong });
//     @export(rdpMessageQ, .{ .name = "rdpMessageQ", .linkage = .Strong });
//     @export(zigBootStack, .{ .name = "bootStack", .linkage = .Strong });
// }


// pub var zigBootStack: [c.STACKSIZE* 2]u32 = undefined;
// pub var zigMainStack: [c.STACKSIZE* 2]u32 = undefined;


// pub var zigIdleThread: c.OSThread = undefined;
// pub var zigMainThread: c.OSThread = undefined;

// pub var piMessageQ: c.OSMesgQueue = undefined;
// pub var piMessages: [8]c.OSMesg = undefined;

// pub var siMessageQ: c.OSMesgQueue = undefined;
// pub var siMessageBuf: c.OSMesg = undefined;

// pub var dmaMessageQ: c.OSMesgQueue = undefined;
// pub var dmaMessageBuf: c.OSMesg = undefined;

// pub var rspMessageQ: c.OSMesgQueue = undefined;
// pub var rspMessageBuf: c.OSMesg = undefined;

// pub var rdpMessageQ: c.OSMesgQueue = undefined;
// pub var rdpMessageBuf: c.OSMesg = undefined;

// pub var retraceMessageQ: c.OSMesgQueue = undefined;
// pub var retraceMessageBuf: c.OSMesg = undefined;


// var contExist: u8 = undefined;
// var contStatus: [c.MAXCONTROLLERS]c.OSContStatus = undefined;

// pub fn zigmain(arg: ?*c_void) callconv(.C) void {
//     _ = arg;

//     c.osCreateMesgQueue(&dmaMessageQ,     &dmaMessageBuf,       1);
//     c.osCreateMesgQueue(&rspMessageQ,     &rspMessageBuf,       1);
//     c.osCreateMesgQueue(&rdpMessageQ,     &rdpMessageBuf,       1);
//     c.osCreateMesgQueue(&siMessageQ,      &siMessageBuf,        1);
//     c.osCreateMesgQueue(&retraceMessageQ, &retraceMessageBuf,   1);

    
//     c.osSetEventMesg(c.OS_EVENT_SP, &rspMessageQ, null);
//     c.osSetEventMesg(c.OS_EVENT_DP, &rdpMessageQ, null);
//     c.osSetEventMesg(c.OS_EVENT_SI, &siMessageQ,  null);
//     c.osViSetEvent(&retraceMessageQ, null, 1);

//     _ = c.osContInit(&siMessageQ, &contExist, &contStatus);

//     GameMain();
// }


// extern fn crash_screen_init() callconv(.C) void;

// pub fn zigidle(arg: ?*c_void) callconv(.C) void {
//     _ = arg;
    
//     c.osCreateViManager(c.OS_PRIORITY_VIMGR);
//     c.osViSetMode(&c.osViModeNtscLan1);

//     crash_screen_init();

//     c.osCreatePiManager(c.OS_PRIORITY_PIMGR, &piMessageQ, &piMessages, c.NUM_PI_MSGS);
//     c.osCreateThread(&zigMainThread, 1, zigmain, null, &zigMainStack[c.STACKSIZE / 4], 10);
//     c.osStartThread(&zigMainThread);

//     c.osSetThreadPri(0,0);

//     while (true) {

//     }
// }


// pub inline fn osInitialize() void
// {
//     c.__osInitialize_common();
// }


// pub fn zigboot() callconv(.C) void {
//     osInitialize();
//     c.osCreateThread(&zigIdleThread, 1, zigidle, null, &zigBootStack[c.STACKSIZE / 4], 10);
//     c.osStartThread(&zigIdleThread);
// }



