# add;cmp;bge exit;body;b head loop shape

- status: works
- tags: loop
- scope: RPGol_802a7a40
- source: fn_802A8170

symptom: loop shape/regs differ
cause: loop form
fix: for(;;){ j += s*2; if (j >= 257) break; ... } keeping s*2 inline (no step local)
