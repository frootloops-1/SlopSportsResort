# Chained castToBounding: assign to local before isInsideBounding

- status: works
- tags: mwcc,chain,regalloc

symptom: layout ptr loaded early into extra saved reg
cause: chained call evaluation order
fix: local = castToBounding(pane) first
