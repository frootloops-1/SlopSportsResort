# li r0,3; bne; li r0,4 select pattern

- status: works
- tags: mwcc,branch
- source: RPGol_802b90b4

symptom: else-if chain gives cntlzw/addi
cause: wrong source shape
fix: v=3; if(x==100) v=4;
