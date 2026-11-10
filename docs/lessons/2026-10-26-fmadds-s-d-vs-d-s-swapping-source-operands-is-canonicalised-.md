# fmadds s*d vs d*s: swapping source operands is canonicalised; pointer ScaleAdd inline fixes it (confirms 2026-10-14 lesson)

- status: works
- tags: fmadds,operand-order,inline-helper,regalloc
- scope: RPBox_802f9f50 fn_802FA794
- source: forecast-regalloc

symptom: fmadds f4,f6(s),f5(dir),f4 in ours vs fmadds f4,f5,f6,f4 in target (fn_802FA794); writing m->dir[b].x * s + pos.x gives identical code
cause: MWCC orders commutative mul operands by vreg kind: named local s vs load temp; inside the inline k is a parameter @-var so the d->x load lands first
fix: static inline void BoxScaleAdd(BoxV3* o, const BoxV3* d, f32 k, const BoxV3* q){ o->x = d->x*k + q->x; ...}; BoxScaleAdd(&p, &m->dir[b], s, &m->pos[b]); 99.9 -> 100. Named-local reorder (forecast lever 1) and BoxV3& references (lever 6) were flat; lever 8 (copy d by value) blew up
