# resort: several @STRING@ in one TU emit in reverse header definition order

- status: works
- tags: resort,rp,data

symptom: weak strings in wrong order
cause: MWCC emission order
fix: define the accessor whose string comes later first
