# pointer-increment loop over struct array

- status: works
- tags: loop,rpbsb
- source: RPBsb_802803b0 2026-10-16

symptom: lwz+add per iteration instead of addi r31,stride
cause: &arr[i] indexing
fix: T* e = arr; for(...) {...; e++;} (fn_80280EE0 74.6->100)
