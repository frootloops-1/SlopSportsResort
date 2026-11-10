# Frustum GetScreenToView closed: named reload local lowers the frsp vreg

- status: works
- tags: egg,Frustum,fpr,regalloc,mwcc_dbg
- scope: egg/gfxe/eggFrustum

symptom: FPR wall: target frsp in place (f2,f2), y=f6 x=f4; ours y=f3 frsp f0,f3
cause: colouring is descending vreg; target needs the store-forwarded *pY reload (frsp) numbered below the x-divide temps, and y numbered below x
fix: f32 ty = *pY; before *pX /= in ConvertToNormalCC LU branch + ty/(size.y/2); call with direct rScreenPos.x/.y args (R17 marker)
