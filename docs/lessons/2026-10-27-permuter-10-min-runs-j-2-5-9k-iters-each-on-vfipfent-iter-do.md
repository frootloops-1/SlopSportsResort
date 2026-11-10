# Permuter round 1 was void (candidates lost helper bodies); round 2 with PERMUTER_KEEP_BODIES: no gain on VFiPFENT_ITER_DoGetEntry, __CalcLFO, SIInterruptHandler

- status: fails
- tags: permuter,VFiPFENT_ITER_DoGetEntry,RecycleRegion_,__CalcLFO,SIInterruptHandler,nogain
- scope: revolution/VF,revolution/MEM,revolution/AXFX,revolution/SI
- source: orchestrator-1027

symptom: Round 1 (stock extract_fn): every candidate scored 9000+ (100 per deleted instruction) against true base scores 98/92/140/341, i.e. the search never explored real variants. Round 2 (10 min, -j 2, 5-6.6k iters each): VFiPFENT_ITER_DoGetEntry base 30, no candidate beat it (only ties); __CalcLFO base 135, nothing; SIInterruptHandler 2885 -> 2410 but the candidate only adds unused dummy locals (new_var, new_var2) and its real mismatch is 81 vs base 52; RecycleRegion_ did not start (permuter: Unable to compile base.c after the pycparser round trip, no detail even with --show-errors).
cause: decomp-permuter src/ast_util.extract_fn replaces every non-inline FuncDef except the target with a bare declaration and strips `static`, so helpers the target inlines under -inline auto vanish in every candidate (setup/base.o is fine, which hid it). My earlier "noise floor from branch-target text" explanation was wrong.
fix: Patched the sibling ../decomp-permuter checkout (outside this repo, gated): PERMUTER_KEEP_BODIES=1 keeps bodies and `static`; tools/permute.py setup --keep-bodies writes a keep_bodies marker and run sets the variable. Check after setup: the run.log "base score" must be low and early candidate scores near it (30-130), not 9000+. Always re-score a permuter best with permute.mismatch after compiling it with PERMUTER_KEEP_BODIES=1, and reject candidates that add unused locals. Round 2 conclusion: VFiPFENT_ITER_DoGetEntry, __CalcLFO, SIInterruptHandler are not closed by 10 min of random permutation; RecycleRegion_ is untested.
