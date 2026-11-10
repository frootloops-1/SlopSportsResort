# RPSports_8020f530: retail pools 2 pane-name strings and -5000 ahead of the first function's literals

- status: open
- tags: pool,stringBase,sdata2,rpsports,8020f530
- source: sp8020f-1104

symptom: @stringBase0: retail N_effect_00, CURSOR_02(F718), N_ABuPosition_00, then 1013C body; ours codegen order. sdata2 retail -5000 first
cause: unknown; candidate: non-inline static helpers (effect start, ABu position, cursor reset) compiled first then auto-inlined and stripped
fix: try static helpers placed next to fn_8020F718 in descending source; WIP patch docs/tasks/RPSports_8020f530-data-wip.patch
