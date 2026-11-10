# LightManager CalcView: inline-returned base pointer closes callee-saved swap

- status: works
- tags: regalloc,LightManager,inline,vreg-order,egg
- scope: egg/gfxe/eggLightManager

symptom: pObjSet r23 vs retail r25, CSE'd (u16)i<<2 r25 vs r23
cause: GPR colouring is descending vreg number after high-degree nodes; named locals have the lowest vregs so are coloured after every @N temp incl. the CSE'd index shift
fix: static inline GetObjSet(m_pObjSet, viewNo) returning &p[view*8] (an @N temp) + InitGX(&pObjSet[i]) without a named cursor -> 100 (MATCH-PENDING R17, ledger row)
