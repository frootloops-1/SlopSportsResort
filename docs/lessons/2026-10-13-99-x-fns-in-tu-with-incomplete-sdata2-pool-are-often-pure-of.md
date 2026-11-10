# 99.x fns in TU with incomplete .sdata2 pool are often pure offset diffs

- status: works
- tags: sdata2,triage
- scope: RPGol_802b614c
- source: opus-worker

symptom: fns at 99.1-99.9 with identical asm
cause: pool offsets shift until all users are written
fix: write the remaining fns first before chasing these
