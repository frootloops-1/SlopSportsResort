# Template bytes referenced via local static avoid reloc-name diffs

- status: works
- tags: sdata2,reloc,naming
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-rpbox-802cb9cc-1022

symptom: lbl_X+3 vs the target's per-byte lbl_Y relocs showed as diffs
cause: dtk names each referenced byte of the original anonymous object
fix: define the const GXColor as a file-scope static (local symbol)
