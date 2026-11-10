# Float 2-vector copied lfs/stfs vs retail lwz/stw: nw4r VEC2 shape

- status: works
- tags: rpgol,802b1a0c
- scope: Pack/RPSports/RPGolScene/RPGol_802b1a0c

symptom: struct copy via float regs instead of int (fn_802B4474)
cause: type shape
fix: plain base struct + empty ctor + assigning ctor; init at declaration; ctor temp to const& push; (n + (x - 1)) % n index
