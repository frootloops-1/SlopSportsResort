# fn_802375B0 closed: named p30 local declared last + root declared after the other locals

- status: works
- tags: colour order,regalloc,simplify,declaration order,RPTns
- scope: Pack/RPSports/RPTnsScene/RPTns_8023758c

symptom: register rotation: retail root r30/e r29/f..i r28..r25, ours i r30 root r28 (52 lines)
cause: Coloring_SimplifyGraph K=29: i (deg 29, lowest named) was skipped in sweep 1 because the root->p30 CSE temp interfered; root (higher vreg) dropped below K in sweep 1. Retail needs i pushed in sweep 1 and root in sweep 2
fix: declare d,e,f,g,h,i first, then TnsRoot* const root = lbl, then TnsP30* p30 (lowest vreg, deg 12, pushed first so i's degree drops to 28); p30 = root->p30; g/h/i/d = p30->... Loading d before i also fixed regs but changed load order (2 lines). Non-const root becomes an @ temp (global copy)
