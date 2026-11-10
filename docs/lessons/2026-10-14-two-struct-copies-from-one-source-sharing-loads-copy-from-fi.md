# Two struct copies from one source sharing loads: copy from first destination

- status: works
- tags: struct-copy,lwzu
- scope: RPTns_8023e934
- source: sonnet worker 2026-10-14

symptom: orig copies global once (lwzu) and stores twice
cause: second assignment reads the first destination
fix: *(T*)&dst1 = global; *(T*)&dst2 = *(T*)&dst1; (fn_8023EDE0)
