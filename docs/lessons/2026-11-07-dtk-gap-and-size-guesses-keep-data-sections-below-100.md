# dtk gap_* and size guesses keep data sections below 100

- status: works
- tags: symbols,gap,objdiff,data
- scope: RPBsbScene
- source: 2026-11-07

symptom: section 9x% though bytes are identical: retail split has gap_* symbols or a 1-byte object + gap, or a pool sized with trailing padding
cause: dtk sizes unknown objects up to the next symbol and names holes gap_*
fix: symbols.txt: delete the unit's gap_* holes, fix sizes (e.g. lbl_804BE648 0x4, lbl_8038DA40 0xC4), name hidden constants (@29483..); split ends can stay
