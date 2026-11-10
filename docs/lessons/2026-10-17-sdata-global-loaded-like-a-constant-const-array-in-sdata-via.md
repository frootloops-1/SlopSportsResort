# sdata global loaded like a constant: const array in .sdata via declspec

- status: works
- tags: scheduling,sdata,const,rpbsb
- source: RPBsb_80273950 fn_802744A0, RPBsb_8027d3ec fn_8027DC80 2026-10-17

symptom: lfs of an .sdata f32 global hoisted before LR save (802744A0) / load order vs a 0.0f literal wrong (8027DC80)
cause: global was const in the original: const loads don't alias stores so the scheduler moves them freely
fix: extern "C" __declspec(section ".sdata") const f32 lbl[1] = {v}; read lbl[0] (array blocks literal folding). DC80 also needed source order y,x,z. Do NOT use when the value is reloaded after a call in a loop (gets hoisted to callee-saved FPR)
