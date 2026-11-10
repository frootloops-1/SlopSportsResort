# fcmpo/bge clamp at zero

- status: works
- tags: float,clamp
- scope: RPGol_802adb7c
- source: fn_802AE444

symptom: cror
cause: ternary orientation
fix: v < 0.0f ? 0.0f : v
