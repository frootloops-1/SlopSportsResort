# RPBsb_8027d3ec fn_8027DC80: named const 0.0f hoisted above sdata loads; asm_diff hides swapped data-ref

- status: open
- tags: sdata2,data-ref,scheduling,named-const,RPBsb_8027d3ec
- source: RPBsb_8027d3ec d1-1028

symptom: unit_cmp shows SIZE-MISMATCH lbl_804C3CB8/CBC (0.0f/1.0f sdata2 labels) and DC80 100% by asm_diff but DATA-REF 99.95%
cause: source used literals for 0.0/1.0 (so labels absent) and the old base vector assigned lbl_CB8 to y and BE564 to z; asm_diff normalises reloc names so the swap was invisible. Fix of labels: extern const f32 lbl_804C3CB8/CBC defined after last use and used at every 0.0f/1.0f site (26/28 syms exact). Correct assignment (y=BE564,x=BE560,z=CB8) makes the scheduler hoist the const load first (99.8).
fix: failed: 6 assign orders x scale position, aggregate init, static-inline setter in 6 orders, non-const cast, volatile cast, non-const extern (regresses DA40/E038). Park DC80.
