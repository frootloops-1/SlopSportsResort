# fn_801F5524: retail double clrlwi needs a non-clean idx def; size then matches but self/idx colours swap (self degree 29 = K)

- status: open
- tags: clrlwi,colour,degree,801f1d4c,parked
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104

symptom: retail clrlwi r4,r31,24 and clrlwi r0,r31,24 around v6 call; ours mr r4,r31 and no clrlwi (228 vs 232)
cause: MWCC drops the u8 truncation when every def of idx is li/lbz; a def via a copy (int idx = u8 cur, or inline return temp) keeps both clrlwi
fix: int idx; else { u8 cur = e[0].cur; idx = cur; ...}; v6(idx,arg); entries[(u8)idx] -> right size, but self (r32, deg 29 >= K) is coloured first (r31) vs retail r30. Failed: inline find/On helpers (int/u8 params), whole body inline, entries pointer local, u16/s16/u32 idx, const self, loop search (right colours, wrong shape)
