# Zero table entry break at loop top

- status: works
- tags: mwcc,loop
- scope: RPGol_802b66c4
- source: opus-worker

symptom: branch to post-loop on zero entry
cause: loop shape
fix: if (!tbl[i]) break; as first statement
