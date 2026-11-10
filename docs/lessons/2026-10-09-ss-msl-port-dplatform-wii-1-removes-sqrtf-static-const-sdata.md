# ss MSL port: -DPLATFORM_WII=1 removes sqrtf static-const sdata2 bloat

- status: works
- tags: msl,sdata2,platform
- scope: MSL_C ports
- source: claude/msl-text 2026-10-09

symptom: printf/wprintf .sdata2 24 B vs original 8 B (weak @LOCAL@sqrtf@_half/_three)
cause: include/MSL_SS/cmath defines sqrtf with function-local static consts unless PLATFORM_WII; the original has no sqrtf
fix: Add -DPLATFORM_WII=1 to cflags_msl_ss (no regressions in the 21 matched units); .sdata2 then 100%. PLATFORM_GCN=1 is the wrong one (regresses)
