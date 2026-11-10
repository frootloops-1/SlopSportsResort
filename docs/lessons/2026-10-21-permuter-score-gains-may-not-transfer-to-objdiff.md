# Permuter score gains may not transfer to objdiff

- status: fails
- tags: permuter,egg
- scope: egg/gfxe
- source: claude/gfxe-1021

symptom: BlurSimple setMaterialInternal permuter 375->265 (decl y before s,c) but objdiff unchanged 98.6
cause: permuter scoring differs from objdiff fuzzy score
fix: always port and re-verify; Frustum GetScreenToView 30 min no gain; fn_80097394 405->385 not ported
