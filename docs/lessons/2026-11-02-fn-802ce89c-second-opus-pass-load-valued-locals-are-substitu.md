# fn_802CE89C second Opus pass: load-valued locals are substituted even when multi-def; GXColor slot not reachable via helpers

- status: fails
- tags: regalloc,copy-propagation,gxcolor,RPBox_802cb9cc
- scope: RPBox_802cb9cc fn_802CE89C

symptom: 99.9%, 26 lines: case-0 r5/r6 swap, plus white GXColor single stack slot
cause: Front end substitutes a load-valued local into its use unless a store or call sits between def and use, regardless of use/def count (dbg4). Target needs p9C/p438 as low CSE temps with kind/mode stores first; no natural shape. Case-0 block B7 has 17 pcodes, so the ~100-pcode block split does not apply (H5 hoisting is order-preserving scheduling). GXColor is a stack-slot assignment issue, so the declare-last lever does not apply.
fix: No source found. Dead: inline member getter BoxGame::Judge() with named e (transparent), static inline BoxFadeWhite() holding GXColor local + fn_801F5634 call (two slots kept: 0xc and 0x8), &(GXColor){...} passed directly (two slots), function-scope judge/game reassigned at several sites (substituted away). Only #pragma cplusplus off closes the slot (99.922, 14 lines, DOL 7 bytes), still blocked by case 0. Parked after two Opus passes (4 stages total); revisit only with a new idea for case 0.
