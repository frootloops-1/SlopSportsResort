# Loop over struct array in self: take entry pointer inside loop body

- status: works
- tags: loop,regalloc
- scope: RPGol_802ae9ec
- source: fn_802AEAA0

symptom: mr base + 0x6c offsets or outer e++ reg swap
cause: indexing form
fix: GolEntry* e = &self->e[i]; inside the loop (addi r30,r27,0x64; 0x8(r30))
