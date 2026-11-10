# Named pool const whose C uses fold to a literal: drop the name

- status: works
- tags: sdata2,pool,named,fold
- scope: RPBoxScene
- source: RPBox_802e5aac/802f1cec/802f438c

symptom: extern const f32 lbl_X declared but never defined; defining it makes C fold to a fresh literal or moves it to the pool end; non-const declspec changes codegen
cause: MWCC folds a visible const initializer; the named object must sit at its retail slot
fix: replace the name by the literal in C and asm (same pool entry), seed it in order (asm2cw --seed <unit> NAME...); symbols.txt can keep the name
