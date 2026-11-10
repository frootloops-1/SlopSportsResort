# MWCC never kills loads through const T* params; target reload means non-const param

- status: works
- tags: mwcc,cse,const,alias,RPUtlCollisionChecker,fn_801BD230
- scope: Pack/RPUtility/RPUtlCollisionChecker

symptom: target reloads point->x/y/z at function end after stores to out; ours keeps first loads live in FPRs (extra regs, 82%)
cause: MWCC treats loads through a const-qualified pointer as unaffected by stores, so they are CSE'd across out-> stores; through a non-const pointer, stores kill them
fix: declare the param non-const (VEC3* point); fn_801BD230 82.2 -> 100 together with x,y,z statement order
