# fn_802F6E80 permuter 10 min -j2 (~3000 iters) no state beats base 35

- status: fails
- tags: permuter,rpbox,modulo,regalloc
- scope: fn_802F6E80
- source: claude/pm1-1028

symptom: fn_802F6E80 99.77%, 4 swapped regs in mulhw/add/srawi/srwi/add chain
cause: permute.py setup (C++ stand-in, --name fn_802F6E80 --static) starts exact-to-object (4 diff lines, score 35); 10 min, 3037 iterations, 485 compile errors: no candidate below 35, so the quotient/sign-term colouring is not reachable by permuter-level source mutations either
fix: none: do not rerun; park (needs scheduler/regalloc-level insight, not spelling)
