# RPGraphics data 85.6% -> 100%: vtable sizes, lbl_ names, split-range alignment pad

- status: works
- tags: rpgraphics,data,symbols.txt,splits.txt,vtable,objdiff
- source: worktree claude/rpgrp-data-1104

symptom: graphics category data 85.58% though all units code-100% and DOL identical
cause: objdiff counts a data symbol matched only at 100%: vtable sizes in symbols.txt included alignment pad (0x10 vs 0xC, 0x28 vs 0x24), RecordBuffer vt was 0x14 vs real 0x18, View vtables/sClipper still named lbl_ (no name pairing), stray gap_ symbol in sbss, sdata2 range included 4B linker pad
fix: Trim/correct sizes, rename lbl_ to real mangled names, delete explicit gap_ symbol line, end the split range before the pad (Renderer .sdata2 end 0x804C1894); dtk split --no-update; DOL 0 diff each time. Remaining artifacts (weak strings, @N locals) do not count
