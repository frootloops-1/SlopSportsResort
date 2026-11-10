# Constant FPR colours above f0/f1 because it doubles as a later call's float arg: fix the callee prototype

- status: works
- tags: regalloc,fpr,constant,call-args,prototype,cse
- scope: RPBox_802f9f50 fn_802FA180
- source: forecast-regalloc

symptom: pool constant (e.g. 1.0f) loaded into f2/f4 instead of f0 for a fdivs, register-only diff that ignores every declaration-order/helper rewrite
cause: MWCC CSEs the constant with an identical literal argument of the following call, so its live range reaches the bl and it interferes with the precoloured arg regs; our extern prototype dropped that float param
fix: check the callee's real signature (fn_801BA634(void*, f32 radius, f32 mass)) and pass the literal: fn_801BA634(o, tbl.f04, 1.0f); same reason cf93c's BoxSetMass+fn_801BA6B0(...,1.0f default) gets f4. fn_802FA180 99.9 -> 100
