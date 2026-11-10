# Tennis RNG: LCG + LFSR written in place on globals

- status: works
- tags: rng,lcg,lfsr,regalloc
- scope: RPTns_80248bb8
- source: opus worker 2026-10-14

symptom: RNG block registers swapped (98.8)
cause: locals for state change coloring
fix: g678 = g678*0x41C64E6D+0x3039; if(g67C&1) g67C^=0x11020; g67C>>=1; return (u16)((g678^g67C)>>1)&0x7FFF
