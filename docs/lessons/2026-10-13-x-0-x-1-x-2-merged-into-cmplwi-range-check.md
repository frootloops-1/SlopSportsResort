# x==0||x==1||x==2 merged into cmplwi range check

- status: works
- tags: mwcc,branches,compare
- scope: RPGol_802bf4f8
- source: opus-worker

symptom: orig has cmpwi/beq chain, ours one cmplwi range check
cause: MWCC merges equality-or chains into a range test
fix: write if (x!=0 && x!=1 && x!=2) {} else {body}, or if (!(x!=5 && x!=6)) {A} else {B}; switch/else-if/inline bool/enum all still merged
