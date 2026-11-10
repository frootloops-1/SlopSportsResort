# forecast lever 8 (named float result) closes fn_801EFA3C

- status: works
- tags: forecast,regalloc,float-local,fctiwz,RPSports_801ef064,fn_801EFA3C
- scope: fn_801EFA3C
- source: forecast-regalloc

symptom: fn_801EFA3C 99.7%: s32 b=(s32)fn_801F8360(...); d = b - e->f30 had fctiwz reload/field load registers r3/r0 swapped vs target
cause: same as fn_801F0020: an s32 local merges into the conversion temp; target kept the call result as f32 and converted at the subtraction
fix: f32 b = fn_801F8360(...); s32 d = (s32)b - e->f30; -> 100% (with or without a named 'previous' local). Pattern '(s32)floatcall - intfield' with r0/rN swap: keep the float named, convert at use
