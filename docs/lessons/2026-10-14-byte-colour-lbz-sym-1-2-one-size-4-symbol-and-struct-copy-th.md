# Byte colour lbz sym/+1/+2: one size-4 symbol and struct copy then modify

- status: works
- tags: sdata2,color
- scope: RPGol_802adb7c
- source: fn_802AE07C

symptom: li+offset or wrong loads
cause: dtk split byte symbols / member-wise copy
fix: merge into one size-4 symbol; static const _GXColor k = {...}; _GXColor c = k; c.a = x;
