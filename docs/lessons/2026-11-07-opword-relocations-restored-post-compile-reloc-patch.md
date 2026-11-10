# Opword relocations restored post-compile (reloc_patch)

- status: works
- tags: opword,reloc,objdiff,asm,R17
- scope: RPBoxScene
- source: 2026-11-07

symptom: DOL-exact asm function stays <100 in objdiff: opwords (template symbol, @STRING@, addic.) carry no relocation
cause: CW inline asm cannot spell those symbols or relocate addic.
fix: list the fn in tools/reloc_patches.json; tools/reloc_patch.py (run after mwcc) copies the retail split object's relocations at identical opcode bytes, zeroing the field, adding undefined globals + .comment records
