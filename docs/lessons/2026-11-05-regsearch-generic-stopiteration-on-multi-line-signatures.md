# regsearch --generic StopIteration on multi-line signatures

- status: open
- tags: tools,regsearch

symptom: regsearch.py fails StopIteration
cause: function_span needs '{' on the signature line
fix: Put the signature on one line with '{' or fix function_span
