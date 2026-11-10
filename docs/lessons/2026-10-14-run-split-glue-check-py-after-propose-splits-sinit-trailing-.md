# Run split_glue_check.py after propose_splits: sinit-trailing thunk runs

- status: works
- tags: split,thunk,vtable
- scope: RPBsbScene
- source: claude/rpbsb-splits

symptom: proposer puts a cut right after a sinit, before subi r3,r3,N; b fn thunks that target the previous TU (RPBsb 8026A190, 8027A38C, 8027B294)
cause: proposer sinit-trailer limit / glue scoring misses thunk runs
fix: python3 tools/split_glue_check.py <blob.s> <proposal.json> [OLD=NEW]; move each flagged cut past the thunk run, rerun until only base-class vtable notes remain
