# fn_80313F60: r0 colouring needs const-1 vreg numbered above the w8 tmp; more variants flat

- status: fails
- tags: regalloc,colouring,RPBow
- scope: RPBow_80313028

symptom: li r4,1 vs target li r0,1; lwz r0 vs lwz r3,8(r3)
cause: dump: li=r48 (declared early), reloaded tmp=r50; descending-vreg colouring colours tmp first so it takes r0; target needs 1 coloured first (higher vreg) - not reachable from source order
fix: failed: plain/true literals, int-returning inline one(), isZero inline, switch(w8), local pointer a, (bool)p->w124, s32 one local, ternary
