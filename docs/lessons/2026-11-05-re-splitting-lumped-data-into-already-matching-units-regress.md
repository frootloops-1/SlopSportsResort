# Re-splitting lumped .data into already-Matching units regresses their .data

- status: fails
- tags: data,splits,rpbow
- scope: RPBowScene

symptom: unit_cmp shows .data 0/57% on Matching neighbours after a first-slot ownership re-split; DOL still 0
cause: owner units' sources don't define the moved tables
fix: Either define each table in its owner (hand void* + R17) or keep the range lumped in the NonMatching unit as hand arrays (RPBow_803381DC did the latter). Check unit_cmp on every touched unit, not just DOL.
