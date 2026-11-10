# resort: loop entry compare appears only when wrapped as if (count > 0) for (...)

- status: works
- tags: resort,bowling

symptom: missing entry test on for loop
cause: MWCC loop shape
fix: fn_804E488C 86.6 -> 95.2; residual loop counter r30 vs r12
