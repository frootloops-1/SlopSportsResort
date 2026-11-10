# Bulk symbols.txt size trim: trailing alignment pad inside a data symbol (gap 1-7 B, non-vtable) cost 1.5% matched data

- status: works
- tags: symbols,sbss,sdata,size,data,report
- source: orchestrator symsize sweep 2026-10-31

symptom: unit_cmp lists SIZE-MISMATCH N!=M (8!=4, 8!=1, 256!=252) on symbols whose code and bytes match; Matching units still show incomplete data in report.json
cause: symbols.txt sizes include the trailing alignment padding up to the next symbol; compiled object has only the real size
fix: Sweep build/evidence/unit_cmp/*.json: left size > right size by 1..7, skip __vt__ and @ pool names, set size to the compiled size, re-run dtk split. 68 symbols, matched_data 84.10 -> 85.62%, DOL 0. Vtables (24 vs 20), gaps >7 and right>left left for manual review.
