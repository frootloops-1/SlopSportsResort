# KPADRead low-callee-saved regs reversed: kp form must match the inlined callee's kp form

- status: works
- tags: KPAD,register,cse,inline,array-index
- scope: revolution/KPAD/KPAD

symptom: KPADRead 99.4: four early values in r14-r17 in reversed order, kp add scheduled before param copies
cause: KPADRead used byte-offset kp while the inlined KPADiControlDpdCallback used the same; target used &inside_kpads[chan] in both. &arr[i] in only one function leaves base/mulli CSE temps
fix: kp = &inside_kpads[chan] in KPADRead AND in KPADiControlDpdCallback -> 100; check the inlined callee's pointer form when only the caller changes
