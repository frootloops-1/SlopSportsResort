# fn_802D7920: li r3 vs r4 is the prepass scheduler placing mr r3,self between li base and lfs 4(base)

- status: fails
- tags: fn_802D7920,RPBox_802cf93c,scheduler,mwcc_dbg
- scope: RPBox_802cf93c
- source: claude/box802cf-r2-1029 opus

symptom: li r4,lbl_804C4DF0 / lfs f1,4(r4) vs target r3 (4 lines)
cause: mwcc_dbg backend-02: prepass order li r37; lfs; lfs s; mr r3,r32; lfs f37,4(r37), so the base interferes with r3. Initial/optimized order has s loaded first (named s or inline param t)
fix: failed: no s local (lbl read in both lerps), fn_802D9790()/fn_802D976C() calls (inlined, same), direct lerp expressions in the call (92.9), inline BoxGloveScale(b) loading t in the body (93.0)
