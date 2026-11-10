# Single-TU ...data.0 anchor levers that do not move the anchor (8027a3c4)

- status: fails
- tags: data,anchor,pool_data,weak
- scope: mwcc
- source: claude/flip-a3c4-20261031

symptom: you want ...data.0 to start after a global .data object defined earlier in the same TU
cause: MWCC places ...data.0 at the TU's .data offset 0. A strong global ahead of it, including one under __declspec(section ".data"), is included in the pool (offsets shift). A weak one drops data pooling for the whole function (individual lis/addi, 79.4)
fix: none in one TU; #pragma pool_data off around the object has no effect. Check for a TU boundary instead
