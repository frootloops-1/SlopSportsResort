# sdata2 byte constants: declare extern const u8 so loads hoist (RPGolMapObjBase)

- status: works
- tags: golf,sdata2,schedule,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: lbz of sdata2 bytes scheduled after stb stores (94%)
cause: CW treats them as non-const data
fix: declare extern const u8 lbl_...; loads hoist, 98.6%
