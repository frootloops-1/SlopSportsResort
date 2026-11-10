# Port zeldaret/ss MSL via vendored headers include/MSL_SS

- status: works
- tags: msl,headers,port
- scope: MSL_C ports
- source: claude/msl-text 2026-10-09

symptom: ss MSL sources need alloc.h, ansi_files.h, critical_regions.h, common.h etc. that include/MSL lacks
cause: include/MSL is a minimal set for game code; ss has the full MSL_C headers
fix: Copy ss MSL include dirs flat into include/MSL_SS (+ small common.h and rvl/OS.h shims), and give ported Objects cflags=cflags_msl_ss, which is cflags_runtime minus include/MSL paths plus -i include/MSL_SS
