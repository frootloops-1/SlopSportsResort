# CNT local aggregate template in original data section

- status: works
- tags: data-section,local-aggregate,const_type,layout
- scope: revolution/CNT/cnt
- source: codex-nearmiss-bte-vf-round2-1018, RSPE01_01

Original contentReadNAND copies632 bytes of error pairs to the stack. The local const array generated identical instructions but its initializer template landed in.rodata instead of.data. Changing local constness, using static arrays, and compiler-version trials were already unsuccessful (2026-10-15 lesson).

`#pragma section const_type ".data"` preserves the aggregate copy and moves the template to.data. Also declare the warning as a file-scope const char array before the function and reference it from OSReport: this puts the49-byte warning before the template, with7-byte padding, matching all688 original data bytes. Pragma alone reported100% data but emitted681 bytes in the wrong order: section scores do not prove layout. `readonly_strings on` did not fix that order. A separate global table plus memcpy regressed code86.945946%; discarded.

Final five functions and.text/.data100%; actual source-linked full DOL SHA1 matches original8bb422971b88b5551a37de98db69557df7b46637. No compiler flag, shared-header or map change. Evidence build/evidence/round2/cnt/ (named-warning,data-proof.json,source-link.log,dol-proof.json).
