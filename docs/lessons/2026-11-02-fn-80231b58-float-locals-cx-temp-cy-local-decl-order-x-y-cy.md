# fn_80231B58 float locals: cx temp, cy local, decl order x,y,cy

- status: works
- tags: regalloc,fpr,locals,RPTns
- scope: RPTns_802318a4

symptom: fn_80231B58 f2/f3/f4 colour swap at 99.0
cause: mwcc colours vregs in descending number: temps (created in IR order) before locals, locals numbered first-declared highest; the target had cx as a forwarded temp and only cy as a local
fix: out->x = x - ..; cy = out->y; out->x = out->x/..; out->y = cy/..; declare f32 x; f32 y; f32 cy (x before y)
