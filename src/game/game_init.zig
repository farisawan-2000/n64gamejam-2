// #include "c_includes.hz"
// #include "gfx/SP.hz"

// comptime {
//     @export(GameMain, .{ .name = "GameMain", .linkage = .Strong });
//     @export(gfxBuff, .{ .name = "gfxBuff", .linkage = .Strong });
//     @export(myGfxTask, .{ .name = "myGfxTask", .linkage = .Strong});
//     @export(gRenderedFramebuffer, .{ .name = "gRenderedFramebuffer", .linkage = .Strong});
// }
// extern var retraceMessageQ : c.OSMesgQueue;
// extern var rspMessageQ : c.OSMesgQueue;
// extern var rdpMessageQ : c.OSMesgQueue;

// pub fn setupTaskStructure(task: *c.OSTask) void {
//     task.*.t.type = c.M_GFXTASK;
//     task.*.t.flags = c.OS_TASK_DP_WAIT | c.OS_TASK_LOADABLE;
//     task.*.t.ucode_boot = &gfx.rspbootTextStart;
//     task.*.t.ucode_boot_size = c.SP_BOOT_UCODE_SIZE;
//     task.*.t.ucode = &gfx._binary_turbo3d_build_t3d_bin_start;
//     task.*.t.ucode_size = c.SP_UCODE_SIZE;
//     task.*.t.ucode_data = &gfx._binary_turbo3d_build_t3d_data_bin_start;
//     task.*.t.ucode_data_size = c.SP_UCODE_DATA_SIZE;

//     task.*.t.output_buff = c.system_rdpfifo;
//     task.*.t.output_buff_size = @ptrToInt(c.system_rdpfifo) + c.RDPFIFO_SIZE;

//     task.*.t.yield_data_ptr = c.system_rspyield;
//     task.*.t.yield_data_size = c.OS_YIELD_DATA_SIZE;

//     // unused
//     task.*.t.dram_stack = null;
//     task.*.t.dram_stack_size = 0;

//     task.*.t.data_ptr = null;
//     task.*.t.data_size = 0;
// }


// var gfxBuff : [c.GLIST_LEN]gfx.gtState = undefined;

// var myGfxTask : c.OSTask = undefined;
// var gRenderedFramebuffer: u16 = 0;
// var gTimer : u32 = 0;



// pub fn GameMain() callconv(.C) void {

//     setupTaskStructure(&myGfxTask);

//     while(true) {
//         _ = c.osRecvMesg(&retraceMessageQ, null, c.OS_MESG_BLOCK);

//         SP.Segment(&gfxBuff[0], c.CFB_SEGMENT, @ptrCast(*c_ushort, &c.system_cfb[gRenderedFramebuffer]));
//         SP.DisplayList(&gfxBuff[1], &gfx.clear_cfb);

//         DP.FullSync(&gfxBuff[2]);
//         SP.EndDisplayList(&gfxBuff[3]);

//         myGfxTask.t.data_ptr = @ptrCast(*c_ulonglong, &gfxBuff);

//         c.osWritebackDCacheAll();
//         c.osSpTaskLoad(&myGfxTask);
//         c.osSpTaskStartGo(&myGfxTask);

//         // _ = c.osRecvMesg(&rspMessageQ, null, c.OS_MESG_BLOCK);
//         _ = c.osRecvMesg(&rdpMessageQ, null, c.OS_MESG_BLOCK);  

        
//         c.osViSwapBuffer(&c.system_cfb[gRenderedFramebuffer]);
//         gRenderedFramebuffer ^= 1;
//         gTimer += 1;
//     }
// }



