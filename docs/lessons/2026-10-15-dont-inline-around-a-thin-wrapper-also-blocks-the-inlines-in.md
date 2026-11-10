# dont_inline around a thin wrapper also blocks the inlines in its body

- status: fails
- tags: mwcc,inline,pragma
- scope: RPTns_8023c74c
- source: claude/rptns-2

symptom: wrapper fn_X(){InlineBody(self);} wrapped in dont_inline compiled InlineBody as calls (0.6%)
cause: pragma applies to calls inside the wrapped definition
fix: write the wrapper body out explicitly (large enough not to be auto-inlined) instead of pragma
