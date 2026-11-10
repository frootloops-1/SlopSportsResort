# RPUtility float near-misses: stack array for stored temps, Vector ctor vs copy, temp-then-assign, isZeroVector

- status: works
- tags: float,stack,RVO,join-moved,RPUtility,inline
- scope: Pack/RPUtility
- source: claude/nm-4 2026-10-16 sonnet batch 3

symptom: fn_801BCC84 87, fn_801BBF8C 80, fn_801C5F04 79 join-moved
cause: target stores per-iteration floats to the stack, copies VEC3 with lfs/stfs, does temp-then-copy instead of RVO, materializes a bool via mfcr
fix: f32 distances[4] array for d1..d3/face (->97.3); Vector p(c->x,c->y,c->z) not *c (->89.4); Vector3f v; v=fn() defeats RVO; isZeroVector(v) not dot(v,v)<=eps, zero branch first; if(a>x){..}else for fcmpo;ble (->95.0). Dead ends: locals all at top (93.4); fn_801BC854 by-value normals 67; decl reorder never fixes r30/r31 swaps (fn_801F9150, fn_802C531C); DrawGX bool temp
