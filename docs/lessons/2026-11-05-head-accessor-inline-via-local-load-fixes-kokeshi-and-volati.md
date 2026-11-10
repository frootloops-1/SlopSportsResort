# Head accessor inline / via-local load fixes kokeshi and volatile swaps

- status: works
- tags: regalloc,accessor,RPBow_8031641C
- source: RPBow_8031641C round 3

symptom: kokeshi head and the shadow-param loop pointer/byte (r3 vs r6) coloured swapped
cause: reading through an inline return value makes the value an @-temp; a named local for the struct pointer changes the load temp numbering
fix: head = BowKokHead(holder) (R17 accessor) in all 4 loops: 150->101; BowShadowTexData* d = ...; param = d->param[i]: 101->79
