# Colouring order: named local numbering decides who is coloured first; IRO strength-reduced pointer vs named p710 (Calculate PlayerSelect closed)

- status: works
- tags: regalloc,mwcc_dbg,colouring-order,vreg-numbering,induction,RPSysPlayerSelectScene
- scope: Pack/RPSports

symptom: Calculate 99.9: loop-1 &info+4i pointer r29, target r27 (and counter r28); 15+ declaration/loop-form variants left 8 lines
cause: mwcc_dbg: named locals get vregs r33.. (sibling scopes in reverse program order, inner scopes first, declaration order within a scope); IRO-created IV/webs get numbers above all locals (IV r44, second web of i r37). Colouring is descending vreg, each node takes the lowest used free callee-saved reg. The IV (r44) was therefore coloured before named p710 (r33) and took r29; target needs ptr after p710 and before the loop-1 counter
fix: write the loop-1 walk as a named s32* p over the info struct (p[1]/p[5], i++/p++ in the for) and declare locals in the order i, p710, p (p710 assigned in the loop body): FLIP-OK, DOL 0. It is a steering cast (MATCH-PENDING R17, ledger row 133). Method: dump with mwcc_dbg, list nodes in regalloc-gpr-pass-1-assigned.txt order, map vregs to pcode in backend-02. mwcc_dbg 256MB crash: raise BoxMem::new(256<<20) in win32/src/machine_emu.rs and MemImpl::new in machine_unicorn.rs to 1024<<20, rebuild with cargo build -p retrowin32 -F x86-unicorn --profile lto --offline (43s), run with OGWS_TOOLS pointing at a dir holding that copy plus a mwcc-debugger symlink
