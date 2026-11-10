# bd_addr_null belongs in bd.c (.sbss2), not an anonymous lbl_

- status: works
- tags: bte,sbss2,symbols
- scope: revolution/BTE/bta/sys/bd
- source: session-2026-11-07

symptom: auto_13_804C6A10_sbss2 8 B; bta_hh_utils used lbl_804C6A10
cause: Broadcom bd.c defines const BD_ADDR bd_addr_null (zero const -> .sbss2); link order bd.c follows bta_dm_cfg
fix: define it in bd.c, .sbss2 split 0x804C6A10-18, symbol size 0x6, drop the lbl_ alias
