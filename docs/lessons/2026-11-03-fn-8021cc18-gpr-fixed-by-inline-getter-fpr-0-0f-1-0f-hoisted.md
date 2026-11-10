# fn_8021CC18 GPR fixed by inline getter; FPR 0.0f/-1.0f hoisted-constant swap left

- status: open
- tags: RPTnsScene,regalloc,fpr,inline-getter,MATCH-PENDING
- source: claude/tns5530-1103 88efc0184

symptom: fn_8021CC18 99.6: cam r30 vs r29 (&lbl_804A6024 swapped) and FPR f27/f28 swapped for the hoisted 0.0f (first compare) and -1.0f (rot flip stores)
cause: GPR: cam must be numbered between the VEC3Add param temp @(&lbl_804A6024) and the loop SR IVs; named cam colours last (r26), the old pc=&cam made it a codegen vreg (r30). FPR: backend constants numbered in codegen order, the first compare's 0.0f (f96) is materialised before -1.0f (f97); target needs 0.0 numbered after -1.0 (fpr_replay search: f96 -> any position > 97)
fix: const TnsCam* cam = TnsGetCam(i) inline getter (no pc) -> 99.9, GPR exact (ledger 130). FPR failed: '0.0f > cam->f14', TnsCamDot/TnsCamTan helpers (dot helper also swaps dot/k f25/f26). Next: find a source form that materialises -1.0f before the first compare, or a pre-loop dominating -1.0f use
