# RPSports_801f1d4c three register walls parked after two Opus passes

- status: fails
- tags: register,parked,permuter,ctor
- scope: RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104b a22784883

symptom: fn_801F5524 97.2 clrlwi vs self/idx colours; SpMdlSet 99.6 tbl/idx*4 swap; SpMdlSetD 99.8 mgr/anm r24 vs r25
cause: Vreg numbering windows unreachable by declaration placement, nested scopes, inline-boundary u8 params; permuter only via address-taken idx; permute_cxx can't handle new-expressions
fix: open: parked; see docs/tasks/RPSports_801f1d4c.md
