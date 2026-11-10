# Struct return from two floats: assign y before x to fix f0/f1

- status: works
- tags: mwcc,regalloc,float
- source: RPGol_802b90b4

symptom: f0/f1 swapped, 99.6
cause: assignment order drives FPR allocation
fix: v.y=m.m[7]; v.x=m.m[3];
