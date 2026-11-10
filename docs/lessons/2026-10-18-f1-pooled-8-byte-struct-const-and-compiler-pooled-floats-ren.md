# F1 pooled 8-byte struct const and compiler-pooled floats: rename/merge target lbl_ to @N in symbols.txt, do not extern

- status: works
- tags: F1,symbols,sdata2
- scope: RPSysLytPlayerSelect,RPBsb_8027039c
- source: claude/nm-data

symptom: two lwz from one pooled 8-byte const: target has two 4-byte lbl_ symbols, ours one @N size 8; extern f32 for a pooled literal changes lfs scheduling and regresses
cause: target symbol split/name differs from compiler pool symbols
fix: merge the two lbl_ into @N size 8; rename lbl_ float to compiler @N (scope:local) and use the literal everywhere; pair relocations via objdiff json to find @N
