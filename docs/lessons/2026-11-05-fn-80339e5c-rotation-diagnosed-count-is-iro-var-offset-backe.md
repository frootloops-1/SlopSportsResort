# fn_80339E5C rotation diagnosed: count is IRO @var, offset backend SR temp (retail reverse)

- status: open
- tags: colouring,iro,induction-variable,loop-bound,fn_80339E5C
- scope: Pack/RPSports/RPBowScene/RPBow_803381DC

symptom: const1/count/offset r31/r30/r23 rotation
cause: mwcc_dbg: (m==0)+1 loop bound CSE'd by IRO into @2192; sample*4 hoisted then strength-reduced by backend into a new temp (r107, coloured first). Retail: bound is a temp, offset an IRO IV created after the v2954 IV
fix: open. Dead: enum-typed sample/count/m/q (enum count makes it a var: worse), radii[m] (offset IRO IV but before v2954 IV: 33), sample as separate IV (30), count spellings/types/positions, inline helpers
