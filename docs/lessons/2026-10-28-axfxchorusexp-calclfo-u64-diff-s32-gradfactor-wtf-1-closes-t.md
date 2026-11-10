# AXFXChorusExp __CalcLFO: u64 diff * s32 gradFactor + (wtf = 1) closes the register wall

- status: works
- tags: AXFXChorusExp,CalcLFO,s64,mulhwu,register
- source: doldecomp/ogws PR AXFXChorusExp.c

symptom: 30-line register diff, 30+ spellings with (u64)diff*(u64)factor stayed at 99.80
cause: Declaring diff as u64 (sign-extended from s32 subtract) and multiplying (s64)diff by the s32 gradFactor gives the original mulhwu/srawi pattern; the shared constant 1 needs an assignment inside the index expression
fix: Use the doldecomp PR spelling; (lastNum + (wtf = 1)) and sign ^= wtf. Plain 1 or hoisted wtf = 1 regress to 99.86
