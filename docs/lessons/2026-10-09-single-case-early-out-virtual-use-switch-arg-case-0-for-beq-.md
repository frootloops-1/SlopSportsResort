# Single-case early-out virtual: use switch(arg){case 0:} for beq-body/b-end shape

- status: works
- tags: switch,branch,virtual
- scope: RPGolMain

symptom: cmpwi; beq body; b end prologue; plain if(arg==0) emits bne end (97.5%)
cause: compiler branch layout
fix: switch(arg){case 0:{...break;}} -> 99.3% by instruction
