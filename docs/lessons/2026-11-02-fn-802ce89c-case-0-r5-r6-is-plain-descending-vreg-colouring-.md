# fn_802CE89C case-0 r5/r6 is plain descending-vreg colouring (all nodes < K); single-use named load locals are substituted away

- status: fails
- tags: regalloc,copy-propagation,RPBox_802cb9cc
- scope: RPBox_802cb9cc fn_802CE89C

symptom: case-0 SetScore block: M must be r5, p9C/p438 loads r6 chain
cause: mwcc_dbg: M r75 (17 nbrs), p9C load r76, p438 load r77 all below K=29 so colouring is descending vreg and M loses; the target needs p9C/p438 in low named vregs with a shared +0x18 base
fix: No source found. Dead: named g/tbl with tbl->e[i] (98.8, loses +0x18 CSE), inline SetScores helper (98.8), BoxGetMain getter (transparent to CSE), g/tbl/e after kind/mode stores (substituted away), H5 interleave g/kind/tbl/mode/e (exact colours but loads hoisted above stores, 99.0/26 lines), multi-def top-level game. C-mode pragma steer alone gives 99.922 and DOL 7 bytes, so it cannot flip. Parked. Idea: a shape where kind/mode stores come first and p9C/p438 values live as multi-use variables.
