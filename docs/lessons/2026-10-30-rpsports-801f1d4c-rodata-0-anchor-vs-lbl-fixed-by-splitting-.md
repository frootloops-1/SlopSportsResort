# RPSports_801f1d4c: ...rodata.0 anchor vs lbl_ fixed by splitting lbl into 4 local statics; @STRING@ name needs real EGG member inline

- status: works
- tags: data-ref,symbols,rodata,anchor,string
- scope: RPSports_801f1d4c
- source: claude/s1f1d4c-1031

symptom: 99.9 fns: lis/addi rX ...rodata.0 vs lbl_80387E58 (one 0x30 s16 table); another fn: @STRING@SpFovSetFovy__FP11SpFovScreenf vs @STRING@SetFovy__Q23EGG7FrustumFf, then lbl_804C2080__3EGG
cause: dtk merged 4 file-scope static s16[6] arrays into one global lbl; a free helper replaced the EGG::Frustum::SetFovy inline (string symbol named after the enclosing fn); block-scope extern inside a namespace-class member gets mangled __3EGG
fix: symbols.txt: split lbl into sSceneStart0/End0/Start1/End1 scope:local size 0xC (objdiff then pairs ...rodata.0 with the first local); merging into a global [4][6] array instead loses the anchor codegen (97%). Replace function-local duplicate statics with the shared file statics. Make SetFovy a member of the local EGG::Frustum view; declare its pool externs at global scope, not in the member body. 3 fns 99.9->100
