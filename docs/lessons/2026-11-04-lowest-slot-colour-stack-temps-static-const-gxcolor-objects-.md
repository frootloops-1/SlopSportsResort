# Lowest-slot colour stack temps = static const GXColor objects copied whole (b340 D40C/D0EC)

- status: works
- tags: stack-slot,gxcolor,sdata2,symbols,static-const
- scope: RPSportsCommon/RPSports_8020b340
- source: claude/b340-1104e 6249d6fbf

symptom: colour locals at wrong stack slots; sdata2 colour bytes split into byte labels
cause: Retail colours are 4-byte static const _GXColor objects; whole-struct copies in loops are hoisted into stack temps created after all inline expansions (lowest slots). Field reads cache the address instead
fix: symbols.txt: size-4 local objects, drop byte labels; source static const _GXColor; copy via const& param inside inline (scaleAlphaRef, compute s before c=src). D40C, D0EC -> 100
