# Jump table target order differs while text is 100%: check DOL .data and enum value of switch cases

- status: works
- tags: nw4r,ef,jumptable,switch
- scope: nw4r/ef

symptom: ef_drawdirectionalstrategy DOL check failed with 2 swapped 4-byte jump-table entries; objdiff .text 100%
cause: ParticleBoth was case 4 in source but is case 6 in original (case 4 falls to default)
fix: use AHEAD_CMN_NODESIGN + 1 for ParticleBoth, default returns Speed; also __declspec(section ".sdata") static u8 tex0[32] __attribute__((aligned(32))) reproduces the 0x20 sdata object
