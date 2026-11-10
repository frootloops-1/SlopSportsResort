# fn_801E59FC closed: change an index param in place in the inline helper (pair *= 2)

- status: works
- tags: inline,param-temp,fold,801E51B4
- scope: RPSports_801E51B4
- source: orchestrator+decomp-hard 2026-11-03

symptom: retail has N separate hoisted zero copies (mr rX,r_i0), add base+i*8 once per call and (i+1)<<3 recomputed; ours folded +8 into the displacement and shared one zero reg
cause: unmodified inline params are substituted and folded; a modified param stays a real temporary
fix: selectionDisablePair: 'pair *= 2;' then button[pair]/button[pair+1] -> 86.5 -> 100, no marker
