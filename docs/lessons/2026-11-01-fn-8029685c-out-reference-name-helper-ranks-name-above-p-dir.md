# fn_8029685C: out-reference name helper ranks name above p; direct const-global reads merge

- status: works
- tags: out-ref,inline,rank,fn_8029685C,R17,RPGol
- scope: Pack/RPSports/RPGolScene/RPGolMapObjTree
- source: step2 2026-11-01

symptom: 99.4%: flag r31 / name r27 vs target h=r31 name=r30 p=r29 flag=r27
cause: flag was a late compiler temp and name a named local below p
fix: read the extern const u8 .sdata2 global directly (three loads merge into one temp); golName(out-ref + inner local) for name/nameLod/nameSh (R17 row 62); lbl_804C4028 size 8->4 (.sdata2 97.44->100). Dead: value-returning inline (99.5), no inner local (99.3), named flag with helpers (99.2)
