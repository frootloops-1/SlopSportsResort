# RVL_SDK units build with GC/3.0a5, not 3.0a5.2: pf_entry_iterator and pf_cp932 match; permuter validated

- status: works
- tags: mw_version,3.0a5,pf_entry_iterator,pf_cp932,permuter,reference-decomp
- source: commits 1b4dfce4f b26ae95d0

symptom: SDK (revolution/*) units stuck on register/scheduling walls under GC/3.0a5.2
cause: doldecomp/forecast (same Nov-2006 SDK code) sets mw_version GC/3.0a5 for its whole RVL_SDK lib and has pf_entry_iterator.c and pf_cp932.c Matching. Under 3.0a5 pf_entry_iterator needs only two natural reorderings (DoGetEntry declares s8* p first; IteratorInitialize stores offset_mask before file_sector_index) and pf_cp932 needs uc_lead reused for the kana value (found by the permuter). tools/permute.py setup uses the unit's mw_version, so permuter runs on a unit pinned to the wrong compiler search the wrong space (earlier cp932 runs found nothing); with 3.0a5 it reached score 0 in under 6 minutes from the broken Unicode2OEM.
fix: For any revolution/* unit below 100: set Object(..., mw_version="GC/3.0a5") first (check doldecomp/forecast's source for the same file), then fix remaining statement order / run the permuter. Consider moving the whole RVL_SDK lib to 3.0a5 and re-gating units one at a time (NdevExi2AD already uses 3.0a3).
