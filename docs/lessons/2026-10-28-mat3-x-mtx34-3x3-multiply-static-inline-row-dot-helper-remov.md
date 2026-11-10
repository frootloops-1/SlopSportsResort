# Mat3 x Mtx34 3x3 multiply: static-inline row-dot helper removes FPR swap and comma hack

- status: works
- tags: fpr,fmadds,helper,mtx33,fn_80295388
- scope: RPGolUtlMtx

symptom: fn_80295388 99.8%, f1/f9 swapped between two fmadds results; inline expression + (0,expr) comma hack + extra block
cause: inline expression tree gave different vreg order; a per-row dot helper reproduces original inlined-callee structure
fix: static inline f32 Col(const Vec* r, const Mtx b, int c){return r->x*b[0][c]+r->y*b[1][c]+r->z*b[2][c];} and SetVec(&m->r0, Col(&t.r0,b,0), Col(&t.r1,b,0), Col(&t.r2,b,0)) per column -> 100%; no comma hack/block needed
