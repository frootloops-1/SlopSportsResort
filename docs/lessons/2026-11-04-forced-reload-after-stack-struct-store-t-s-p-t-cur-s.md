# Forced reload after stack-struct store: T s = *p; T& cur = s;

- status: works
- tags: reload,alias,cse,stack-struct
- scope: global
- source: docs/llm_matching_tricks.md 3.6

symptom: target reloads a value from memory after a store to a stack struct; ours CSEs it
cause: Taking a reference to the local copy makes MWCC treat the store as possibly aliasing
fix: T store = *pos; T& cur = store; (plain locals, helper refs don't). Candidate honest replacement for R17 row 212 (b340 fn_8020E464)
