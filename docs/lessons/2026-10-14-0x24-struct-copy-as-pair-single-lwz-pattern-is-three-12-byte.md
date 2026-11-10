# 0x24 struct copy as pair/single lwz pattern is three 12-byte structs

- status: works
- tags: struct-copy,lwz,codegen
- scope: RPTns_80218e84
- source: sonnet worker 2026-10-14

symptom: copy emitted lwz pair then single repeating (0 pair, 8 single, 0xc pair, 0x14 single)
cause: source copies three consecutive 12-byte u32[3] sub-structs, not one 0x24 blob
fix: declare struct of three 12-byte members and assign each
