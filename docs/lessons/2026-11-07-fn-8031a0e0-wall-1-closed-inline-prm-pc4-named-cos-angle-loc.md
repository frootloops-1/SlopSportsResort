# fn_8031A0E0 wall 1 closed: inline prm->pC4 + named cos-angle local (no alias change needed)

- status: works
- tags: A0E0,RPBow,scheduler,regalloc,fpr,ps_mr,named-local
- scope: fn_8031A0E0
- source: round 10

symptom: v1BC/v1C8 VEC3 lerp block: extra ps_mr pair and shifted FPRs; round-8 model said c and the f19C cos arg needed whole-object aliases
cause: Retail colours need the cos arg live early pre-RA: a named local's vreg load is issued early (pending==1 successor fmr f1) and coalesces with f1; c must be a temp, not a named local
fix: Write prm->pC4 inline in both lerps and f32 rot = self->f19C; cs = -(f32)cos(rot); keep sin(self->f19C). Block exact, 97.5 -> 98.5. Found by a 0.3 s/variant brute force (scratch-A0E0-r10/gen.py, run1.py) over c named/inline x angle local placement x alias trick
