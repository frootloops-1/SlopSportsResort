# fn_802A35EC: copy Vec2 fields individually, declare f32 c,s reversed

- status: works
- tags: rpgolmath,vec2,stack-slot,sincos
- scope: RPGolMath
- source: opus

symptom: Vec2 in=*v gives lwz/stw (90.3%); s/c stack slots swapped
cause: struct copy codegen and local declaration order
fix: in.x=v->x; in.y=v->y; declare f32 c, s;
