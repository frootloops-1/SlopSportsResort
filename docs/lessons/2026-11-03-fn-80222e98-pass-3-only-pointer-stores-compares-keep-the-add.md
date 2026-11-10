# fn_80222E98 pass 3: only pointer STORES/compares keep the addi; nothing found that keeps it and then disappears

- status: fails
- tags: addi,fold,add-propagation,scalarize,RPTns_80222a70,fn_80222E98
- scope: Pack/RPSports/RPTnsScene/RPTns_80222a70
- source: claude/tns-2e98-1103

symptom: target keeps addi r31,mgr,0x14 / addi r5,r5,0x18 + lfs 0(rX); ours folds to lfs 0x14/0x18(mgr) (97.6 refs, 94.4 const f32* locals)
cause: Backend add-prop is blocked by any non-foldable use of the pointer: cmplw (rad==rsq) gives the exact addi/FPR shape (97.5, only the extra compare block differs). Storing the pointers into a stack-backed local struct gives the exact target body plus 3 stores and a 0x60 frame. IRO only leaves a struct on the stack if a FLOAT member is actually accessed; pointer-only structs/arrays are scalarized. The backend forwards the reloads but never removes the dead stw.
fix: none. Tried and folded (94.4): u32 casts, pointer-only structs (2 or 3 members, with operator=), pointer arrays, struct-returning inline, out-param refs, inline getters (single statement, local+return, identical-arm if), identical-arm ternaries on the pointer, copy after the FSqrt join, unrolled for(k<2) re-assignment, cursor p=mgr; rad=p+5; p+=6 (f32*/u8*/struct*), pointer-to-member, const/__restrict/scoped base, getters defined after use (-inline deferred), pragmas (opt_propagation/common_subs/strength_reduction/loop_invariants off, optimization_level 3), all 6 compiler versions. Self-compares (rad!=rad) are folded by IRO. Open: find a blocking use the backend deletes after add-prop (a dead mr from a join copy is the only candidate left)
