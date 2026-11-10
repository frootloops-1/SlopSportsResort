# mwcc-debugger (compiler internals for register/scheduling walls)

Dumps the real GC/3.0a5.2 compiler's PCode after each backend pass and its register allocator state, for ONE function.
Set up 2026-10-28; tooling lives outside the repo (see `~/Downloads/ogws-tools/mwcc-debugger/gc30/NOTES.md` for layouts, addresses, limits).

```sh
# from the repo root (needs build/compilers/GC/3.0a5.2); ~1-2 min per function
~/Downloads/ogws-tools/mwcc-debugger/gc30/run_unit_fn.sh src/revolution/VF/pf_cp932.c VFiPFCODE_CP932_OEM2Unicode /tmp/dump
```
Outputs: `backend-00-initial-code` (instruction selection), `01-after-optimizer`, `02-before-regalloc` (= after the pre-RA
scheduler), `03-after-regalloc`, `...-final-code`, `regalloc-gpr-pass-N-assigned.txt` (priority/colouring order, neighbours).
C only for now (plain link names); `-enc SJIS` is dropped. Compare 01 vs 02 to see what the scheduler moved.

## Read-out for pf_cp932 (first use)
In both `OEM2Unicode` and `Unicode2OEM` the optimizer emits the target's order (`...; sth/stb; li r3,1; li r4,2; b`), and the
PRE-regalloc scheduler then hoists `li r3,1` above the remaining ALU/store work. That puts a precoloured write of r3 inside the
temp's live range, so the allocator (r50 neighbours r0 r1 r3 r4) cannot give the temp r3 and picks r5. The target did not hoist.
So the wall is a pre-RA schedule difference, not an allocation-order one: look for source that changes the block's instruction
mix/dependencies before scheduling (see backend-01), not declaration order.

**Resolution (same day):** `pf_cp932` matched on `mw_version="GC/3.0a5"` (OEM2Unicode unmodified; Unicode2OEM with the
MATCH-PENDING `u16 temp`, ledger row added). Lesson: before a variant search on an SDK unit, compile it with each older
compiler in `build/compilers/GC` (see the "Compiler-version sweep" lesson). A sweep of the remaining below-100 units
(`pf_entry_iterator`, egg/nw4r/MetroTRK ones) found no other compiler-version wins.

## C++ units and the generic wrapper (2026-10-28, tools/mwcc_dbg.sh)

**Concurrency (2026-11-01):** the gdb stub port 9001 is hard-coded in both `mwcc_debugger.py` and retrowin32 (`cli/src/debugger.rs`),
so two simultaneous runs make one gdb attach to the other's compiler and dump the wrong worktree. `tools/mwcc_dbg.sh` therefore
serialises on `/tmp/mwccdbg.lock` (mkdir lock holding the pid; stale locks of dead pids are removed; `MWCC_DBG_LOCK_TIMEOUT`
seconds, default 3600), also waits while something else listens on 9001, and after the run fails (exit 3) if `run.log` shows a
`Reading /private/tmp/<other worktree>` line. Expect "waiting for another dump to finish" when other workers are dumping.
`mwcc_frontend_trace.py` uses the same port and is not locked yet: do not run it concurrently with a dump.

`tools/mwcc_dbg.sh <unit-under-src> <function> <outdir>` takes the unit's real flags from `ninja -t commands` (drops `-enc SJIS`,
`-MMD`, the dep step), so it works for C++ units too. Give the **unqualified** name (`setColor`, `Draw`), not the mangled one: the
compiler's function object carries the plain name (mangled name -> "Skipping function" for every function, then a crash).
Overloads: the first one wins. ~2.5 min per function, also for the 120-line `ShadowTexture::Draw`. The dump is of OUR source; the
target is read from its disassembly, so use it to learn which vreg is which and the real colouring order of ours.

How to read `regalloc-gpr-pass-1-assigned.txt`: entries are in colouring order (first gets r31 if its neighbours allow); named
locals show their name, the rest are temps/`@N`. Named locals: first declared = highest vreg = coloured first. Temps and `@N`
values are coloured before every named local and can occupy r31/r30 across a local's whole range.

Read-outs:
- **CpuTexture::setColor I8**: ours has `red` as an expression temp (`lbz r88,color,0`, coloured early, takes r0) and `offset` as a
  named multi-def variable (`r36`, `add r36,..; add r36,r36,block`, coloured last, takes r6). The target is the reverse (offset r0,
  red r8): red must be an OLD vreg and the offset a NEW temp. Dead-first-assign / top-declared / uninit red variants all keep
  red a temp (8 lines unchanged), because the optimiser forwards it.
