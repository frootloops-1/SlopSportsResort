# fn_802F6E80 signed %360 temp rename: source-shape variants all no-gain

- status: fails
- tags: regalloc,rpbox,modulo,mulhw
- scope: fn_802F6E80
- source: claude/box2-1028

symptom: add/srawi/srwi/add of n%360 uses r0 then r4, original keeps quotient in r4 then r0 (4 instrs)
cause: unknown; vreg coloring of mulhw sequence temps, not source-shape sensitive
fix: tried: q=n/360;r=n-q*360; moving h00|=4 before/after h02 store (before regresses to 97.1, after = same); u16 m local (99.6); static inline mod360 (99.7, fadds operand swap); frac+(u16)x (99.7). Retained source stays at 99.77
