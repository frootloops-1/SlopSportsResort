# fmadds operand order: x / 2.0f gives var-first, 0.5f * x gives const-first

- status: works
- tags: RPBow_80320EFC,fn_80320EFC,operand-order,fmadds
- scope: fn_80320EFC

symptom: fmadds f1,f22,f1,f20 (var, const) in target vs ours (const, var); swapping source operands of 0.5f*w has no effect
cause: front end canonicalises constant-first for a literal multiply; a division by 2.0f is turned into *0.5f with the variable first
fix: write w / 2.0f + ox and oy - h / 2.0f - 80.0f (harness 12 -> 10)
