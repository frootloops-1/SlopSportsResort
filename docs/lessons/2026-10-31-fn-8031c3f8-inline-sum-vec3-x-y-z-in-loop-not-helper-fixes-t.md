# fn_8031C3F8: inline sum += VEC3(x,y,z) in loop (not helper) fixes temp slot; double d=__fabs(x); f32 m=d fixes fabs/frsp coalescing

- status: works
- tags: rpbow,8031c3f8,vec3,fabs,frsp,stack-slot
- source: worker flip-swing 2026-10-31

symptom: VEC3 temp slot 0x30 vs target 0x60; fabs f29,f0;frsp f29,f29 vs target fabs f0,f0;frsp f29,f0
cause: static-inline helper around the VEC3 temp moves the slot to frame end; f32 local holding BowAbs result coalesces fabs into the saved reg
fix: write sum += VEC3(pts[i].x,pts[i].y,pts[i].z) directly in the loop; use double d = __fabs(x); f32 m = d. Dead: sum += pts[i] (x,y,z load order), named VEC3 temp / VEC3Add (221 lines), pointer-walk, Vector3f temp, work0/1/2 decl order, case-4 inline helper BowRawSmall (98.2). Remaining: sum-loop ps work regs f6/f5/f4 vs f4/f2/f0, case-4 reload of index/samples.
