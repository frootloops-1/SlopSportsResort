# MWCC FPR colouring on GC/3.0a5.2 (observed): many-call nodes first in vreg order, one-call nodes after, late nodes reuse the lowest used free reg

- status: works
- tags: regalloc,fpr,model
- scope: tools/regalloc_diag.py, docs/forecast-regalloc-notes.md
- source: FPR experiment 2026-10-28

symptom: published model (docs/forecast-regalloc-notes.md) says each node takes the highest free callee-saved reg and FPR high-degree needs K~32 neighbours
cause: measured in fn_802D930C: the high/low split follows live across many calls, not a K~32 neighbour count (FP neighbours ~10); within each group order is temp > @N inline locals > named locals in declaration order > params; a late one-call node reuses the lowest-numbered already-used callee-saved reg its neighbours leave free
fix: to land a value on a dead high register (f31) it must be coloured early: make it an inline param/@N local or expression temp, not a named local; declaration-order moves inside the named group never moved it. Single-function observation
