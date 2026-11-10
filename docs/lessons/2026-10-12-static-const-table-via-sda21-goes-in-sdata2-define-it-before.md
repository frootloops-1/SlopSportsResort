# static const table via sda21 goes in .sdata2: define it before includes

- status: works
- tags: sdata2,sda21,const,order,include
- scope: RPGrpModelAnmImplement
- source: sonnet worker, verified 2026-10-12

symptom: li rX,sym@sda21 table (TO_BIND_OPTION) not in .sdata2 offset 0; floats shift by 4-8 bytes
cause: Header-pooled floats/consts precede a later definition
fix: static const int T[2] at top of file before all includes
