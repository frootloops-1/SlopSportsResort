# MWCC FPR callee-saved order across loops; store-only constants colour late

- status: works
- tags: regalloc,fpr,callee-saved,hoist,loop
- scope: global
- source: claude/b340-1104f 9fcaa5273

symptom: hoisted float constants in wrong callee-saved FPRs across two loops
cause: A callee-saved-needing node takes the lowest free already-handed-out callee-saved reg, else next new (f31 down); which loop's constants colour first decides order. Store-only constants drop out of the across-call group and colour late
fix: Function-scope uninitialised local before another named local (f32 z; f32 step = 2.0f;), assigned in the later loop. C878 91.3->91.5
