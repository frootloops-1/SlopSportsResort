# TU-end pad: delete gap_ symbol / shrink sbss symbol

- status: works
- tags: symbols,sdata2,sbss,pad
- scope: RPGol_802bb044
- source: sonnet-worker

symptom: .sdata2 66.67 with gap_12_804C49EC at TU end; .sbss 50 with lbl_804BF948 size 0x8
cause: dtk gap symbol / pad-inclusive size has no counterpart in our object
fix: delete the TU-end gap_ symbol; shrink the last symbol to its real size
