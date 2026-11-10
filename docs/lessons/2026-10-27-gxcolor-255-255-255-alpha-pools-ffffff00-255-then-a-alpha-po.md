# GXColor {255,255,255,alpha} pools FFFFFF00; {..,255} then .a=alpha pools FFFFFFFF

- status: works
- tags: sdata2,GXColor,aggregate,eggDrawPathDOF
- scope: egg/gfxe/eggDrawPathDOF
- source: claude/dof-1027

symptom: pooled colour literal ffffffff vs target ffffff00 (alpha byte not loaded)
cause: aggregate init with a runtime member pools 0 for that member
fix: GXColor color = {255, 255, 255, alpha}; instead of {255,255,255,255}; color.a = alpha;
