# CpuTexture setColor: if/else-if chain and swapped case order are worse

- status: fails
- tags: cputexture,setcolor,switch,shape
- scope: egg/gfxe/eggCpuTexture

symptom: setColor I8 red r0 vs r8, offset r6 vs r0 (8 lines, 6 DOL bytes)
cause: switch-shape hypothesis (untried before): control flow is not the lever; colouring order is set inside the I8 block
fix: none: switch -> if (fmt==RGBA8) else if (fmt==I8) gives 17 diff lines (.text 99.52); I8 case before RGBA8 gives 32 lines (97.75). Baseline switch kept (8 lines). Parked after 2 tries per Opus-ceiling rule
