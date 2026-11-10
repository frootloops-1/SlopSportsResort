# Zero-word sdata gap: const zero goes to sdata2, plain zero to sbss

- status: fails
- tags: sdata,zero-word,SIBios
- scope: revolution/SI/SIBios
- source: session 2026-10-26

symptom: sdata 4-byte zero word after __SIVersion has no owner
cause: MWCC places const zero in .sdata2 and non-const zero in .sbss; neither gives writable .sdata
fix: none yet
