# fn_801BD7E0 Hermite: natural forms under default scheduling never get f29-f31 (closed)

- status: fails
- tags: fpr,scheduling,RPUtlDirMath
- scope: Pack/RPUtility/RPUtlDirMath
- source: claude/dirmath-1027

symptom: need retail early loads + callee-saved weights without stack locals
cause: default pre-RA scheduler sinks loads regardless of source order
fix: failed: x/y/z locals + direct reads (all associativities), direct out stores, const& params, non-const params, loop over (&p->x)[i], stage-wise accumulation (3 placements of end), loads-first locals (all subsets), 250-sample decl-order sweep, struct copy VEC3 a=*p (lwz/stw), pragmas scheduling twice/fp_contract_aggressive/ppc_no_fp_blockmove. Whole-file schedule once breaks the other 13 fns
