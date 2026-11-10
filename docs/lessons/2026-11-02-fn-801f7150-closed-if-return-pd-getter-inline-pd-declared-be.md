# fn_801F7150 closed: if/return pd getter inline + pd declared before for-scoped loop vars

- status: works
- tags: RPSports,colouring,inline,getter,mwcc_dbg,fn_801F7150
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f6ebc
- source: opus 2026-11-02

symptom: inlined IsAllMedalAtLeast x2: outer pd/i/inner pd r26/r27/r29 vs target r29/r26/r27 (99.0)
cause: frontend trace: a ternary assigned to a named local is linearised into a NEW @N temp after all inline expansions (lowest @ vreg, coloured late); inside the inline, locals are created in reverse declaration order. Target colouring needs outer pd > game1 > sport1 > pd1 > game2 > sport2 > pd2 (descending vreg), found by brute-force renumbering on the colour model (rule reproduces dump at K>=26)
fix: static inline getter written as if (self->p8) return self->p8->p10; return self->p1C; (return-value @N created at expansion time, before the helper expansions); use it for outer pd and in the helper, and declare pd BEFORE for (int sport..) for (int game..). Ternary getter or local-var getter: no change; sport/game declared before pd: 98.7
