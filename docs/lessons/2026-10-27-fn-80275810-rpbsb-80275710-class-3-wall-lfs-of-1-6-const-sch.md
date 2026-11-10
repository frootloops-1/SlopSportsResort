# fn_80275810 (RPBsb_80275710): class-3 wall, lfs of 1.6 const scheduled after fadds and count/fctiwz-reload swap r0/r7; 5 more variants + 8-min permuter no gain

- status: fails
- tags: RPBsb_80275710,fn_80275810,register,schedule,lfs,permuter,F6
- scope: Pack/RPSports/RPBsbScene/RPBsb_80275710
- source: orchestrator-1027

symptom: 96.84%, 10 differing lines: target schedules lfs f0,lbl_804BE3A0@sda21 (1.6) before stw r29,0x34(r1), ours after fadds; count lwz is r0 in target but r7 in ours, fctiwz int reload (lwz 0x2c(r1)) r7 in target but r0 in ours, swapping regs in stw 0x24 / 0x1c
cause: register/schedule: target colours the count vreg before the fctiwz-reload vreg; fields 0x18..0x2C are mixed state/count/timer/int/u8 so no array/struct remodel explains it
fix: failed: f24 store before count store (96.7), direct self->count = lbl_804BE3A4 with no cnt local (96.7), single-expression (0.5f+3.6f*(6.0f*speed))*K (fuses to fmadds, 96.3), f32 k = lbl_804BE3A0 before v (96.0), K*v operand swap (96.6), ids[8] above stores (prologue savegpr, 11%); permuter (extern C name needs --name fn_80275810, PERMUTER_DIR set) base 80, ~7000 iters/8 min -j 6, best 85
