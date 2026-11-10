# RPGol debug constructor closes with native assembly and explicit existing string pool

- status: works
- tags: RPGol_802aa614,asm,R17,string,pool
- scope: fn_802AA714
- source: docs/tasks/RPGol_802aa614.md

symptom: Last constructor at 81.3% after two deep C++ scheduling/register-allocation passes; unit 5/6, data already exact
cause: Color loads and name stores cross MWCC pcode scheduling-block boundaries; natural source and steering reorder variants could not recover both register allocation and schedule
fix: Native scheduled constructor matches 302 instructions/1208 raw bytes/all 81 relocations. Retain earlier C++ under #if 0. Its 17 literals form exactly 123 bytes; explicit concatenated char array named GolDebugStringPool replaces compiler-local @stringBase0 at same address, allowing symbolic HA/LO refs without new strings or padding. 6/6 and all five sections 100; full DOL 0 differences, known collisions only. R17 row 229 supersedes 214.