- **ShadowTexture::Draw**: named order is w, h, alpha, y, x, restoreClearColor, clear, pScreen, this (declaration order, reversed
  numbers). Declaring alpha first does reorder the vregs (alpha 46 > w 45 > h 44) but alpha still lands in r29: two temps coloured
  before all named locals (`r145`->r31, `@16800`->r30) already hold r31/r30 over alpha's range. So the lever is whatever creates
  or shortens those two temps, not the named-local order.


## Scheduler decision traces (GC/3.0a5.2)

```sh
python3 tools/mwcc_sched_trace.py egg/geom/eggPlane project build/evidence/plane-scheduler
```

This checks the compiler SHA1 and uses `mwcc_dbg.sh`'s flags and global debugger lock.
It reads the native scheduler without changing PCode or registers. The external debugger
is copied and instrumented under the output directory; the external installation stays unchanged.
`MWCC_DEBUGGER` selects that extension in the wrapper.

Alongside the usual backend/FPR/GPR dumps, `scheduler.json` records complete dependency
graphs, candidate snapshots, processor `can_issue` results, and actual selections.
Phase 0 is scheduling before allocation; phase 1 is the forced scheduling pass after allocation.
Nodes are in the block's input order. Edges point to dependent instructions and include their
delay; `pending` counts unissued prerequisites. `height`, `latest`, `earliest`, and opcode `rank`
expose priority inputs. A zero-pending candidate can still fail the processor eligibility check.
Pointer identities are local to a run. Detailed snapshots can be large; inspect summaries.

Native hooks: scheduler entry `0x5995c0`, block entry `0x599740`, completed graph `0x5997f8`,
selection call/return `0x59985e`/`0x599863`, eligibility returns `0x59994f`/`0x59998a`/`0x5999c1`.
Node layout: four pointers (prev, next, dependents, instruction), then five u16 fields
(latency, earliest, latest, height, pending). Dependent entries are next pointer, node pointer, u16 delay.

Plane result (2026-11-01): the `dot(rVec)` product has only two FPR interference neighbours,
so renumbering alone cannot yield retail's f4 under the allocator's lowest-free-register rule.
A diagnostic PCode reorder reproduced the retail FPR allocation but still gave a different final
schedule; it is **not** a source match. Source probes gave no gain. See `docs/tasks/egg-Plane.md`.

## Frontend identity traces (GC/3.0a5.2)

Use `python3 tools/mwcc_frontend_trace.py <unit> <unqualified-function> <outdir>` when a source temporary disappears before the first PCode dump. Run in a configured task worktree. The tool reads its real ninja command, checks the exact compiler SHA1, and uses the same external debugger/emulator installations as `mwcc_dbg.sh`; it does not edit source.

The extension snapshots the native AST at codegen entry and IRO nodes around scalarization, copy propagation, expression propagation and dead-store elimination. The first 25 frontend snapshots are retained by default (`--frontend-limit` changes this); backend PCode and register-allocation dumps still complete. `trace-index.json` contains phase labels, reference counts and decoder-error counts. `run.log` contains the verbose debugger output. Unknown expression forms retain raw bytes; absence is meaningful only when the relevant accesses were decoded successfully.

GC3 node names must be reloaded at target entry: the initial startup table is empty. Its ENode/IRO layouts differ from the old debugger's GC1/2 decoders. A proposed earlier inline hook at `0x545830` did not execute under ef_animcurve's actual flags, so this tool deliberately starts at the active `CodeGen_Generator` gate.

Verified U8 case: `negative0` and `combined0` each have two references through scalarization and copy propagation. `IRO_ExpressionPropagation` substitutes their single reads, leaving one store reference each; `IRO_DeadStore` then removes them. Corresponding signed accesses preserve the frontend objects but force stack-backed storage. Backend forwarding removes those stores/reloads and leaves anonymous vregs, so the old register identities still do not survive. Do not infer allocator identities from source names alone.

### Separate compiler reproductions

`--source PATH` compiles a standalone diagnostic with the selected unit's flags and
precompiled header, writing only to the trace output directory. `--track NAME`
adds an object to the compact snapshot summaries and can be repeated.
`compile-command.json` records the source override, compiler SHA1, exact command,
and tracked names. IRO operand rows retain their ENode bytes; known unary/binary
operators have decoded names, while other node kinds retain raw fields.

See [the Tennis address-order reproduction](repros/tns_address_order.md): a branching
signed-long example reproduces alias hoisting before induction initialization.
The delayed variant reverses the address/copy ownership with the normal compiler
and no extra final instructions. Its full-function port is **not a match**;
the fixture isolates pass ordering from the remaining register-allocation problem.
