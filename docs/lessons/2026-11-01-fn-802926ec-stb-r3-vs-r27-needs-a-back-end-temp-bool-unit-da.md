# fn_802926EC: stB r3 vs r27 needs a back-end-temp bool; unit data is all extern

- status: fails
- tags: fn_802926EC,colouring,bool,RPGol
- scope: Pack/RPSports/RPGolScene/RPGolFieldManager
- source: step2 2026-11-01

symptom: 99.8%, 24 lines: stB r27 (target r3), mgr ptr r28 (r27), cfg/lbl_804BF8C4 r3 (r28)
cause: no node reaches K, colouring is descending vreg; the 0xa8 copy temp got r6 in the original so stB already held r3: stB must outrank the 9-word GolBasis copy back-end temps (r51-r59) but a two-assignment bool is always a named lowest vreg
fix: none. Dead: !GolIsStateB(), bool stB = a||b and ?: (li 1 first, branch shape changes, 53 lines), enum ternary local/in condition (53-55), named-local order stB,cfg,mgr,sg (28). Try: a form making stB a back-end temp at the condition while keeping li 0 / conditional li 1, or restructure the guessed GolFrame/GolMakeMtx helpers so the copy temps number differently. Unit is NOT flippable regardless: .ctors fn_80294178 missing, vtables lbl_803C78AC-DC, .sbss lbl_804BF868/86C, .rodata lbl_8038E458, .sdata2 floats lbl_804C3ED8-3F6C and @1433 only extern; gap_07_8038E456_rodata and gap_12_804C3EDD_sdata2 must be deleted from symbols.txt
