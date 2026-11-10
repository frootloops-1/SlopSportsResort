# Named local colours last: read it through an inline getter to make it an early-coloured temp

- status: works
- tags: rptns,regalloc,colouring,inline,getter,mwcc_dbg
- scope: Pack/RPSports/RPTnsScene/RPTns_80244198
- source: opus 2026-11-02

symptom: fn_80246254: msg/msg2 r26/r27 vs target r29/r28; last-loop ptr IV r29 vs r28; decl-order perms and regsearch no gain
cause: MWCC colours in descending vreg order, each taking the lowest already-used non-conflicting reg; named locals have the lowest vregs (coloured last); inline-expansion temps are numbered above the IRO IVs, so they colour first while only r29 is in use
fix: msg = lbl_804BF730->getMsg(); msg2 = lbl_804BF730->getMsg2(); with inline member getters on TnsMsgRoot -> 100 (static inline free getters also work). MATCH-PENDING R17, ledger row 80
