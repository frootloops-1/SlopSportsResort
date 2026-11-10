# PostEffectBlurSimple::setMaterialInternal FPR constant colouring + KColor load hoist: 8 forms no gain

- status: fails
- tags: egg,PostEffectBlurSimple,fpr,GXColor,hoist
- scope: unit

symptom: 98.6%: target 0.0f const in f25 (lowest) vs ours f30; radius/offset f27/f26 vs f26/f25; and lwz of color slot after GXSetNumTevStages is hoisted into r30 before the bl (target lwz r0 after bl)
cause: FPR colour priority of the 0.0 constant differs; load hoist unexplained
fix: failed: using makeBlurTexMtx inline (94.2, stack slots change), y->center.z (94.4), field-wise GXColor init (97.8), explicit kc=color copy (same), late kc decl (95.5), const GXColor (same), static-inline const GXColor& setter (same), compound literal in call (97.1), decl color after GXSetNumTevStages (97.1)
