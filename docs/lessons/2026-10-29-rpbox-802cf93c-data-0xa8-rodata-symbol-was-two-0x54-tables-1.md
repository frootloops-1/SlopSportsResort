# RPBox_802cf93c data: 0xA8 rodata symbol was two 0x54 tables; 1-byte sdata2 sym + gap was s8[2]; missing .ctors word

- status: works
- tags: rodata,sdata2,ctors,symbols,rpbox,802cf93c
- scope: RPBox_802cf93c
- source: claude/box802cf-data-1029

symptom: unit_cmp: lbl_8038FC5C 168!=84, lbl_804C4E08 66.7, .ctors 0
cause: dtk merged lbl_8038FC5C+lbl_8038FCB0; s8[2] {1,-1} tables split as 1-byte sym + 3-byte gap; hand-written sinit fn_802DE33C had no .ctors pointer
fix: symbols.txt: FC5C 0x54 + new lbl_8038FCB0 0x54; E08/E0C size 2 with 2-byte gap_ syms; force_active __declspec(section .ctors) static ptr = fn_802DE33C. Also extern-pool lbl_804C4EA0 replaced by literal 0.1f (fn_802DAA84 stays exact) + pool_renames -> @6286
