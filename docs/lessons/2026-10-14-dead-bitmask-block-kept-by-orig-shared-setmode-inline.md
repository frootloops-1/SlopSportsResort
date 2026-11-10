# Dead bitmask block kept by orig: shared SetMode inline

- status: works
- tags: dead-code,inline
- scope: RPGol_802a7a40
- source: fn_802A9FE0

symptom: orig keeps unreachable (1<<m)&0x31 block
cause: inline with club check folded after inlining
fix: shared inline SetMode (m==3 -> club in {6,10,11}?0:2, m==0 -> 3, else 1)
