# DrawPathDOF Draw residues parked: fog near/far hoist, alloc temp slot, loop FPR colouring

- status: fails
- tags: eggDrawPathDOF,register,scheduling,park
- scope: egg/gfxe/eggDrawPathDOF
- source: claude/dof-1027

symptom: internalDrawStandard 99.3 (GetNear/FarZ loaded before fog colour copy), internalDrawLite 95.8 (alloc w temp slot 0xc0 vs 0xc8; f26/f28 swapped)
cause: post-RA scheduling / stack-slot and FPR colouring residue
fix: failed: fog start/end locals 97.7, SetFog inline helper 97.6, compound literal colour same; alloc /2.0f direct worse, u16 h/w locals same, calcLayerZ/Alpha helpers 95.6
