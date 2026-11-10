# Frustum GetScreenToView(VEC3) ConvertToNormalCC LU FPR coloring wall

- status: fails
- tags: egg,frustum,fpr,register,inline,frsp
- scope: egg/gfxe/eggFrustum

symptom: GetScreenToView VEC3 99.2%, 18 DOL bytes: input y f3 vs target f6, LU temps permuted, frsp not in-place
cause: pure FPR coloring of inlined ConvertToNormalCC LU branch (store-forwarded *pY with fneg+frsp)
fix: failed: -(y - sy/2) form (no change); ConvertFromCanvasLU(x,y,&x,&y) into params (drops frsp, 97.0); *pY/= before *pX/= (frsp in-place but 98.8). Weak @STRING@SetSizeX/Y and __dt__ SIZE-MISMATCH are dedup, not symbol bugs
