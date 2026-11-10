# CpuTexture setColor: second 15-min permuter run (6 jobs, ~7k iterations) no gain

- status: fails
- tags: eggCpuTexture,setColor,permuter
- scope: egg/gfxe/eggCpuTexture
- source: claude/cpu2-1027 sonnet

symptom: I8 red r0/offset r6 vs target r8/r0
cause: permuter only moves RGBA8 branch (x copy 'new_var' before the switch, score 475->415); the I8 branch is untouched, so it is not a source-spelling residue the permuter can reach
fix: Do not rerun; the I8 coloring needs a new structural hypothesis (types/inline helper), not random spelling.
