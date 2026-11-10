# Avoid CTR loops: do-while with --i >= N when orig uses cmpwi/bge

- status: works
- tags: loop,ctr,bdnz,do-while
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: for(i=47;i>=1;i--) became mtctr/bdnz; orig subi+cmpwi 1+bge
cause: MWCC CTR-converts for loops with computable trip count, not do-while
fix: i=47; do {...} while (--i >= 1); same for >= 0x18 and >= 0 (subic.)
