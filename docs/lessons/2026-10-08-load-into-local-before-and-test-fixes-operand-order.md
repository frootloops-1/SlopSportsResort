# Load into local before and. test fixes operand order

- status: works
- tags: regalloc

symptom: and. operand order reversed
cause: inline load inside if
fix: u32 hold = ...; if (hold & dirs[i])
