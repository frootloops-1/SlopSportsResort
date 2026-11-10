# MWCC bool flag: write tests as '== 0' to keep 'li 1 ... li 0' shape

- status: works
- tags: mwcc,bool,drawgx,RPGrpModelRfl,register
- scope: RPGrpModelRfl::DrawGX

symptom: bool v=true; if(!(a&m) && !(b&n)) v=false compiles to inverted 'li 0; bne; beq; li 1' vs retail 'li 1; bne; bne; li 0'
cause: negated bit-test spelling makes MWCC fold the assignment into the inverted form
fix: spell tests (a&m)==0 && (b&n)==0; r5/r6 swap in nested && temps fixed by inline bit-test with '? true : false' (IsEntered, like IsVisible); GXColor compound literal passed straight to call (no named local) fixes stack slots
