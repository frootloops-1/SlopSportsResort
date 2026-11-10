# fn_8028AFB4: getFlags/getCount accessors rank flags/cnt above the cur*4 CSE temp

- status: works
- tags: accessor,iro-temp,fn_8028AFB4,R17,RPBsb
- scope: Pack/RPSports/RPBsbScene/RPBsb_8028aef0
- source: batch 2026-11-01

symptom: 99.9%: flags r27 / cur*4 r29 swapped
cause: cur*4 CSE temp (vreg 41) sits above named locals flags/cnt so it colours first
fix: static inline getFlags(data)/getCount(si) initialisers (R17 row 53); pSi=&si required (99.7 without); getFlags alone stays 99.9
