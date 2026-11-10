# resort: Swordplay classes carry Shift-JIS debug names via a 0xC getName virtual; Swordplay runs to end of .text

- status: works
- tags: resort,splits,swf,vtable
- scope: resort
- source: swf-template-batch-2026-11-09

symptom: no singleton creates or qualified strings in Swordplay, so no file names
cause: each class has vtable {0,0,0x802037E0,getName,dtor} and a Shift-JIS name string in .data (薪割り Speed Slice, 対戦 Duel, 組み手 Showdown)
fix: decode the getName strings for class-level file cuts and sub-game attribution; Swordplay is 0x805EFD7C-0x80653FA0 incl. the unsplit tail after the last __sinit
