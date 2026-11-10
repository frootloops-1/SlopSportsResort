# Parse-time data object stuck at .sdata2 offset 0 = wrong TU boundary

- status: works
- tags: split,sdata2,evidence
- scope: RPGol_802b66c4
- source: opus-worker

symptom: const array must follow a double literal but always lands first
cause: file/function statics are created at parse time before codegen literals; the double's user belongs to the previous TU
fix: move the double's user to the preceding TU (RPGol_802b697c -> 802b66c4 at 0x802B6A58); test by compiling it there and checking emitted .sdata2
