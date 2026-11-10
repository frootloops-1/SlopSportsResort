# RPSports_801ef064: unreferenced static const char* const table is NOT dropped here; file-end static helper pools a literal first

- status: works
- tags: string-pool,dead-table,R17,static-helper,RPSports_801ef064
- scope: Pack/RPSports/RPSportsCommon/RPSports_801ef064
- source: claude/sp801ef-1103

symptom: retail pools Scm_skillgraph_light (fn_801F062C) before fn_801F0020's strings; RPBsb dead-table trick emitted a 4/8-byte sdata2 object instead of being dropped (inside or outside extern C, top or mid file)
cause: this TU keeps unreferenced statics; code literals pool at codegen and a non-inline static function is compiled at its own source slot (file end = first)
fix: move the literal-bearing loop body into 'static void SpRankFlashLight(SpRankEntry*)' defined at the file END (auto-inlined into 062C, local copy dead-stripped at link, DOL unaffected); R17 ledger 161
