# fn_802D7920: volatile reads of s / lbl_804C4DF0[1] leave li r4 unchanged

- status: fails
- tags: fn_802D7920,RPBox_802cf93c,volatile
- scope: mwcc GC/3.0a5.2
- source: tenth pass

symptom: li r3 vs r4 sdata2 base (mr r3,self between li and lfs 4(base) pre-RA)
cause: prepass picks mr r3 as latency filler
fix: failed: volatile s (4 lines), volatile lbl_804C4DF0[1] local (4), volatile lbl_804C4DF0[0] (18), volatile lbl_804C4DF8[0] (33)
