# Varargs print with first arg (global) scheduled last (97.2/96.8)

- status: open
- tags: scheduling,varargs
- scope: RPGol_802aaf88
- source: fn_802AB63C

symptom: orig loads lbl_804BF918 into r3 after lha
cause: unknown
fix: dead ends: s16/int local, wrapper param orders, psq_st helper variants
