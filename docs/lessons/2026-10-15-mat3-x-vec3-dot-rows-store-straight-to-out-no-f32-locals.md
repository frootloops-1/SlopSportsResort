# Mat3 x vec3 dot rows: store straight to out, no f32 locals

- status: works
- tags: regalloc,float,fmadds,locals
- scope: Pack/RPUtility/RPUtlDirMath
- source: claude nearmiss 2026-10-15

symptom: fn_801BD990/fn_801BD9F4 98.8%: f4/f5 swapped and lfs order off; earlier source hacked operand order (in->z*b.z) to get close
cause: f32 x/y/z locals then out->x=x stores change FPR allocation order
fix: out->x = b.x*in->x + b.y*in->y + b.z*in->z; (natural left-to-right, direct member stores) -> 100% for both
