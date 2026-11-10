# fn_80320EFC residue: b12 lerp n-1 GPR and final-block ctx r5

- status: fails
- tags: RPBow_80320EFC,fn_80320EFC,gpr
- scope: fn_80320EFC

symptom: b12 n-1 r31 vs r28 (4 lines); final block ctx r4 vs r5 + vA0 load order (6 lines)
cause: n-1 is IRO CSE @681 with 31 neighbours, stuck; sim says it needs 2 fewer neighbours or vreg ~100-150. ctx: no visible r4 neighbour in target
fix: none. Dead: lerp value local before sprintf, k split/uninit, Set(const&), struct copy, holder ptr, ctx before outer if, field assignment; tx/ty locals fix load order only (same score)
