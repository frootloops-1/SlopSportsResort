# fn_harness find_def matches call sites like 'if (fn_X(...)) {'

- status: open
- tags: tools,fn_harness
- scope: tools
- source: claude/bsb5a3-c-1107 opus

symptom: variant replaces a caller body instead of the definition; compile fails at the caller line
cause: regex ^[^\n;]*\bfn\s*\( allows leading whitespace/if (
fix: use ^[A-Za-z][^\n;(]*\bfn ... (scratch copy fixed it); orchestrator should patch tools/fn_harness.py
