# int vs s32 loop index controls MWCC unroll

- status: works
- tags: loop,unroll

symptom: 4-trip loop fully unrolled but original uses ctr loop unrolled x2
cause: s32 is long; long index fully unrolls, int index gives partial unroll
fix: declare the loop index as int (fn_801E05A8)
