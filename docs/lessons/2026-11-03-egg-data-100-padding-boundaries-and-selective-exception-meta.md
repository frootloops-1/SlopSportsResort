# EGG data 100: padding boundaries and selective exception metadata

- status: works
- tags: egg,data,padding,symbols,jumptable,extab,relocation,exceptions,R17
- scope: egg (11 units)
- source: 2026-11-03; build/evidence/egg-data-20261103/; dtk abs relocation syntax verified in https://github.com/encounter/decomp-toolkit/blob/main/src/obj/relocations.rs

symptom: EGG code 100 and all 84 units complete, but data 97.24% (24964/25672). Eleven units contain inexact scored data/BSS sections although the linked DOL is already exact.
cause: Eight named alignment-gap objects are real zero padding, two string pools include trailing padding, ModelEx BYTE_CODE_MIX is pointer-sized, CpuTexture jump table lacks a matched name, and DrawHelper BSS registration node is 12 bytes plus 4 padding. DrawHelper helper glue and Matrix unused Vector3f destructor emit surplus exception records. Matrix cleanup descriptor also contains an unrelocated absolute Quatf destructor pointer; removing noreloc alone does not make quick_analysis infer it.
fix: Correct the owned symbol metadata: delete only explicit padding declarations (dtk emits hidden gaps), trim string pools to 35/97, pointer to 4 and registration node to 12; pair compiler-local jump table/BSS names using verified relocs. Add config.yml abs relocation at 0x8000654C to __dt__Q23EGG5QuatfFv (original word 0x800A21E8). R17 scoped exceptions-off: Matrix vector header only, DrawHelper existing force-reference glue only. Preserve actual destructor/function records. Both source-edited units retain exact functions on six GC builds; 161/161 affected target functions unchanged, all code/data/BSS sections 100, no EGG emission-order mismatch. Refreshed EGG data 25672/25672 (100%); DOL 0 bytes, only three known collisions. Extra linker-discarded ELF atoms may remain; original header settings unknown.
