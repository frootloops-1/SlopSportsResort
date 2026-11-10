# F1 pooled 1.0f used via extern f32 in several fns: replace every use with the literal, delete extern, then rename target lbl_ to @N

- status: works
- tags: F1,sdata2
- scope: RPSports_80201240
- source: claude/nm-data

symptom: lfs lbl_804C21BC vs @2380; renaming alone regresses other users
cause: extern uses of a constant the compiler would pool
fix: literal everywhere + rename (RPSports_80201240)
