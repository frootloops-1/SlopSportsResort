# RPUtlAccAnalyzer zero byte array to .sdata: non-const plus explicit_zero_data

- status: works
- tags: sdata,sbss,explicit_zero_data,const

symptom: 8-byte zero array lands in .sbss (or .sdata2 if const)
cause: const small data goes to .sdata2; plain zero goes .sbss
fix: non-const u8 arr[8]={0} wrapped in #pragma explicit_zero_data on/reset (no DECL_SECTION)
