# fn_80200600 a/loop-ptr r28/r29/r30 swap in else-branch: levers flat (parked 99.9)

- status: fails
- tags: fn_80200600,regalloc,forecast

symptom: target a=r29, second loop ptr=r29; ours a=r28, ptr=r30
cause: unknown; separate-branch webs coloured differently
fix: failed: single function-scope s32 i reused by all loops (99.9->99.5); non-const SpAnm2* a without const_cast (flat). Diagnoser lever 1 wrong, lever 3 (inline getter) untested/no accessor evident.
