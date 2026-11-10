# Duplicate identical string literal under -str reuse: one copy has an explicit NUL

- status: works
- tags: sdata,string-literal,str-reuse,NWC24
- scope: revolution/NWC24/NWC24MsgCommit
- source: NWC24MsgCommit sdata session 2026-10-26

symptom: orig .sdata holds two \r\n objects (same visible bytes), mine merges them; pool_strings/dont_reuse_strings/casts/inline/order no effect
cause: -str reuse keys on size+bytes; padding hides that one copy is "\r\n\0" (size 4); dont_reuse_strings is read at codegen (end of file) and makes a new object per inline expansion
fix: write one occurrence as "\r\n\0"; @N names in symbols.txt come from tools/pool_renames.py on our own build, not evidence. Dead global fn holding a literal: literal is stripped at link with the fn (DOL -4)
