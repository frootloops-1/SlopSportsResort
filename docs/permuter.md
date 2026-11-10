# decomp-permuter (tier C near-misses)

Installed 2026-10-08: checkout at `../decomp-permuter` (sibling of this repo,
override with `PERMUTER_DIR`), deps in its `.venv`. PowerPC binutils come from
the project's pinned `build/binutils` (`ninja build/binutils`; if Python's
download times out, fetch
`https://github.com/encounter/gc-wii-binutils/releases/download/2.42-1/macos-universal.zip`
with curl and unzip into `build/binutils`).

```sh
python3 tools/permute.py setup revolution/SI/SIBios SITransfer   # -> build/permuter/SITransfer/
python3 tools/permute.py run SITransfer --minutes 20             # progress in run.log
python3 tools/permute.py best SITransfer                         # diff command for the best candidate
python3 tools/route_functions.py record SITransfer permuter gain|nogain|match
```

`setup` preprocesses the unit with its exact ninja flags, keeps all header
code (inline functions, class bodies) whole, replaces the unit's other
function bodies with prototypes, assembles the target function alone from
`build/RSPE01_01/asm/<unit>.s`, and checks that `base.c` compiles. Scores:
lower is better, 0 = exact; roughly 1,000 candidates/min with `-j 4`.

## C vs C++

- **C units** (`revolution/*`, MSL, MetroTRK, etc.): `setup <unit> <fn>`.
- **C++ units** (Pack, nw4r, egg): `setup` builds the C stand-in itself
  (`tools/permute_cxx.py`); no hand-edited `base.c`. Pass the mangled symbol
  from `asm/<unit>.s`; the source name is demangled (`--name Class::method` to
  override, `--static` for a static member / free function, `--index N` for an
  overload; with overloads it tries each and keeps the best).

```sh
python3 tools/permute.py setup egg/core/eggHeap findContainHeap__Q23EGG4HeapFPCv --static
# "starting mismatch: 0 instruction lines (exact)" means the stand-in reproduces the object
```

  How it works: `base.c` holds only the target function (mangled symbol as its
  name, `Cls* this` added, `::`/`~`/template calls/`T& x =`/`T x(args);`/casts
  rewritten to C, `typedef struct X X;` stubs found by trial parsing).
  `compile.sh` turns each candidate back into C++ (original head, scope names,
  `#pragma unused`) and splices it into the *real* source file, so includes,
  earlier functions that `-inline auto` may inline, and anonymous-namespace
  names behave as in the build. Only the target function is scored
  (`objdump --disassemble=<sym>`). A non-zero starting mismatch for a function
  known to compile exactly means the stand-in lost something (e.g. macro side
  effects in the C round trip). On a 40-function sample of Matching C++ units,
  33 set up exact.
- Not supported (setup stops with the parser error): inline functions defined
  in headers, placement `new`, lambdas, SJIS (non-UTF-8) source text, `asm`
  functions.

## Applying a result

### Typed C++ search inputs and improved seeds

`setup` always reads the current source TU, so apply and verify a prior winner
before preparing a new search. Archive the old `build/permuter/<function>/`
directory first: setup replaces it, including its logs and candidates.

Supply optional C typedefs to replace opaque parser stubs:

```sh
python3 tools/permute.py setup Pack/RPUtility/RPUtlRigid fn_801BA758 \
  --name fn_801BA758 --static --type-context tools/permuter/RPUtlRigid.types.h
```

This describes vector fields for mutations without changing the compiler's real
C++ types. The context must contain only typedef declarations; it is copied to
`type-context.h` beside the search input and is discarded during C++ restoration.
Method descriptions are parser hints, not object ABI declarations. Overloaded
operators are still interpreted by a C parser and may produce invalid mutations.
Inspect mutations for semantic changes before applying them.

Compare `base.o` against the real compiled function with objdiff before searching;
the adapter must reproduce that function at 100%. A score closer to the permuter
target alone does not establish adapter fidelity. Setup saves compiler diagnostics
in `baseline-compile.log`, avoiding dependence on `/dev/stderr` access.

A candidate is a hint, not a patch: port the meaningful change (statement
order, temp variable, cast) back into `src/`, rebuild the real object, and
verify with objdiff as usual. Never paste permuter `source.c` into `src/`.

## Escalation

Permuter first (one run, ~20 min). No gain → Opus ×2 → park. Opus is the
ceiling; there is no Fable lane (see `docs/model-routing.md`).

## Notes (2026-10-13)

- The checkout is `../decomp-permuter` of the primary tree (`~/Downloads/decomp-permuter`);
  override with `PERMUTER_DIR`. Worktrees outside `~/Downloads` need that variable.
- Added `perm_identical_ternary` to the permuter's `src/randomizer.py` and
  `default_weights.toml` (local edit, not committed in that checkout): turns an
  int literal `K` into `(x ? K : K)`. MWCC keeps the dead test, which is what
  took `TRKSuppAccessFile` from 91.9% to 98.9%; the permuter now rediscovers it
  in under two minutes (score 480 -> 145). Weights: 3 base, 8 for mwcc.
- Run the permuter on a near-miss before spending Opus on register-allocation
  or scheduling diffs.

## TODO

- Permutations the RPGraphics wins needed that the permuter lacks: local-array
  sizes (`buf[255]`), `(int)` casts for overloads, inline-helper extraction,
  loop forms. (Reinstall and automatic C++ stand-ins are done, see above.)
