# Inline helper param order + body use order drives load order and pool order

- status: works
- tags: inline,sdata2
- scope: RPGol_802b1a0c
- source: fn_802B34FC

symptom: pool/regs off in ease helper
cause: args evaluated at use in body
fix: ease(outLo,outHi,base,inLo,inHi,x){ return outLo+(outHi-outLo)*pow(base,(x-inLo)/(inHi-inLo)); }
