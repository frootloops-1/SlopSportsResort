# playFrame lwzx frames[index] GPR: hoist &ring->frames[index] before the loop

- status: works
- tags: mwcc,gpr,licm
- scope: Pack/RPUtility/RPUtl_801C67B8
- source: claude/rputl-c67b8-1027

symptom: fn_801C76D0 old cursor int in r5 vs r4; recordCount load scheduled before clrlslwi
cause: index<<2 must be computed before recordCount is loaded; a frames local + frames[index][i] puts the hoisted shift after it
fix: Record** frame = &ring->frames[index]; ... (*frame)[i] fixes the GPR lines (60 -> 24 with temps) but objdiff scores 97.6 < 97.9, so not committed
