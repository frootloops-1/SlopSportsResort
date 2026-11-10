# RPBow_80320EFC fn_8032212C c f30/f29 residue insensitive

- status: fails
- tags: RPBow_80320EFC,fn_8032212C,regalloc

symptom: cos result c in f30 vs f29; lerp i r5 vs r4
cause: unknown
fix: none: lerp body shapes, c/s/r decl permutations and 720 top-level decl orders all give the same 25-diff result
