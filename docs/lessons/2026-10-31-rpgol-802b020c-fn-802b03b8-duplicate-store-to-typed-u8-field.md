# RPGol_802b020c fn_802B03B8: duplicate store to typed u8 field (o->f2=2; o->f2=2;) gives retail lwz o; li; lwz src; stb (R17)

- status: works
- tags: rpgol,802b03b8,schedule,duplicate-store,permuter,r17
- source: worker gol-b03b8 2026-10-31

symptom: 99.9%: 4-line load/li order diff at a join label
cause: pre-RA scheduler tie; a single store (typed field or ((u8*)o)[2] cast) schedules the src load first; the field store before the src load drops to 99.2
fix: give GolPad44 a real u8 f2 (RPGrpModel::mDrawGroup at +2) and store it twice (permuter found it in 9 min); a dead first store of another value also works; cast-form double store does not; one inline setter called twice works. Marker-ledger row 36. Real source likely two writes (two setters / default then overwrite).
