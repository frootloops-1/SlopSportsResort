# fn_80275E34 (RPBsb_80275a44): inline param t (frsp) f4 vs a f2 swap, 10 variants flat

- status: fails
- tags: regalloc,fpr,inline
- scope: RPBsb_80275a44 fn_80275E34
- source: FPR batch 2 2026-10-28

symptom: 99.62, opcodes identical
cause: making a an expression temp does not colour it ahead of the inline param t; it shifts the clamp value instead
fix: none: a/b direct args (99.0), a/b decl orders, explicit lerp (99.3), BsbClamp inline, ternary clamp as in fn_80275F38 (95.6)
