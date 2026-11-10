# fn_8031A0E0 flag fmadds operand order: named slope local

- status: works
- tags: A0E0,RPBow,fmadds,operand-order
- scope: fn_8031A0E0
- source: round 10

symptom: fmadds f0,f4,f1,f0 vs retail f0,f1,f4,f0 for dir.x/dir.z*len2+f198
cause: Inline division expression reassociated by IRO
fix: f32 slope = dir.x / dir.z; flag = slope * len2 + self->f198 > 0
