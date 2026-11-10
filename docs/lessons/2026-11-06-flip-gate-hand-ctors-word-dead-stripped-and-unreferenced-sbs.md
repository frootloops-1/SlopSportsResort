# Flip gate: hand .ctors word dead-stripped and unreferenced .sbss hole shift DOL by 4

- status: works
- tags: flip,ctors,sbss,force_active,dol
- scope: RPBow_80323790
- source: claude/bow-80323790-1105 2026-11-06

symptom: unit 100% in objdiff but FLIP-FAIL: _dtors -4 and sda21 offsets of later .sbss floats 4 low
cause: __declspec(section .ctors) pointer without force_active is stripped by MWLD; original .sbss had a hidden 4-byte gap_ symbol (unreferenced) before lbl_804BF9C0
fix: #pragma force_active on around the .ctors pointer and around a padding u32 global at the gap address (R17). __declspec(align(8)) on the next float instead changed codegen (82.6) and broke the DOL.
