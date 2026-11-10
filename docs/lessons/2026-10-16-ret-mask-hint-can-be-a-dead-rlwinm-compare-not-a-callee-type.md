# ret-mask hint can be a dead rlwinm. compare, not a callee type

- status: fails
- tags: ret-mask,dead-compare,BRANCH-SHAPE
- scope: Pack/RPSports/RPBowScene/RPBowTrajectoryGuide
- source: claude/nm-4 2026-10-16 sonnet batch 1

symptom: UpdateControllerState 93.3%, 1 wrong instr, near_miss hint ret-mask
cause: target keeps rlwinm. r0,r0,0,23,23 on a discarded x&0x100; MWCC drops every dead form we tried
fix: none: if(x&0x100){}, bool temp, ?1:0 statement, !x all dropped; down(0x100) wrong offset. Check the masked op follows a call before trusting ret-mask
