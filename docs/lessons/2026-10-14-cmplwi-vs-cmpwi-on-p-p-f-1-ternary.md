# cmplwi vs cmpwi on p ? p->f : -1 ternary

- status: works
- tags: compare,signedness
- scope: RPGol_802ae9ec
- source: fn_802AF37C

symptom: cmpwi instead of cmplwi
cause: field/fallback signed
fix: make field u32 and fallback (u32)-1
