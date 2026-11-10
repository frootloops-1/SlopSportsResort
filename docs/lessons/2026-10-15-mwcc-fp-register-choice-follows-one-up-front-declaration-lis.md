# MWCC FP register choice follows one up-front declaration list; auto_inline off for same-TU callee

- status: works
- tags: mwcc,registers,inline-deferred,RPBox
- scope: RPBox_802e9774

symptom: float helper regs swapped (f12/f31); small extern C callee inlined into caller
cause: -inline deferred inlines small same-TU callees; f-reg order tracks declaration order of locals
fix: #pragma auto_inline off around callee; declare all float locals in one list and reorder (93.6->99.6); permuter moved a Lerp statement 93.6->99.1
