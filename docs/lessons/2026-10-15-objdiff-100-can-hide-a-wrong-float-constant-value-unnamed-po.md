# objdiff 100% can hide a wrong float constant value: unnamed pool refs compare equal

- status: works
- tags: sdata2,float,objdiff,pool
- scope: egg/gfxe

symptom: eggPostEffectBlurGather: all fns 100% but DOL differs 1 byte in .sdata2
cause: reset() stored 0.0f where original used 0.5f; both are lfs from an unnamed pool symbol so objdiff cannot see the value
fix: tools/data_diff.py --unit <u> lists missing pool atoms with their value (0.5f <- reset); always try the DOL link before trusting 100%
