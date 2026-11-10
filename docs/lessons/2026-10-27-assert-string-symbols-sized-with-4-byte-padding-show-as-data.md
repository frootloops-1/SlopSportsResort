# Assert-string symbols sized with 4-byte padding show as .data <100% (SIZE-MISMATCH 12!=9)

- status: works
- tags: data,string,symbols,objdiff,egg
- scope: egg/gfxe/eggDrawPathBase
- source: drawpathbase-1027

symptom: eggDrawPathBase .data 95.42% with .text 100%; @STRING@getScreen__Q23EGG7IDrawGXFv(@0) at 78.8/85.7%, unit_cmp SIZE-MISMATCH 12!=9, 20!=13
cause: symbols.txt gave the inlined-assert string literals the padded sizes (0xC/0x14) and scope:global; compiler emits exact string lengths (9/13) as weak data:string
fix: set size to the real string length (0x9, 0xD), scope:weak data:string, re-run dtk dol split; .data 100%, DOL still 0 bytes
