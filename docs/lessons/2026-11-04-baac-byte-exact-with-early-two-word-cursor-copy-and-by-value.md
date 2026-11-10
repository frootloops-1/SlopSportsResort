# BAAC byte-exact with early two-word cursor copy and by-value outline color

- status: works
- tags: fn_8020BAAC,RPSports_8020b340,stack,copy,marker
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340
- source: codex-baac-1104

symptom: Target has three cursor buffers at 0x20/0x28/0x18 and frame C0; ordinary copy chains make only two and frame B0.
cause: Float assignment after early declaration introduces FPR transfers; ordinary late copies have the wrong stack creation order. Fill and outline color copies also had reversed slots.
fix: R17: declare intermediate before getter, assign through a two-u32 POD view, then ordinary CurPos copy; inferred by-value outline adapter fixes color C/8 slots. No pointer/integer round trip needed. All 404 bytes and 17 relocations match original DOL; no regressions, B6DC still exact, containing unit remains NonMatching.
