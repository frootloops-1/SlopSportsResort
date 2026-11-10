# Two float loads from one struct: target loads field 2 first (RPGolMath fn_802A3864)

- status: works
- tags: rpgolmath,atan2,float-load-order
- scope: RPGolMath
- source: haiku

symptom: Atan2FIdx(v->x, v->y) scored 99%; target loads 4(r3) before 0(r3)
cause: arg evaluation order vs load scheduling
fix: f32 y = v->y; return Atan2FIdx(v->x, y)*(PI/128) -> 100%
