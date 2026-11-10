# fn_8027B020 ...data.0 anchor: dtk label alias and TU data models do not fix it

- status: fails
- tags: data,anchor,rpbsb,objdiff
- scope: RPBsb_8027a3c4
- source: claude/d2-1028

symptom: fn_8027B020 99.9: target @518 vs ours ...data.0 on lis/addi r31
cause: Original B020 uses the TU local-.data section anchor (r31=@518, local .data starts at @518, 6A20 not anchor-visible). Defining lbl_803C6A20/6AA0/6B0C in the TU (even weak) emits them before @518 (vtables at parse time, jumptable at TU end) so offsets become anchor+0xe8 etc (96.3 / 99.8, worse). Adding a symbols.txt label '...data.0' at 0x803C6A48 next to @518 (precedent exists for ...rodata.0) does not help: dtk picks the sized object @518 for relocs; renaming @518 itself would just move the mismatch to AB94's jumptable ref.
fix: unfixable in objdiff; leave unit NonMatching, judge by DOL link. Do not retry weak/extern data definitions or the label alias.
