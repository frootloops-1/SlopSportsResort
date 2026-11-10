# fn_802D0E5C: flag diamond li 1/b/li 0 is not reproducible: if/else, ?:, inline if-return, inline ?: with param arms all become mfcr

- status: fails
- tags: fn_802D0E5C,RPBox_802cf93c,mfcr,diamond,bool
- scope: RPBox_802cf93c

symptom: target int flag = (f38 >= 0) as cror;bne;li r0,1;b;li r0,0; ours (flag=0; if() flag=1) hoists li r10,0 and is 4 bytes short (97.9)
cause: some IR-level pass turns a 0/1 diamond into a compare-value (mfcr/extrwi); not found in IroEval/IroTransform/COptimizer
fix: failed: if/else 1/0 (92.6), ?: 1:0 (92.6), static inline if(x>=0) return 1; return 0 (92.4), inline ?: a:b with (1,0) args (92.4). Untried: flag typed bool/u8, arms not constant (e.g. w148 compare), ELOR/ELAND lowering
