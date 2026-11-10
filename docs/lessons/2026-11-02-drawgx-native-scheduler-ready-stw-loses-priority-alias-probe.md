# DrawGX native scheduler: ready stw loses priority; alias probes give no gain

- status: fails
- tags: RPGrpModelRfl,DrawGX,scheduler,alias,inlining
- scope: Pack/RPGraphics/RPGrpModelRfl
- source: Native trace 2026-11-02; build/evidence/rfl-drawgx-20261102

symptom: Only DrawGX remains at 99.652176%; retail stw precedes lbzx/addi, ours follows them.
cause: Native graphs 17/104 show lwz->stw delay 2, but stw is eligible at cycle 2 when lbzx wins. lbzx height 9/latest 2 beats stw height 7/latest 4. Latency alone is not sufficient explanation for the differing textual order.
fix: 38 new successful forms plus control across six builds (234 builds), no gain: const/restrict/reference/out-param/record helpers, casts, volatile combinations, C99 alias modes, inlining variants, empty asm. Full helper works with auto_inline off on wrapper (dont_inline disables inner inlining too), but keeps same wall plus extra register diffs. C99 conversion warnings can be suppressed for diagnosis; slot type change does not help. Reject all probes. Baseline/data matches untouched; DOL 0. Native graphs and replay saved in evidence; next attempt needs new alias/dependency idea.
