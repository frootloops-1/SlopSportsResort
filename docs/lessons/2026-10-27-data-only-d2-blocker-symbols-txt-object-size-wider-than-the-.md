# Data-only D2 blocker: symbols.txt object size wider than the compiled object (trailing alignment padding)

- status: works
- tags: flip,sbss,rodata,symbols,alignment,RPBsb_80273950
- scope: RPBsb_80273950
- source: orchestrator-1027

symptom: RPBsb_80273950 code 100%, .sbss 50% (lbl_804BF818 size 8 vs 4) and .rodata 99.13%; objdump -s of built vs dtk .o differs only in a trailing zero tail
cause: symbols.txt sizes included the alignment padding (sbss ptr 0x8, string pool 0x198 vs compiled 0x191)
fix: Set size to the compiled size (0x4, 0x191); dtk adds the gap. No source change. DOL 0. Check the symbols.txt address after editing: a worker typo .sbss:0x404BF818 still built clean.
