# resort: u16 flag clears: bitfield assignment gives rlwinm, '&= ~mask' gives andi.

- status: works
- tags: resort,codegen,bitfield,flags
- source: rp-camera worker 2026-11-09

symptom: andi. where retail has rlwinm r0,r0,0,.. on a u16 flag
cause: MWCC lowers bitfield stores with rlwinm
fix: model the flags as a union of u16 all + bitfield struct; clear via bitfield, test via all & mask
