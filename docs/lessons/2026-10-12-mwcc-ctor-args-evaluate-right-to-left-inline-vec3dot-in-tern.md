# MWCC ctor args evaluate right-to-left; inline VEC3Dot in ternary arg gets high FPR

- status: works
- tags: mwcc,regalloc,fpr,vec3,ctor,args,FSqrt,VEC3Dot
- scope: Pack/RPGraphics/RPGrpModelRecord Lerp
- source: claude subagent 2026-10-12

symptom: VEC3(x,y,z) built from three FSqrt calls: asm computes z then y then x; a dot-product value living across the calls had wrong FPR (f22 vs f31) and fmuls operand order swapped
cause: MWCC evaluates call/ctor args right-to-left; a separate f32 dot local gets a different virtual-reg priority than the same expression inlined into the arg
fix: Write VEC3 s((VEC3Dot(&c0,&cross) > 0.0f ? 1.0f : -1.0f) * FSqrt(...), FSqrt(...), FSqrt(...)) with the dot inline in the x arg; also declare QUAT result before the two inputs to get stack order (later-declared = lower offset)
