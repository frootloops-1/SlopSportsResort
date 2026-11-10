# Const-const float subtraction folded from by-value inline args

- status: works
- tags: float,fold,inline,sdata
- scope: RPGol_802c58d4
- source: claude/rpgolscene-unsplit

symptom: orig fsubs of two literals (0.005-0.0); ours folds to one literal
cause: by-value inline params propagate constants
fix: copy the arg into a local inside the inline (float hi = in1; d = hi - in0); a const float& param also stops the fold but puts the literal temp in .sdata (wrong)
