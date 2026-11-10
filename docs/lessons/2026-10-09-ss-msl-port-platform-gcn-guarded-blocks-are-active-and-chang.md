# ss MSL port: PLATFORM_GCN-guarded blocks are active and change codegen

- status: works
- tags: msl,platform
- scope: MSL_C ports
- source: claude/msl-text mem_funcs 2026-10-09

symptom: ported function differs only in register numbers / an extra add
cause: ss sources have '#if !PLATFORM_GCN' blocks (e.g. cps/cpd casts in mem_funcs rev_unaligned) that are live here because PLATFORM_GCN is undefined; defining -DPLATFORM_GCN=1 globally makes things worse (string, strtoul, ansi_files regress)
fix: Delete the offending guarded block per function instead of defining the macro
