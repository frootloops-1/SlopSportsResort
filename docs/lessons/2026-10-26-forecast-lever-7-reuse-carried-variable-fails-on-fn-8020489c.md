# forecast lever 7 (reuse carried variable) fails on fn_8020489C/fn_801F0020

- status: fails
- tags: forecast,regalloc,reuse-variable
- source: forecast-regalloc

symptom: register rename on a value derived from a load (fn_8020489C reusing outer 'mode'; fn_801F0020 'best -= f30')
cause: reusing the carried variable either was the existing wrong shape (fn_8020489C: reuse of 'mode' gave r29, target r31) or added instructions (fn_801F0020: 8 lines, -1 regression)
fix: no gain; prefer one named local shared by sibling branches (fn_8020489C) or a float-typed named result (fn_801F0020)
