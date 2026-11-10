# NW4R data 100 through jump-table pairing and padding-size corrections

- status: works
- tags: nw4r,data,symbols,padding,jumptable,guard,alignment
- scope: nw4r (five units)
- source: 2026-11-03; build/evidence/nw4r-data-20261103/

symptom: NW4R data 99.84456% (287768/288216), code already 100 across 191 complete units. Five units have inexact scored data/BSS sections, while all 83 affected functions already match.
cause: ParticleManager jump tables were not paired; cylinder/billboard/smoothstripe final float symbols included four trailing padding bytes; billboard eight-byte tex0 initializer was sized as its 32-byte alignment; final smoothstripe guard included four pad bytes; two alignment gaps were explicitly declared as objects.
fix: Correct symbols.txt only: pair 30/10-entry ParticleManager tables as @6893/@6892 after verifying all 40 relocation tuples; size three last floats to 4 and pair compiler pool names; size tex0 to 8 retaining align:32; last guard to 1; remove zero gap declarations at 0x804BFE7C and 0x804C04E4 (dtk emits hidden gaps). Regenerate dtk splits and progress. All five units have code/data/BSS 100%, all 83 functions unchanged, NW4R data 288216/288216 (100%). DOL remains 0 bytes, only three known symbol collisions, NW4R order0. No source/header/flag changes or new markers; unused weak ELF atoms still linker-discarded.
