# RPSysEffectBase.h / eggDrawGX.h emit unused revolution inlines into .text

- status: works
- tags: header,text-size,inline
- scope: RPTns_8022f2b8
- source: sonnet worker 2026-10-14

symptom: .text 0x18c0 vs 0x164C with MEM*/GX*/OS* local functions
cause: header static inlines emitted
fix: declare minimal local class views instead of including (RPTns_8022f2b8)
