# fn_80353CA4 frame(neg)/loop-i swap: inline neg expr and up-front i flat/worse

- status: fails
- tags: regalloc,forecast,fn_80353CA4,RPBow
- scope: fn_80353CA4

symptom: target frame neg in r31 and loop i in r28, ours reversed (99.9)
cause: colouring order of named local vs loop induction var; not controlled by declaration position
fix: dead ends: startDynAnmIn(-pCtx->mField34) without named frame (96.7, neg moves); int i declared up front before/after frame (99.8). Diagnoser lever 9/1 flat. Parked.
