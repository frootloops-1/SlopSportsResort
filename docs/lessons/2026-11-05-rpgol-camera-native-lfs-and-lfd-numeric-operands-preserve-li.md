# RPGol camera native lfs and lfd numeric operands preserve literal relocations

- status: works
- tags: RPGol_802c441c,asm,R17,literals,pool
- scope: fn_802C531C
- source: docs/tasks/RPGol_802c441c.md

symptom: Remaining 99.8% function has one GPR pair swapped; full native fallback needs compiler-local @N float references
cause: Short asm gets correct GPRs but reserves CR0 and moves surrounding C++ comparisons to CR1; native lfs/lfd numeric operands automatically emit pooled SDA21 references
fix: Native scheduled fallback uses exact decimal round-trip f32/f64 operands on lfs/lfd, not hardcoded SDA offsets or data aliases. Dead native helper seeds all 37 retail constants before deferred C++ emission, replacing three old pool placeholders. 325 instructions/1300 raw bytes and 59 canonical relocations match; 10/10 functions and all sections 100. Original C++ retained, R17 rows 226-227.
