# Weak duplicates (policyTable, inline vtables, @STRING@) break objdiff data sections

- status: works
- tags: weak,data,sdata,objdiff
- scope: RPBsbScene
- source: RPBsb_80283fe0/8025a3e8

symptom: .sdata/.data <100 with an extra weak object (GetAnmPlayPolicy policyTable, __vt__11RPGrpScreen, EGG @STRING@)
cause: our TU emits weak copies the linker discards for an earlier unit's copy; the retail split never had them
fix: "strip": [names] in tools/reloc_patches.json: reloc_patch drops the definition (bytes, shifts later symbols/relocs) and leaves an undefined global
