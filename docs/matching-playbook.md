> **Resort note:** this playbook was written on Wii Sports (ogws). Paths and commands carry over with `RZTE01_01`;
> compiler/flag facts for Resort are in `AGENTS.md` and `docs/decompilation-roadmap.md` ("Resort differences").

# Matching playbook

Read this before starting a batch. Merges the 2026-10-24 closeout session (`docs/archive/closeout-playbook-2026-10-24.md`)
and the 2026-10-25/26 order-mismatch session. The latter records what yielded results in the function-order session
(14 units' emission order fixed, 4 units flipped to Matching with DOL 0 diff, ~14 functions closed,
8 more partially improved) and what burned time. Workers: follow "Default procedure" below.

## What paid off (in order of yield)

1. **Flip candidates first.** Units with exactly one function left and data sections already 100%
   (`tools/unit_cmp.py`) became Matching: RPSports_801CDD90, MetroTRK support.c, RPBow_803536C4,
   RPGol_802b90b4. Check data sections BEFORE spending code time; two flips were data-blocked
   (RPGol_802b90b4 `.sdata2` pool order cost a full extra round after the code was 100%).
2. **Function emission order is a DOL-level fact objdiff cannot see.** `tools/order_check.py` then reorder.
   Direction differs per unit: some units emit in SOURCE order, others in REVERSE (look at the unit's
   current `nm -n` order vs target before moving anything). Hoisting a small function above its caller can
   make it auto-inline: wrap it in `#pragma dont_inline on/reset` (RPGolPlayer `fn_8029FBEC`). Fixing order
   alone rarely raised function scores (1 of 14 units), but is required for DOL 0 diff.
3. **Structural source levers beat register fiddling.** Nearly every close was one of:
   - Wrap a statement group, or `new`+ctor, in a `static inline` helper (changes saved/volatile colouring:
     fn_803536E4, fn_802B9F90, fn_8026FBFC, fn_801CE528 clear loop).
   - Declare pointer params `const T*` (prologue `stw` vs param-load scheduling: fn_802BA878).
   - Change the branch shape: `if (a != 0 || b != 0) return;` instead of `switch (x) { default: return; ... }`
     (fn_802A0128/0164, 93 -> 100).
   - Constructor wrappers: write the body directly in the `fn_` taking `self`, not `return T();` with an
     inlined ctor (inline-param temps get reversed stack slots); make the ctor return `this` if the caller
     uses it (fn_80268A30 94.9 -> 98.4, fn_801CE528).
   - Array member + `for (s32 i...)` clear loop instead of per-member stores.
   - MWCC evaluates args right-to-left; the PMF constant table order in `.data` tells the `init` arg order.
   - Pool order: move `extern const` table definitions to the end of the TU (rodata/sdata2 order), dead literal
     statements at the top of the first generating function, or `#pragma defer_codegen off` with ascending
     source order when named consts must sit mid-pool.
   - Declaring a loop-body temp at the top of the enclosing block (callee-saved priority).
   - **Register-only residue:** follow `docs/regalloc-playbook.md` before the permuter: declare-then-assign
     declaration order, local types (merge into load temps), one-expansion loops, non-POD `AsColor` lvalues,
     `T s = *p; T& cur = s;` for forced reloads; sweep orders/types with a one-function harness.
4. **Escalate residue to Opus (decomp-hard) with a list of what was already tried.** Sonnet workers left
   the same 99.x register residues untouched; Opus re-framed them as helper boundaries.
5. **Several units per worker, one worker at a time per worktree.** Order-fix units were cheap; batching
   them kept overhead down.

## Data and symbol levers (closeout 2026-10-24; often bigger than codegen)

Objdiff scores hide these, so check them before blaming code: `verify.py`/`near_miss.py` percentages and the
objdiff JSON relocation names show them; `asm_diff.py` masks symbol names.

1. **DOL flips of 100%-code units.** One unit at a time: flip in `configure.py`, `ninja build/RSPE01_01/main.dol`,
   `dol_diff.py`, `sym_addr_check.py` (shows swapped weak/template order). A unit whose `.ctors` pointer is dead-stripped needs
   `#pragma force_active` (RPBowPlayerLaneNpc). Flipped this way: WPADHIDParser, RPBsb_8026e62c/8027c2f0, RPBowTrajectoryGuide, RPBowPlayerLaneNpc.
2. **Pool symbol naming:** `python3 tools/pool_renames.py --apply` (1,760 verified `lbl_` -> `@N` renames at once); re-run after
   every new first-source unit.
