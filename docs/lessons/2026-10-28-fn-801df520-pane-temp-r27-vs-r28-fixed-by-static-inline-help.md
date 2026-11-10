# fn_801DF520 pane temp r27 vs r28 fixed by static-inline helper around first pane block

- status: works
- tags: regalloc,static-inline,pane,RPSysLytPlayerSelect
- source: fn_801DF520

symptom: 99.86%: findPane result in r27 instead of r28 (only 4 mr lines differ)
cause: bare {} scope and single-variable reshapes do not change colouring; moving the unbind/bind/restart pane block into a static inline helper does
fix: static inline RebindActiveArrow(self) holding findPane+unbind x2+bind+restart; fn_801DF520 -> 100%. Hoisting pane to fn top and inlining findPane into args failed (95.4%)
