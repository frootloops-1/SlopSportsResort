# permute.py setup strips inlined static helpers: use --keep-bodies; stock baselines were 442/90/65/279 lines vs real 6/30/15/49

- status: works
- tags: permuter,setup,keep-bodies,tooling,inline
- scope: tools/permute.py
- source: orchestrator-1027

symptom: setup reported starting mismatch 442 for VFiPFENT_ITER_DoGetEntry (real diff 6); base.o was empty (static target unreferenced) and later 341 vs 442 insns because helpers lost their bodies
cause: strip_other_fns turns non-inline static helper bodies into prototypes unless -ipa file, so -inline auto cannot inline them in the stand-in
fix: python3 tools/permute.py setup --keep-bodies <unit> <fn> keeps every non-asm body and scores only the target via objdump --disassemble. Baselines then 6/15/15/52. compile.sh needs ABSOLUTE paths (it cd's to the repo root).
