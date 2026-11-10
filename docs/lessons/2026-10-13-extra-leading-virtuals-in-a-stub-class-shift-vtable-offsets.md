# Extra leading virtuals in a stub class shift vtable offsets

- status: works
- tags: mwcc,vtable,struct
- source: RPGol_802b90b4

symptom: vtable call offsets +8 vs original
cause: stub class declared extra leading virtuals; mixing data members into it also shifted layout
fix: keep the vtable stub class virtuals-only; read fields through a separate plain struct view + cast
