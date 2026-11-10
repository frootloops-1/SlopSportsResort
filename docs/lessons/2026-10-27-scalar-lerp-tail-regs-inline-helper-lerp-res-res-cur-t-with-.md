# Scalar lerp tail regs: inline helper Lerp(&res,&res,&cur,t) with res filled by field assignment

- status: works
- tags: mwcc,fpr,lerp,inline,vec3-ctor
- scope: Pack/RPUtility/RPUtlRigid fn_801BA758

symptom: from-translation vs current-position FPRs swapped (f3/f4 vs f6/f7) in t==0/t==1/else lerp
cause: open-coded lerp and VEC3 ctor for the start vector
fix: inline LerpRigid(out,a,b,t){if t==0 *out=*a; else if t==1 *out=*b; else out->x=a->x+t*(b->x-a->x)...}; VEC3 result; result.x=from->_03;... (ctor form stays wrong)
