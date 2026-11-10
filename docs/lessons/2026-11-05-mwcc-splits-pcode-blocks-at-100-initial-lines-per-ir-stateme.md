# MWCC splits pcode blocks at >100 initial lines per IR statement; scheduler window = merged block

- status: works
- tags: scheduler,block-split,hoist,pcode,rpgol,aa614,ctor,table-init
- scope: fn_802AA714
- source: gol-aa614-1105

symptom: fn_802AA714: ours hoists a 5th colour's lbz into the first scheduled block, retail stops at 4; long straight-line table init
cause: MWCC ends a pcode block after an IR statement once the block has >100 initial pcode lines (mwcc_dbg backend-00); optimizer merges neighbours whose post-opt sizes total <= ~100. Block boundaries decide what the pre-RA scheduler may hoist
fix: Count initial pcode lines per statement (backend-00-initial-code) and reorder/resize statements so block boundaries land where retail's do; here interleaving colours 0-3 before names 15/16: 33.7 -> 81.3. Dead exprs/unused locals/inline params vanish before codegen and do not count
