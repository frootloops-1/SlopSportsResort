# Weak @STRING@ assert strings resolve to another unit's copy

- status: works
- tags: weak,string,opword,asm
- scope: RPBsbScene
- source: RPBsb_80283fe0

symptom: asm lis/addi of @STRING@X differs in DOL: retail points to 0x80397E4C, not this unit's .data
cause: weak inline-function assert strings are deduplicated by the linker to the first unit's copy; CW asm cannot spell @STRING@ names
fix: emit those lis/addi as opword with the retail words (no relocation)
