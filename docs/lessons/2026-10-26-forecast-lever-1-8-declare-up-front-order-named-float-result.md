# Forecast lever 1/8 (declare-up-front order, named float result) flat on fn_802FA180 constant FPR

- status: fails
- tags: forecast,regalloc,fpr,declaration-order,fdivs
- scope: RPBox_802f9f50 fn_802FA180
- source: forecast-regalloc

symptom: lfs f2 (1.0f) / fdivs f0,f2,f1 in target, ours lfs f0 / fdivs f0,f0,f1 (fn_802FA180, RPBox_802f9f50)
cause: not a vreg-order problem: the 1.0f was CSE'd with the next call's third float arg (f2 precoloured) and fn_801BA634 was declared with too few params
fix: none of: uninitialised up-front decls in two orders, named f32 inv result, f32 one local first, no local, inline setter/recip helpers changed a single register
