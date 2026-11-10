# fn_801BC2B8 storage r5 vs r6 across struct copy: ~80 variants fail

- status: fails
- tags: regalloc,struct copy,rename
- scope: Pack/RPUtility/RPUtlCollisionModel
- source: claude nearmiss 2026-10-15

symptom: 99.6%: orig storage addr r5 and VEC3 pair temp r6/r0; ours storage r6 pair r5/r0
cause: unresolved; pair temps from 12-byte block copy colored before storage. Copy through self->storage (not ptr) gives storage r0 (52 lines)
fix: failed: decl positions, src/dst via locals/self->data/refs, const/void* param, inline copy/bind/setData helpers, nested ifs, user operator= (VEC3 then copies as lfs), _VEC3/Vec/anon origin type, explicit memberwise with storage mid-copy, W3/W2+single/{a,b,c} casts (sequential {a,b,c} gives storage r5 but wrong copy shape), 30 load/store permutations of explicit a/b (best: d[1]=b;d[0]=a right regs, wrong store order, 2 lines)
