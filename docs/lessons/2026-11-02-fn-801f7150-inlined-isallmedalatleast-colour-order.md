# fn_801F7150 inlined IsAllMedalAtLeast colour order

- status: fails
- tags: RPSports,colouring,fn_801F7150
- scope: RPSports_801f6ebc

symptom: pd/i/inner pd regs r26/r27/r29 vs target r29/r26/r27
cause: color_sim: colour order descending vreg; target needs game > pd_outer > sport > innerpd > i; ours innerpd > game > sport > pd_outer > i
fix: tried: i hoisted decl, pd decl order in helper (98.4), const self, getter inline for pd (outer/inner/both, ternary or if/else: same or 98.7), for-scoped sport/game (98.4), decl permutations of sport/game/pd (98.2-98.5), tmp/pd order; regsearch --generic had only 2 mutation sites. Open
