# fn_8025291C (RPBsb_8024e9a4) PMF-state ctor 81.9 -> 99.1: base-vtable dead store, countdown loop, direct inits

- status: works
- tags: pmf,state-record,rpbsb,block-split,mwcc_dbg,reloc-name
- source: claude/bsb-2291c-1103e 937c51489

symptom: 81.9% then 92.7% with a duplicated obj=0 store; remaining colouring diff self r28/base r30 stmw r18 frame 0xf0 vs retail r30/r31 stmw r20 frame 0xe0
cause: (1) Natural dead store of the abstract base vtable (all-zero, lbl+0x14) before the derived vtable in clear() sets the ~100-pcode block split; (2) a per-record pointer temp (state=&states[6]) just before a block split keeps an unfolded addi live, costing a phantom callee-saved reg
fix: clear(): vtbl = lbl_803C5288+0x14; vtbl = lbl_803C5288; array built with countdown p=&st0; for(n=7;n>0;--n){p->clear();++p;}; every init written directly as self->stN.init(...) (no state/v locals) = 286/286 insns identical, 99.1. Remaining 0.9 is objdiff reloc-name (...data.0 anchor vs retail local @28219, same addresses/offsets), unverified by DOL since unit has other fns <100. Ledger row 150 retired (dup obj=0 marker removed). for-i loop + same store 82.8; for-i + 2 obj stores 97.7; dead stores to direct members outside the unrolled loop do not move the split. mwcc_dbg on large Pack TUs: patch retrowin32 memory 256->1024MB, cargo at ~/.rustup/toolchains/stable-aarch64-apple-darwin/bin
