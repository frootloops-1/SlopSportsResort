# Duplicated flag stores: compute local u8 then store once

- status: works
- tags: mwcc,flag,store

symptom: stb duplicated into both branches
cause: ternary/bool local form differs
fix: u8 flag assigned in if/else then self->flag = flag
