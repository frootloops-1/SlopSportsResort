# RPGolConfig aggregate initialization recovers retail static initializer

- status: works
- tags: RPGolConfig,constructor,aggregate,data,initializer
- scope: Pack/RPSports/RPGolScene/RPGolConfig
- source: docs/tasks/RPGolConfig.md

symptom: Manual fn_8029E2E8 initialization scored 12.99%; source text was 480 bytes versus retail 744
cause: The table used vector constructor temporaries, aggregate word copies and a compiler-generated array destructor registration
fix: Inferred 12-byte vector with POD base and user constructors; empty hole-record destructor; first ten vectors constructed and last four copied from external zero vector. Compiler generates all three exact functions and the 12-byte registration BSS record. Recover their local/weak symbols and remove the manual .ctors record.