3. **Per-unit `symbols.txt` fixes** (Sonnet workers, 12 DATA-REF functions per batch, edits only inside the unit's own split ranges): merge
   split string pools into one `@stringBase0`/`lbl_` (phantom `R_PPC_NONE` addend), split one big dtk `lbl_` into per-compiler-local symbols,
   `scope:weak` for `@STRING@` assert labels, `sdata2` 8 -> 4 + gap, `jumptable_X` -> `@N`. About 45 functions went exact; see
   `docs/lessons/2026-10-18-*` and `2026-10-24-*` and `tools/data_fix.py`.
4. **`splits.txt` boundary moves** when a unit uses rodata/text owned by its neighbour (RPBowNpcManager, RPSportsKokeshiLytDebug,
   eggLightObject). Orchestrator only; needs a human-level check.
5. **Source idioms** (`docs/lessons/2026-10-24-*`): cur/prev state-join load order (`s32 prev; if (cur != (prev = self->prev))`), volatile
   re-read for loads the compiler CSEs, non-nested static-inline helper for by-value temp slot order, moving a loop-body scalar init to
   first use, `(u32)__cntlzw(x-4)>>5`, `*++p` fill loops, file-local inline copy instead of editing shared headers.
6. **Shape hints** (`tools/near_miss.py --shape`, lessons `2026-10-16-label-only-diffs-*`): moved-`<label>` near-misses are mechanical
   source-shape fixes; Sonnet batches of ~13 closed 18 functions where permuter and Opus closed none.

## Known dead ends (do not repeat without a new hypothesis)

- FPR/GPR-numbering-only functions at 99.9% (Golf Remap, lyt, Kokeshi sort loops): ~40 attempts, 0 matches. Re-test with
  `docs/forecast-regalloc-notes.md` ("Cross-check ... 2026-10-28") before parking: an inline *param* / `@N` local is coloured
  before named locals (closed fn_802D930C), and check callee prototypes for a missing FP/int arg (closed fn_8024F7C0).
- FPR colouring wall: `tools/mwcc_dbg.sh` then `python3 tools/fpr_replay.py check|analyze|search <dump> <target.s>` replays MWCC's
  sweep order (K=32) and finds which vreg needs a different number. Closed fn_801BB9B8 (named `dx`, R17) and fn_8024DD80
  (move a dead store later in source). GPR counterpart: `tools/color_sim.py`.
- **Check the objdiff JSON before chasing a 99.x "SCHEDULE pure" near-miss.** 4 of 6 such targets (2026-10-30) had byte-identical
  code (asm_diff clean) and the one "wrong" row was objdiff synthesizing a phantom `R_PPC_NONE` relocation on a target
  `subi rX,rX,4` before a `lwzu` table-copy loop: `table - 4` lands inside the previous rodata object in the target but in
  padding in ours. Diagnose: `objdiff-cli diff -p . -u main/<unit> -o x.json <fn>`, print the DIFF_REPLACE rows and their
  `relocation` field. Fix is data layout, not code: define the referenced extern const table in the file (at the END of
  the file, so it lands after the local rodata objects; mid-file lands at .rodata offset 0), or fix symbols/splits
  (split a merged `lbl_` over several static arrays into local symbols; remove stray alignment-pad symbols; separate TU).
  To test a symbols hypothesis without editing config: `powerpc-eabi-objcopy --strip-symbol=<sym>` on a copy of the target
  .o, then `objdiff-cli diff -1 copy.o -2 ours.o`. Lessons: docs/lessons/2026-10-30-*phantom-r-ppc-no*, *objdiff-synthesized*.
- Actor-ctor tail `li r4` vs `li r0` family (4 functions), `OnShutdown`, `TRKDoSetOption` (`mr` vs `addi r3,r31,0`), `eggDrawPathBase`
  thunk order, `eggModelBoundingInfo` template order, `fn_8027B020` (`...data.0` anchor).
- Units needing real classes for vtable placement after jump tables (RPBsb_8027a3c4: three hand vtables); jumptable ownership in
  RPBow_80313028's lumped `.data` range (needs a proper RPBow data split).
- The near_miss "IMM" bucket was misclassified: fn_802B03B8, fn_8022BC38, VFiPFENT_ITER_DoGetEntry are register/schedule walls.

## What did not pay off (do not default to these)

- **The permuter is NOT the default.** About five runs (support.c, Bow, Gol stand-ins, several fns), zero
  gains; C++ stand-ins have a high mutation-failure rate. Use it only for a diagnosed register residue after
  the structural levers above are exhausted, and cap it at ~10 minutes.
- **Declaration-order sweeps.** 720 permutations were flat on fn_803536E4; 120 flat on fn_8026AA3C.
  Try one or two hand-picked orders, not a sweep.
- **Large-gap scheduling/string-pool walls** (fn_8026FF28 72.7, fn_80269DF4 73.3, fn_80293008 86): hours of
  Opus time, no gain. They are post-RA scheduler residue or need a symbols/pool change. Park them.
- **Fakematches the compiler "likes"**: `self->dat++; self->dat--;`, a dead duplicate vtable store, a
  self-assignment in a return path, `read ? 5 : 5`. Decide the policy up front (see below); report them as
  MATCH-PENDING, do not leave them in unflagged.

## Default procedure for the next batch

0. **Check the compiler build first** (2026-10-28). `python3 tools/version_sweep.py <unit>` compiles a unit with every
   MWCC build. RVL_SDK is GC/3.0a5: of 240 `revolution/*` units built on 3.0a5.2, 228 are identical on 3.0a5, and 12
   (WPAD, GXPixel, GXTransform, OSRtc, vi, WUD, uusb_ppc, wenc, nettime, NWC24MBoxCtrl, NWC24Time, pf_path) need 3.0a5.2,
   which matches the override list in doldecomp/forecast's `configure.py` (it also overrides KPAD, WPADHIDParser,
   WPADEncrypt, OSExec, i2c, vi3in1, hcicmds). Game code, nw4r and egg showed no gain on any older build (all 152 below-100
   non-SDK units swept, Pack with per-version precompiled headers). Always compare against forecast's source for the same file.
   See lessons "RVL_SDK units build with GC/3.0a5".
   **Flags too:** when a unit is stubborn (1-2 instruction diffs that no source spelling or permuter run closes), diff its
   cflags against forecast's `configure.py` before more source work. `-sdata2 0` missing from `cflags_trk` was the whole
   msghndlr wall (see AGENTS.md "Compiler flags are a per-unit input").
