# RPSports_8020f530: by-value Pt2 args (compiler temps) instead of named Pt2 locals fix caller stack slots

- status: works
- tags: stack,temps,rpsports,8020f530
- source: sp8020f-1104

symptom: fn_8021013C Pt2 copies for fn_80211610/fn_8020F718 at wrong r1 offsets
cause: callees take Pt2 by value; retail copies are compiler temps (allocated after named locals), not named locals
fix: declare callee params by value (fn_80211610(ButtonHolder*, Pt2)) and pass *(Pt2*)&self->f7C directly
