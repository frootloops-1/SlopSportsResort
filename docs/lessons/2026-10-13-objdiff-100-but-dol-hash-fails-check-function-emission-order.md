# objdiff 100% but DOL hash fails: check function emission order

- status: works
- tags: order,dol,link,reverse
- scope: RPGolScene
- source: claude/rpgolscene-unsplit

symptom: all fns/sections 100% in objdiff, Matching flip breaks main.dol sha1, first diff at TU start
cause: MWCC here emits functions in reverse source order; objdiff matches by symbol so it hides it
fix: write functions in descending address order; confirm with dtk elf disasm <o> | grep ^.fn and dtk shasum -c config/RSPE01_01/build.sha1
