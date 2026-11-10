# fcmpu+mfcr+extrwi+xori via int ne = (0.0f != x); if(!ne)

- status: works
- tags: mwcc,float,compare
- scope: RPGol_802bb044
- source: sonnet-worker

symptom: direct if (0.0f == x) gives plain fcmpu/bne
cause: bool materialized
fix: int ne = (0.0f != x); if (!ne)
