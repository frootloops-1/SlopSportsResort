# switch pivot order via empty extra case

- status: works
- tags: switch,mwcc,rpbsb
- source: RPBsb_8028bb24 2026-10-16

symptom: switch on 0,1,2 compiles with pivot cmpwi 1; original pivots at 2 then 0
cause: MWCC binary-search pivot depends on case count
fix: add an empty 'case 3: break;' (fn_8028C1A4 94.6 -> 100)
