# fn_802C5C78: ctor-arg load propagated to temp; name it to make it a variable

- status: works
- tags: fpr,colouring,inline,ctor,RPGol_802c58d4
- scope: Pack/RPSports/RPGolScene/RPGol_802c58d4
- source: opus pass 4

symptom: scalar v[0] load (GolV2 h(v[0], v[2])) coloured before the VEC3Dot work regs (ours f1, target f6)
cause: the leftmost (last evaluated) ctor arg is propagated into a codegen temp (high vreg) while v[2] stays a variable
fix: float x = v[0]; GolV2 h(x, v[2]); makes it a variable numbered below the asm work regs; then nw4r VEC3Dot (w0..w3 decl order) matches both dots
