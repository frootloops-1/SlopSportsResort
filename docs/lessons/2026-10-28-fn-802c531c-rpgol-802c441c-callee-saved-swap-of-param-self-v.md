# fn_802C531C (RPGol_802c441c): callee-saved swap of param self vs a loaded pointer st fixed by assigning st through a getter inline

- status: works
- tags: regalloc,gpr,inline
- scope: RPGol_802c441c fn_802C531C
- source: Gol units 2026-10-28

symptom: 97.2 -> 98.9: self r30/st r31 (target self r31, st r30), 194 diff lines
cause: the getter inline makes st an @N inline-return value instead of a named local read directly, so it is coloured differently from the param; a self copy declared first, a named kindB temp and the flag as a call-arg expression were flat
fix: static inline GolShotState* golShot() { return lbl_804BF890->f6B4; } and st = golShot(): diff 194 -> 64 lines, no marker (plausible real accessor, name inferred). || chains written as `bool r=false; if(..) r=true` or a switch replace the cmplwi/andi. bit test with a compare chain, so keep `return a||b||c`
