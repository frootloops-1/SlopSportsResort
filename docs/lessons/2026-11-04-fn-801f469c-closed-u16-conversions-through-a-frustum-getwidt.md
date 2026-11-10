# fn_801F469C closed: u16 conversions through a Frustum::GetWidth/GetHeight inline getter fix volatile r0/r3/r4 choice

- status: works
- tags: inline-getter,volatile,conversion,801f1d4c
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f1d4c
- source: claude/sp801f1-1104

symptom: two (u16)(s32)f -> f32 blocks: retail lwz r0 / clrlwi r3,r0 vs ours lwz r3 / clrlwi r3,r3 (99.6)
cause: retail reads the capture screen's size via EGG::Frustum's u16 GetWidth()/GetHeight() (static_cast<u16>(mSize.x)); the inline return temps change volatile numbering
fix: add u16 GetWidth/GetHeight to the TU's local Frustum view (no asserts, string order unaffected) and use cap->GetWidth()/GetHeight() in both blocks; .sdata2 stays 100
