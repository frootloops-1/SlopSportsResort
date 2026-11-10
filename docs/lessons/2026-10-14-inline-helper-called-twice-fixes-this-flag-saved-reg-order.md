# Inline helper called twice fixes this/flag saved-reg order

- status: works
- tags: regalloc,inline
- scope: RPGol_802b08a0
- source: fn_802B134C

symptom: r30/r31 swap between this and flag
cause: inline body locals
fix: static inline golSe(id) called twice
