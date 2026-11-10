# fn_802717CC (RPBsb_8027039c): x/y/z trans loads f0/f1/f2 vs target f2/f1/f0, 8 variants flat

- status: fails
- tags: regalloc,fpr
- scope: RPBsb_8027039c fn_802717CC
- source: FPR batch 2 2026-10-28

symptom: 99.37, opcodes identical
cause: declaration order moves which of x/y/z gets f0 but reorders the loads too, so target's in-order loads with x=f2 are not reached
fix: none: f32/f64 locals, uninit locals, no locals (99.2), reversed decl (99.1), SetTrans inline ref or 3 float params (99.2/99.3), const pv, struct-return fn_80257418 (89.3, adds struct copy)
