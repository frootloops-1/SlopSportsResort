# Const folding: 'extern const f32 x = 0.0f' defined above its use is folded into a new @N literal

- status: works
- tags: sdata2,const
- scope: RPSports_801fba3c

symptom: named sdata2 const duplicated as @N 0.0f, reloc names differ
cause: definition with initializer visible at use is folded
fix: declare extern const f32 x; use it; define it (with initializer) at end of file so uses keep the symbol reference; named consts are emitted in definition order before generated literals
