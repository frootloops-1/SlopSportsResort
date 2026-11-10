# Unit owning ptmf state table + vtable + local name array: define them in the TU

- status: works
- tags: rodata,data,string-pool,ptmf,vtable
- scope: Pack/RPSports/RPSportsCommon/RPSports_801eabf4

symptom: .rodata/.data 0%: source externed lbl_80387458 (ptmf table), lbl_80387500 (name array), lbl_80387510 (strings), lbl_803C2660 (vtable)
cause: data was referenced as externs so the object defined none of it
fix: extern "C" const table of {0,-1,(s32)fn} rows; local const char* names[4]={literals} (copied array becomes @N rodata before @stringBase0, its strings pooled first); inline literals elsewhere; vtable as extern "C" void* lbl_[8]={0,0,fns...}; symbols.txt: string pool -> @stringBase0 scope:local data:string_table, trailing sdata2 float size 8->4 (pad becomes gap). All sections 100, DOL 0
