# RPSports_80201240 data in source: all data sections 100 (sinit array with ctor, PMF view class, defer_codegen vtables)

- status: works
- tags: data,sinit,ptmf,defer_codegen,string-pool,RPSports_80201240
- scope: Pack/RPSports/RPSportsCommon/RPSports_80201240
- source: claude/sp80201-1104

symptom: .ctors/.rodata/.data/.bss/.sdata/.sbss 0, hand sinit fn
cause: data was extern lbls; sinit was a plain fn; PMF records/vtables/order missing
fix: file-static name tables; SpMsgEntry ctor + array init gives __sinit (rename fn_ to __sinit_ scope:local); &SpSelView::vXX for PMFs (parse-time PMF array is 8-aligned and changes code: dead); hand vtables after defer_codegen off + extern; 23B0 table as local aggregate init (const extern table hoisted loads); symbols resync from objdump
