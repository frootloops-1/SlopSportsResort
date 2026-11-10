# Byte setter via pointer temp matches

- status: works
- tags: regalloc,setter,byte

symptom: fn_801BB8BC 6 GPR diffs with sample/cursor temporaries
cause: need address temp before store
fix: u8* p = &self->samples[cursor - age + (age>cursor?length:0)]; *p = *value;
