# Nested for loop for table zeroing fixes constant scheduling

- status: works
- tags: scheduling,loop,unroll,constants
- scope: RPTns_80227918
- source: opus worker 2026-10-14

symptom: li -1 / lis scheduled differently vs first stores (90%)
cause: orig wrote a 2D zeroing loop that MWCC unrolled
fix: for(i<2) for(j<5) self->tbl[i][j]=0; (fn_802280C4)
