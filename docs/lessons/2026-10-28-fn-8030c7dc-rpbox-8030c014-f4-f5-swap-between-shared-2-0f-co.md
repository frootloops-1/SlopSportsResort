# fn_8030C7DC (RPBox_8030c014): f4/f5 swap between shared 2.0f constant and BoxLerp t ignores every class change

- status: fails
- tags: regalloc,fpr
- scope: RPBox_8030c014 fn_8030C7DC
- source: FPR batch 2 2026-10-28

symptom: 99.56
cause: CSE'd constant vs inline param swap not reachable by named t, sibling fn_8030C9A0 shape, accessor inline for k, or operand swap
fix: none; park
