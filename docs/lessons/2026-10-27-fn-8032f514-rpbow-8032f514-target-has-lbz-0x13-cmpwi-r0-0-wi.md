# fn_8032F514 (RPBow_8032F514): target has 'lbz 0x13; cmpwi r0,0' with NO branch, then the 0x15 test; ~35 source shapes cannot keep the compare without the beq

- status: fails
- tags: RPBow_8032F514,fn_8032F514,beq,dead-compare,control-flow,F9
- scope: Pack/RPSports/RPBowScene/RPBow_8032F514
- source: orchestrator-1027

symptom: 99.0%, ours 404 B vs 400 B: ours lbz13;cmpwi;beq end;lbz15;cmpwi;beq end; target lbz13;cmpwi;lbz15;cmpwi;beq end (first divergence our .o 0xf4 / 0x8032F5E4)
cause: wall class 2: MWCC drops an empty if at the front end, so any shape that removes the b13 branch also removes its lbz/cmpwi; the original leaves a cmpwi with no consumer (probably a branch whose body vanished late, post-scheduler)
fix: failed: empty if / if-else / ; / (void)0 bodies, dead-local store (96-97), dead load, empty inline/static nop call, b13&&0, b13||0, b13==1, bool copy, comma expr, b13?0:0, b13?b15:b15, (b13||1)&&b15, b15|(b13&0), goto L;L:, do{break}while(0), switch case0/default, for(;b13;){break;}, #pragma opt_dead_code off, nested if/&& (all keep the beq), volatile read (keeps load, no cmpwi, 98.9). Untried: an inlined accessor/assert from the neighbouring RPBow functions, b13 as a bitfield-backed flag.
