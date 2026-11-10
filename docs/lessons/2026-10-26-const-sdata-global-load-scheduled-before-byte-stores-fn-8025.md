# Const sdata global load scheduled before byte stores (fn_80254AAC)

- status: works
- tags: scheduling,alias,const,sdata,lfs
- scope: RPBsb_80252e7c/fn_80254AAC
- source: forecast-regalloc

symptom: lfs of sda global placed first, pool 0.0f lfs after li; target loads 0.0f first; regs/order 4-line diff at 97.8
cause: non-const global load must precede the following stb (may alias), so it becomes first in schedule; a const global has no alias dep, so the 0.0f pool load wins the tie
fix: declare extern const f32 + define __declspec(section ".sdata") const f32 lbl = v; 97.8->100. Forecast levers 1/2/6/8/9 (decl order, f64 type, reference copy, store order, inline-param helper) were all flat
