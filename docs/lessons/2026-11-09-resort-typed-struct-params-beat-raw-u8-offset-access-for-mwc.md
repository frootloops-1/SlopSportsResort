# resort: typed struct params beat raw u8*+offset access for MWCC scheduling

- status: works
- tags: resort,bowling,codegen
- scope: resort
- source: bowling-lanes

symptom: raw *(f32*)(p+off) access CSEs addresses into registers and reorders loads
cause: alias analysis differs for raw byte pointers
fix: use typed struct params/fields (LaneHead*, etc.); read globals directly, not via a const u8* local. Closed 4 RPBow_80323790 functions. The .sdata2 pool order gives the original statement order of long constant-init functions
