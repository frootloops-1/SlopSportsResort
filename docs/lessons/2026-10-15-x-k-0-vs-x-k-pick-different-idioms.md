# (x & K)==0 vs !(x & K) pick different idioms

- status: works
- tags: bitmask,idiom
- scope: RPTns
- source: RPTns_80235cd0

symptom: extrwi/xori vs rlwinm/cntlzw/srwi
cause: different expression trees
fix: (x & 0x20) == 0 gives extrwi/xori; !(x & 0x20) gives rlwinm/cntlzw/srwi
