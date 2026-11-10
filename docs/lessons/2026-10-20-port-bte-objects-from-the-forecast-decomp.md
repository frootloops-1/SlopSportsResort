# Port BTE objects from the forecast decomp

- status: works
- tags: BTE,forecast,headers,splits
- scope: BTE
- source: claude/bte-forecast2 2026-10-20

symptom: Forecast BTE .c compiles against ogws headers with signature/layout errors, or links with undefined data
cause: Forecast headers use REVOLUTION ifdefs with different Wii struct layouts; ogws splits carry cfg/bss data forecast keeps in other units
fix: Copy the .c, then merge only the needed header hunks (never overlay whole header trees: breaks ~20 matched units); add HCIC_FORECAST_PROTOS for hcimsgs; split cfg/bss data per forecast splits.txt; name fn_ symbols from forecast order; check DOL with cmp after a full ninja
