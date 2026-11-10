# fn_80206370: typed params replace void* casts; .sdata2 floats defined at file end

- status: works
- tags: typed-params,sdata2,emission-order,fn_80206370,RPSports
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020634c
- source: unit sweep 2026-11-01

symptom: 89.8%, 20 bytes short, .sdata2 50% (four floats missing)
cause: void* params cast to non-const locals change scheduling/colours and unroll the loop; early initialised global floats fold into @ literals
fix: fn_80206370(const SpRankElem* src, SpRankElem* dst, s32 n); dst[i+1].d = pi->d; explicit prev local; define lbl_804C21F0.. const f32 at END of file with earlier extern const decls; reorder_fn.py to descending address (deferred emission)
