# fn_80339E5C 3-reg rotation is not declaration order

- status: fails
- tags: rpbow,regalloc,fn_80339E5C

symptom: const 1 r30 vs r31, count r23 vs r30, offset r31 vs r23 (99.9)
cause: unknown
fix: failed via fn_harness: all 24 orders of the 4 array locals, hoisted count, 1+(m==0), ternary, sample const/dropped, m outside loop, m<=10, cnt local
