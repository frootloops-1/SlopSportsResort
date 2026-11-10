# RPSysPlayerSelectScene Calculate 99.8 -> 99.9: inline the state-11 body by hand + temps in args + real fn_801D99C8 prototype

- status: works
- tags: regalloc,inline,RPSysPlayerSelectScene,prototype
- scope: Pack/RPSports
- source: claude opus worker 2026-11-03

symptom: Calculate 28 diff lines: state-2 r r30 vs r29, calcState11 loop i split (r28/r27), p710 r28 vs r27
cause: inline member calcState11 splits the shared i into two vregs; named idx16/mii locals rank below r. Target: mii/idx16 are arg temps, one i
fix: Body written directly in the state-11 branch (i unified), fn_801D99C8(mpUnk88, fn_801E9650(p710,i), NULL, fn_801D973C(..)->unk4, fn_801D973C(..)->unk8) with prototype (void*,void*,void*,s32,s32) as defined in RPSysMenuKokeshiMgr (u16 last param deferred the lhz). 28 -> 8 lines, DOL 18 -> 4 bytes
