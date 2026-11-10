# GXInit __GXShutdown 99.8: static s64 split into two sbss symbols in symbols.txt (config, not code)

- status: open
- tags: GXInit,GXShutdown,sbss,symbols,s64
- scope: revolution/GX/GXInit
- source: gx-df-1026

symptom: __GXShutdown stw/lwz time+4 shows as time$1107 vs SYM+0x4; sdata 66.67, sbss 75, GXDefaultProjData 32!=28
cause: symbols.txt has peCount$2073 size 8, time$2127 size 4 and time$1107 size 4 (s64 time split in two); our .o lays peCount@0x10 (4), time@0x18 (8), calledOnce@0x20, so layout already matches. sdata: split end 0x804BD600 includes 4B inter-unit pad after __GXVersion (same as SIBios)
fix: orchestrator: symbols.txt peCount size 4, merge time into one size-8 symbol at 0x804BEE78 (drop time$1107), GXDefaultProjData size 0x1C, delete gap_10_804BD5FC_sdata, splits .sdata end 0x804BD5FC; re-split; no source change expected
