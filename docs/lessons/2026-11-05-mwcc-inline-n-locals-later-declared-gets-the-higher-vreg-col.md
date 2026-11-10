# MWCC inline @N locals: later-declared gets the higher vreg (coloured first)

- status: open
- tags: regalloc,inline,vreg-order,mwcc_dbg
- scope: Pack/RPSports/RPBowScene/RPBow_80319C98

symptom: decl-order reasoning for inline-expansion locals
cause: dump of fn_8031B3F4 BowCamShake: i@1445 r88 < tbl r89 < ti r90 for declaration order i, tbl, ti (opposite of function-level named locals, where first declared = highest)
fix: to colour an inline local first, declare it last within the inline
