# fn_80257804 (RPBsb_802564b4): natural lbl[i*4+j-1] indexing fixes IV init order but merges row/p

- status: fails
- tags: RPBsb,induction,regalloc,park
- scope: fn_80257804
- source: worker nm64b4 2026-10-31

symptom: li r22 (i*16 IV) before li r29 (i*4 IV) in outer preheader
cause: IV creation order; row=lbl+i*16 computed before the inner loop creates the i*16 IV first
fix: Failed: natural lbl[i*4+j-1] gives right li order but row/p collapse (95.9); row var + natural inner index 94.7; 2D-array cast 94.2; named last=i*4+3 before row 99.6; signed i*16 94.3
