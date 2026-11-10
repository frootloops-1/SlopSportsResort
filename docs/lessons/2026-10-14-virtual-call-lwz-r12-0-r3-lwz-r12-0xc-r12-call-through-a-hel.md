# Virtual call lwz r12,0(r3); lwz r12,0xc(r12): call through a helper class

- status: works
- tags: virtual,vtable,codegen
- scope: RPTns_8022c304
- source: sonnet worker 2026-10-14

symptom: explicit void** vtable cast gives lwz r4/r12 instead of r12 chain
cause: only a real C++ virtual call emits the r12 sequence
fix: cast self to a helper struct with N virtual decls and call the one at the slot offset (first virtual is +8)
