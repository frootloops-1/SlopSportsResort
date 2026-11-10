# dont_inline on the callee disables inlines inside it; wrap the caller

- status: works
- tags: pragma,dont_inline
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: fn_8022BCFC got inlined into fn_8022B3DC; wrapping BCFC dropped it to 66%
cause: pragma applies to calls compiled inside the region
fix: #pragma dont_inline on/reset around the caller fn_8022B3DC only
