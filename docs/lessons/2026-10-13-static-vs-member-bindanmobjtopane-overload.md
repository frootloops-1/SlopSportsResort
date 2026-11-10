# Static vs member bindAnmObjToPane overload

- status: works
- tags: overload,static,mangling
- scope: RPSportsCommon_unsplit

symptom: 96.5% arg/this shift calling bindAnmObjToPane
cause: pane overload is static (anm, Pane*, bool)
fix: declare static in local RPSysLayout view
