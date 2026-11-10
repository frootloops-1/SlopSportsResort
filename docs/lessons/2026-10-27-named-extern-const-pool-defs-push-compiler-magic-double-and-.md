# Named extern-const pool defs push compiler magic double and 0.5f to pool end

- status: works
- tags: sdata2,pool,dol
- scope: RPUtlDohGraphSun
- source: claude/rputl-doh-1027

symptom: objdiff .sdata2 100% but DOL 80 bytes: int->float magic double and inline /2.0f 0.5 linked after all lbl_ consts
cause: extern const f32 lbl_ defs at TU end are emitted before every compiler @N entry; consts defined before use are literal-folded instead
fix: use plain float literals (original form); pool comes out in first-use order; objdiff then needs pool_renames.py --apply for lbl_ -> @N
