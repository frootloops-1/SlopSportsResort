# Merged rodata pool symbol matches named pool base (RPBsb_8027be84)

- status: works
- tags: rodata,string-pool,symbols,matching
- source: RPBsb_8027be84 (13/13 exact, DOL OK)

symptom: Only one relocation differs: orig addresses format strings as lbl_8038D230@ha + offset (named pool object), ours emits @stringBase0; fn at 99.77%
cause: symbols.txt split the pool into separate string objects, so the TU-level pool base had no matching named symbol
fix: Merge the pool in symbols.txt into one lbl_8038D230 object (size 0x228 data:string); after dtk dol split, the function matches 100%. Same as commit 9bd5d10c
