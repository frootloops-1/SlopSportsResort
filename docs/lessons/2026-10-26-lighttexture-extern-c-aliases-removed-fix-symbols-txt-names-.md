# LightTexture extern C aliases removed: fix symbols.txt names to the real signatures

- status: works
- tags: egg,symbols,rename,alias,LightTexture
- scope: egg/gfxe

symptom: extern C aliases needed to reach members named after wrong signatures (draw(int), capture(const GXColor&,bool), fn_ static)
cause: symbols.txt names guessed from wrong arity; r4 compared to 0 in capture is the bool itself, draw's int unused; CW mangles statics without S
fix: rename in symbols.txt + header + definition + caller together; unit stays exact, DOL 0 diff
