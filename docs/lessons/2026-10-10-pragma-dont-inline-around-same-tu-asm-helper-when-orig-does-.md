# #pragma dont_inline around same-TU asm helper when orig does bl (RPGolMapObjTree fn_80296C7C 78->98%)

- status: works
- tags: rpgolmapobjtree,dont_inline,inline-asm
- scope: RPGolMapObjTree
- source: sonnet

symptom: same-TU helper inlined, orig calls it
cause: MWCC auto-inline
fix: #pragma dont_inline on / reset around the helper definition
