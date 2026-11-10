# Register-allocation walls: ogws digest of `docs/llm_matching_tricks.md`

`docs/llm_matching_tricks.md` comes from another GC/3.0a5.2 Wii decomp (Forecast Channel `SceneBase.cpp`, 57/57 to
Matching). Its allocator model was decompiled from `mwcceppc.exe` and checked in gdb. Read it in full when a function
has **the same instructions as the target but different register numbers** (wall-identifier class "register /
schedule"). This file lists what is easy to miss, how it maps to our tools, and where it applies to open walls here.
(The "guide" it mentions, `docs/llm_decomp_guide.md`, is not in this repo; our equivalent is `docs/matching-playbook.md`.)

## The model in five lines (agrees with our `tools/mwcc_dbg.sh` dumps, `docs/mwcc-debugger.md`)

1. Select colours nodes in **descending vreg order**. Each takes the **lowest free volatile** register, and
   callee-saved registers are handed out in order **r31, r30, ...** (f31, f30, ...). High-degree nodes (live across
   calls) are ordered by spill-weight/degree instead, so **use counts** change their order.
2. vreg numbering, low to high: parameters (in order), then **named locals (first declared = highest = coloured first)**,
   then `@N` variables (inline-expansion locals, created in reverse declaration order per expansion; nested expansions
   lower; optimizer temps such as strength-reduced table pointers lowest/newest), then **expression temps** (above every
   variable, so coloured first; later generated = higher).
3. Interference is half-open: a result can reuse a source that dies in the same instruction.

## Levers that are easy to miss (try these before reshaping expressions or running the permuter)

- **A local's declared type decides whether it is a variable at all.** A local assigned from a load is *merged into the
  load's expression temp* when the types allow it, and is then coloured like a temp (first). Another type keeps it a
  separate named variable (coloured where its declaration puts it). "A local has no effect" usually means it was merged:
  change its type (e.g. `wchar_t` vs `u32`, `s32` vs `u32`, a typed pointer vs `void*`). Test both.
- **Declare up front, uninitialised, then assign** in the original statement order. Only the declaration order then
  moves the vregs, not the code. Initialising at the declaration often changes the code.
- **Search declaration orders and types exhaustively with a one-function harness** (section 4 of the source doc,
  ~0.5 s per variant: prelude + the function and its inlines, compile with the unit's exact flags from `build.ninja`,
  score the *whole* function, never a window). 6-8 locals = 720-40,320 variants, cheap. **The decomp-permuter does not
  explore declaration order or local types**, which is why our long permuter runs on colour walls returned only ties.
- **Loops that must colour together belong in one inline expansion.** A nested inline helper makes its locals newer
  (coloured later). Use `goto found;` inside the helper to reproduce inlined early-return code (`break` differs).
- **Walk a copy of a pointer parameter** (`const T* p = str; ... p++`) rather than incrementing the parameter.
- **4-byte structs by value (GXColor):** passing an lvalue of a *non-POD* class (user ctor, e.g. `nw4r::ut::Color`
  via `static inline const nw4r::ut::Color& AsColor(const GXColor* c)`) hoists the stack copy's `addi rX,r1,imm` out
  of loops and can change argument-evaluation order.
- **A reload after a store to a stack struct** (target reloads, ours CSEs): `T store = *p; T& cur = store;`. This is
  plain source, not steering. A class with a dtor also forces it but emits an extra weak dtor.
- **Extend a carried variable's live range by reusing it** (`prev = ...; x += prev;`) instead of a new local.
- **Name float results** (`f32 offX = ...;`) so loads colour first, and use **a named local for a hoisted constant**
  (`f32 m1 = -1.0f;` inside the block) to reorder callee-saved float constants.
- Not levers for these walls (confirmed there and here): compiler versions, `-O`/`-ipa`/`-inline`/`-schedule` flags,
  `#pragma opt_*`/peephole/scheduling, `const`/`register` qualifiers, random expression rewrites.

## Link-level points (section 6 of the source doc)

- Weak function emission order (e.g. swapped weak dtors after `__sinit`): `extra_cflags=["-ipa file"]` for the unit is
  the other known fix besides defining the dtor out of line at its retail position.
- Check ninja's **exit status** after a link: a failed link leaves the old DOL and a shasum can still pass.
- The first `ninja` after an edit can fail on a missing `.d` file (`transform_dep.py`); re-run.

## Where this applies in ogws right now (2026-11-04)

- `RPSports_801f1d4c` `__ct__9SpMdlSetDFPv` (parked, 99.8): `mgr`/`anm` colour as named locals (r24); retail colours
  them earlier (r25). **Not yet tried:** the type-merge lever: give `mgr`/`anm` types that let them merge into their
  load temps (match/mismatch `spCurrent__20RPGrpModelResManager`'s declared type and the `f38->anm` field type), plus
  an exhaustive declaration-order/type sweep with a harness. Seven passes tried shapes, pragmas, helpers and the
  permuter, never types/decl-order systematically.
- `RPSports_8020b340`: `fn_8020E464` (R17 row 212 getter) may close honestly with `T store = ...; T& cur = store;`;
  `fn_8020D0EC`/`fn_8020D40C` colour-argument residue: try the non-POD `AsColor` lvalue; `fn_8020C530`/`fn_8020E58C`
  register residue: declaration order/type sweep.

## Tooling notes for this machine

- **`tools/fn_harness.py <unit> <fn> [variant files...]`** (2026-11-04): compiles a variant of the unit with the exact
  `build.ninja` flags into a temp object and scores the whole function (0 = exact; sanity-checked on exact functions).
  `--perm` sweeps declaration orders. Data relocations compare by type only. Use it for decl-order/type sweeps.

- Our dump tool already exposes the colouring order: `tools/mwcc_dbg.sh` -> `regalloc-gpr-pass-N-assigned.txt`
  (see `docs/mwcc-debugger.md`). Use it to tell variables from temps before choosing a lever.
- The source doc's gdb-on-wibo anchors in `mwcceppc.exe` (VAs: `0x596df0` per-class colouring loop, `0x61fae0` graph
  builder, `0x597300` simplify, `0x5970e0` select, `0x46b4a0` vreg numbering) were taken from their GC/3.0a5.2
  `mwcceppc.exe`; check they hit the same code in `build/compilers/GC/3.0a5.2/mwcceppc.exe` before relying on them.
  There is no gdb on this Mac; our debugger path is the retrowin32-based `mwcc_dbg.sh`.
