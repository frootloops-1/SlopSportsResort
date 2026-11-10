# Hand .data object of size multiple of 8 is 8-aligned

- status: works
- tags: data,align,jumptable
- scope: RPBoxScene
- source: RPBox_802e2a84 2026-11-07

symptom: hand jump table lands 4 bytes late (0x98 vs 0x94)
cause: CW aligns an object whose size is a multiple of 8 to 8; compiler switch tables are 4-aligned
fix: split: __declspec(section ".data") static void* head = e0; static void* rest[n-1] = {...}; (both force_active)
