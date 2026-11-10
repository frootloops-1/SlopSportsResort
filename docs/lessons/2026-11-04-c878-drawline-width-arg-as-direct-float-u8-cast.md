# C878: DrawLine width arg as direct float->u8 cast

- status: works
- tags: regalloc,cast,u8,b340,C878
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340

symptom: width arg went through extra s32 temp; retail lwz r6,68(r1); clrlwi r6,r6,24
cause: (u8)(s32)(expr) adds an intermediate; retail casts float straight to u8
fix: (u8)(w + (f32)k): C878 harness 41->37 (91.5->91.6)
