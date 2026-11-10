# Rename assert-string labels across lanes together

- status: works
- tags: egg,assert,symbols,integration
- scope: egg/gfxe
- source: claude/gfxe-1021

symptom: function drops after merging lanes (ShadowTexture Calc 100->9x)
cause: one TU externs lbl_ strings another lane renamed to @STRING@ weak names
fix: call the real header inline (e.g. PostEffectBlur::getBlurData) so the weak @STRING@ name is emitted; avoid extern lbl_ string hacks
