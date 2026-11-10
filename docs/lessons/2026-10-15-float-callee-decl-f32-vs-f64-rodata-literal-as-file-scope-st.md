# Float callee decl f32 vs f64; rodata literal as file-scope static const; inline accessor moves FPR

- status: works
- tags: mwcc,rodata,fpr,RPBox
- scope: RPBox_802e9774

symptom: frsp before store; 3-float literal copied to stack; dt in wrong FPR
cause: callee declared f64; const local copies to stack; direct global read vs inline accessor
fix: declare callee f32; file-scope static const POD defined before use gives lis/addi/lfs from .rodata+0; read global via static inline f32 GetDt() moved dt to f31; enum/inline-wrapper for duplicated ternary param; volatile read reproduced repeated reload (workaround, not likely original)
