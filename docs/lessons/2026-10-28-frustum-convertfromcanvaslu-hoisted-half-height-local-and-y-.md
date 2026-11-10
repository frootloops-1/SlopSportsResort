# Frustum ConvertFromCanvasLU: hoisted half-height local and Y-first store order are worse

- status: fails
- tags: frustum,fpr,getscreentoview
- scope: egg/gfxe/eggFrustum

symptom: GetScreenToView(VEC3) LU branch: y in f3 vs f6, neg/frsp colours differ (26 lines, 18 DOL bytes)
cause: colouring of the inlined LU temps is not moved by store order or a named half-height local
fix: none: 'f32 hy = size.y/2; *pY=-(-(hy-y))' -> 31 lines, 16/18 fns (98.46); pY computed before pX -> 32 lines (99.57). Header restored. Parked after 2 tries
