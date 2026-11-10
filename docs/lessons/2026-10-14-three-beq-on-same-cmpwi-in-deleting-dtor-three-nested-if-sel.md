# Three beq on same cmpwi in deleting dtor: three nested if(self)

- status: works
- tags: dtor
- scope: RPGol_802b4f2c
- source: fn_802B55D8

symptom: missing beq
cause: nested null checks from inlined dtors
fix: if (self) { if (self) { ... if (self) ... } }
