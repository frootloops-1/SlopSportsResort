# Local const aggregate copy happens at declaration point

- status: works
- tags: mwcc,rodata,locals
- scope: RPGol_802bf4f8
- source: sonnet-worker

symptom: fn_802C024C u32 colors[6] lwzu/stw copy hoisted into prologue, frame size off
cause: MWCC copies a local const aggregate from rodata where it is declared
fix: declare it right before first use (after the idx if-chain)
