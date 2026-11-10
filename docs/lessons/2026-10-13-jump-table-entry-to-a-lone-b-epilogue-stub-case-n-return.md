# Jump-table entry to a lone b-epilogue stub: case N: return;

- status: works
- tags: switch,jumptable,return
- scope: RPGol_802c16a4
- source: claude/rpgolscene-unsplit

symptom: orig has a separate b stub for one case
cause: break merges into common exit
fix: case N: return; instead of break
