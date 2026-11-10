# resort: game-code .sdata2 pools are 8-byte padded per file; padded 8-byte constant symbol marks a file end

- status: works
- tags: resort,splits,sdata2,basketball
- scope: resort
- source: basketball

symptom: finding file boundaries in Resort game code
cause: each TU's .sdata2 pool is aligned to 8; the last 4-byte constant gets 4 bytes of padding
fix: an 8-byte symbol holding a 4-byte constant plus zeros ends a file; agreed with every duplicate-constant cut in Basketball
