# RPGolMain .rodata pool order is not first-use inside fn_8028E40C

- status: open
- tags: rodata,string,pool,order
- scope: RPGolMain

symptom: orig pool: breff(0) breft(0x12) glf_course(0x24) rp_Gol_sound(0x37) sports_message(0x4A), used in order glf, sound, message, breff, breft; ours pools first-use (92.8%)
cause: unknown; dead if(0), (void)str, unused static fn, earlier static inline helper did not change order; top-level const char* locals fix order but hoist base + stmw r27 (85%)
fix: open
