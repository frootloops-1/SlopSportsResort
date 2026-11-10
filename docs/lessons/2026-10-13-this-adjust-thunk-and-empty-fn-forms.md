# this-adjust thunk and empty fn forms

- status: works
- tags: thunk,blr
- scope: RPSportsCommon_unsplit

symptom: subi r3,r3,N; b X thunks and bare blr
cause: multiple-inheritance thunks
fix: void f(void* self){ X((u8*)self - N); } with extern C X(void*); void f(void*){} for blr
