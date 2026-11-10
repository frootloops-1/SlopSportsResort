# fn_802A7CD8 FPR walls: named-local decl sweep is flat while inline results coalesce; un-inline then order

- status: works
- tags: regalloc,fpr,inline,coalesce,RPGol
- source: RPGol_802a7a40 2026-11-05 opus

symptom: 7 float locals: every decl order gave the same colours (5040-order sweep flat)
cause: named locals assigned from an inline result (GolMul/GolAbs) are copy-propagated into the inline's @ var, so their decl position is ignored
fix: write those values without the inline (b = x / 256.0f gave fmuls operand order; abs as d = d > 0 ? d : -d) and declare u,d,a,b uninitialised up front; then m-site lerp written inline '(1.0f - lo) * pow(..) + lo' + GolClamp fixed the volatile f0/f2 pick (d must be an expression temp, newer than the CSE'd 1.0). mwcc_dbg fpr assigned list names each var