1. **Rank targets by flippability**, not by percentage: one function left + data sections 100% first;
   then two functions left; then units whose blocker is a symbols/splits decision (list those for the user
   up front: ctor/dtor renames such as fn_802EE1DC -> `__ct__9BoxSndCtlFv`, fn_8026E0DC needing a `__dt`
   rename of fn_801BEA7C, fn_80293008 unit-wide literal pool).
2. **Triage by wall class** (`tools/near_miss.py` buckets, wall-identifier skill) and run the structural
   checklist in "What paid off" item 3 before anything else.
3. **Time-box**: ~30 minutes of worker time per function, ~10 minutes of permuter if used at all; park
   anything under ~80% that is a scheduling wall.
4. **Parallelise with one worktree per worker** (never two workers in one worktree: ninja is not safe
   concurrently). The orchestrator merges branches one at a time, running `dol_diff.py` and
   `sym_addr_check.py` after each flip. Each worker commits only its own unit's files.
5. **Tooling**: `tools/setup_worktree.sh` makes a ready worktree (agent docs and `lessons.py`/`route_functions.py` are tracked, so they arrive with the checkout). Use `tools/reorder_fn.py` (committed) instead of ad-hoc scripts for function moves, and
   check `order_check.py` after every move.
6. **Verify yourself** after every worker: `tools/verify.py <unit>`, `tools/order_check.py`, and for flips
   `ninja build/RSPE01_01/main.dol` + `tools/dol_diff.py` (want 0) + `tools/sym_addr_check.py` (only
   `__FUNCTION__$1983`, `CPUFifo`, `GPFifo`, `time$1107`).

## Honesty policy (user-approved 2026-10-26: markers allowed as a last resort)

- Structural levers first. A marker (identical-arm ternary, dead pool-order literal, dummy local, invented helper,
  extra function, steering cast, dead duplicate store) is allowed only when nothing else closes the function.
- Each marker gets `// MATCH-PENDING (R17): <what it steers, what the real source probably lacks>`, invented helper names
  get `// name inferred` and a generic name, and `docs/marker-ledger.md` gets a row in the same commit.
- Gate: verify.py no regressions, DOL 0 bytes, sym_addr_check only the 4 known collisions; revert a marker that fails.
- Reports list marker functions separately ("bytes-matched, MATCH-PENDING"), never as plain matches.

## Mistakes to avoid repeating

- Moving a function with a script that matches a prototype (multi-line signature, `{` on the next line, labels
  at column 0 inside the body) and duplicates or truncates code. Use `tools/reorder_fn.py`, then build.
- Moving code inside/outside a `#pragma push/pop` or `dont_inline` region (changes inlining silently).
- Leaving a forward declaration behind a moved definition (duplicate prototypes) or dropping the prototype a
  hoisted caller needs.
- Declaring a unit done at objdiff 100% without the DOL check; flipping two units before checking the first.
- Spending a code pass on a unit whose `.sdata2`/`.rodata` split still differs.
- Sleeping/polling on a single serial worker when the work could run in parallel worktrees.

## Parallel-run lessons (2026-10-26)

- Give every worker its own scratch subdirectory; a shared scratchpad let one worker overwrite another's files.
- `git checkout <file>` / `git restore` on source files is blocked by the sandbox classifier: take a backup copy
  before experimenting and restore by copy/Edit.
- First `ninja` in a new worktree must run sequentially (concurrent builds clobber build/tools/dtk); objdiff-cli
  3.4.1 used to come back after every configure; `configure.py` now pins v3.8.2, so no re-copy.
- A successful `dol_diff` after a FAILED `ninja build/RSPE01_01/main.dol` is stale. Always check ninja's exit status.
- A Matching unit must define the global (non-@) symbols that symbols.txt assigns to its split (e.g. lbl_804C6188/618C
  in RPBow_80330FE8, 64.0f/80.0f in RPGol_802b90b4) or the link fails for units that extern them.
- `tools/unit_cmp.py` sections and `tools/dol_diff.py` decide flips, not objdiff % alone: RPBox_802f57a0 (.sdata2 pool
  order @145/@144) and RPBox_80305b7c (data layout) were 100% in code but did not flip.
