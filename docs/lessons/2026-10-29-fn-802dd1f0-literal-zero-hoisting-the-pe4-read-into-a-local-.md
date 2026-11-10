# fn_802DD1F0 literal zero: hoisting the pE4 read into a local or using the BoxTkV10 inline does not move lwz pE4 above stw r20,0x80

- status: fails
- tags: fn_802DD1F0,RPBox_802cf93c,scheduler,lbl_804C4E10
- scope: RPBox_802cf93c
- source: claude/box802cf-r5-1029 opus

symptom: with f32 zero = 0.0f one stw r20,0x80 issues before lwz r3,0xe4 (99.0); the extern lbl_804C4E10 read is exact but unresolved at link
cause: program order of the pE4 load is irrelevant (same-base different-offset loads/stores are disambiguated); the extern works only because a DDATA read orders the following pointer stores
fix: failed: BoxTkObj* e4 = self->pE4 hoisted above the Reset stores (99.0, identical), BoxTkV10(self) inline for the vcall block (98.8). Untried: a real named const global for the 0.0f slot (would split the shared pool slot used by other functions)
