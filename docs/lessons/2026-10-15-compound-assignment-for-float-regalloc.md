# Compound assignment for float regalloc

- status: works
- tags: float,regalloc
- source: RPTns_80216810

symptom: v.x = k*(c-v.x)+v.x or y = y*k+c scores 97-99.5
cause: Compound ops change which FPR holds temps
fix: Use v.x += k*(c-v.x); v.y=0; x*=k;y*=k;z*=k;y+=c
