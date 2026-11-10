# Jump table .data ~54% with exact switch code: case-to-value mapping wrong; RPSports_801f9150 split into two TUs

- status: works
- tags: jump-table,tu-split,splits,symbols,RPSports_801f9150
- scope: RPSports_801f9150

symptom: @2732/@3033 jump tables 54% while switch fn 100%; unit .sbss 50, .data 78
cause: case->return mapping in source inverted (identical blocks hide it in objdiff code); unit held two TUs (boundary 0x801F9534, 8-aligned chunk ends, no cross refs)
fix: Compare target .rel label order with objdump -r of ours and reassign cases; split into 801f9150 (TU-1, Matching) + 801f9534; shrink TU-end .sbss symbols to 0x4, delete gap_ sdata2 symbol; @STRING@ weak in symbols.txt drops copy at link (-0x28) so use scope:local.
