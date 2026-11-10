# dtk config.yml add_relocations for missed lis/subi address pairs (types ha / l, not addr16_*)

- status: works
- tags: dtk,config,relocation,RPBow_8031641C
- scope: RPBow_8031641C

symptom: target asm has raw constants (lis r0,0x803d / subi r3,r3,0x59a0) where our object has relocations; fn stuck 99.x
cause: dtk missed the ha/lo pair
fix: config/RSPE01_01/config.yml: add_relocations: - source: 0xADDR type: ha|l target: sym. Re-run dtk split. DOL stays 0.
