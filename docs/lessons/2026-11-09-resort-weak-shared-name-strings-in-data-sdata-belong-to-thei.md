# resort: weak shared name strings in .data/.sdata belong to their first user in link order

- status: works
- tags: resort,data,splits
- scope: resort
- source: archery

symptom: gaps between contiguous unit data ranges hold weak instance-getter name strings
cause: weak data deduped into the first TU that emits it
fix: assign each gap symbol to its earliest referencing unit in link order
