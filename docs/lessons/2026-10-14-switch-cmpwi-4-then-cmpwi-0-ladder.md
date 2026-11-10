# switch cmpwi 4 then cmpwi 0 ladder

- status: works
- tags: switch
- scope: RPGol_802b1a0c
- source: fn_802B1A34

symptom: compare ladder differs
cause: case set
fix: cases 0, 1-3 plus empty case 4: break;
