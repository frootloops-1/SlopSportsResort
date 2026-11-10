# Pool order follows generation order: unused zero local goes in lowest-address fn

- status: works
- tags: sdata2,literal-order
- source: RPBsb_802734e0

symptom: 0.0f not first in .sdata2
cause: functions generated in reverse source order
fix: put unused 'f32 zero=0.0f' in the function generated first (lowest address, last in source); a*v+b pools addend before multiplier
