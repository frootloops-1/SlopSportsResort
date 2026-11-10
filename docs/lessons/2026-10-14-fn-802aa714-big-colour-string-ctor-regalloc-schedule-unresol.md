# fn_802AA714 big colour/string ctor: regalloc/schedule unresolved

- status: fails
- tags: ctor,scheduling
- scope: RPGolScene
- source: claude/rpgol-family

symptom: 36.6%: same instrs/frame; target keeps table base in r16 early, spills colours 14-16
cause: unknown
fix: Not found: local table ptr, by-value setter, unsized extern, reorder/reverse colour blocks, named const colours (32.4), locals at top
