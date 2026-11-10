# x / 4.0f, not x * 0.25f: operand order and pool position

- status: works
- tags: sdata2,pool,fmuls,operand-order
- scope: mwcc
- source: RPTns_802390b0

symptom: fmuls const,x instead of x,const; 0.25 pooled before 160 in (x+160)*0.25
cause: MWCC canonicalises literal multiplies const-first and pools the literal at parse; power-of-2 division becomes *0.25 at codegen (var first, constant pooled after the fn's literals)
fix: write x / 4.0f (and x += 160; c = x / 4.0f to keep fadds x,const)
