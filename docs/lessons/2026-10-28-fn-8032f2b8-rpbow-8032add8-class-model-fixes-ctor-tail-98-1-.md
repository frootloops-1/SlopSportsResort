# fn_8032F2B8 (RPBow_8032ADD8): class model fixes ctor tail (98.1 -> 99.4); object temp r26 vs retail r27 unsolved

- status: open
- tags: RPBow_8032ADD8,fn_8032F2B8,sound-actor,class-model,regalloc,new-temp
- scope: RPBow_8032ADD8
- source: claude/flip-bow-1028 sonnet

symptom: after class model: inlined new temp is r26 in ours, r27 in retail (mr, 0x20/0x48 offsets, stores, final stw 0x30(r31)); plus 4 reloc-name lines
cause: plain new colours the temp one register off in the opposite direction from Bsb (there plain was higher than retail); placement-new marker trick does not help
fix: same BowPinSndActor 0x6C / lbl_803CA588 as RPBow_80335DB0, plain new fixes the li r0 tail. Failed for temp: local at function top, T* const local, static-inline new helper, typed placement new, new(__nw__FUl(0x6C)) direct (all r26); void* snd=__nw__FUl; snd=new(snd) gives r24. Untested: make the second block (0x90 BowNewSnd/RPBowNpcSndObject) a class new too; player is r27 in retail so the first temp may depend on the second block's live values
