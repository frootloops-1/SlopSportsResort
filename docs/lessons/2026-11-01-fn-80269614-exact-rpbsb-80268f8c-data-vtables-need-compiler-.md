# fn_80269614 exact; RPBsb_80268f8c .data vtables need compiler-generated tables

- status: open
- tags: const,sdata,vtable,PMF,fn_80269614,RPBsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_80268f8c
- source: wave3 2026-11-01

symptom: 94.2%: global lfs before prologue stw r31 in retail; unit .data 32.81 (lbl_803C5DAC 0x84, lbl_803C5E30 0x28 undefined)
cause: const-qualified .sdata object (R17 row 69). Vtables: plain global array definitions make fn_80269DF4 reach them via the ..data.0 anchor (71.6); __declspec(weak) arrays restore named addressing (99.9) but .data order is user data before the @754-@759 PMF records, retail is lbl_803C5D58, @754-759, then vtables; in this deferred-inline unit source-defined data always precedes compiler-generated PMF records
fix: fn_80269614: row 69. Next for the unit: model BsbActorView as a real polymorphic class with multiple inheritance (vptrs +0x28/+0x2c, second table at +6 entries) so the compiler emits the vtables after the records, rename lbl_803C5DAC/lbl_803C5E30 to __vt__ names in symbols.txt; would also retire the R17 dead duplicate vt2c store in fn_80269DF4. Hard-tier class-model task

Resolution (2026-11-01): this unit now passes FLIP-OK with explicit vtable arrays.
`#pragma defer_codegen off` plus plain extern declarations before their definitions flushes
the PMF-generating functions first, preserving named extern addressing. A real polymorphic
class is still useful source cleanup, but is not required for the data/layout match. See
[the closeout lesson](2026-11-01-rpbsb-80268f8c-closed-defer-codegen-flush-plus-extern-declar.md).
