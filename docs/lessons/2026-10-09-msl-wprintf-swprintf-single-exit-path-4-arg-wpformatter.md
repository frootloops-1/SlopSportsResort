# MSL wprintf swprintf: single exit path, 4-arg __wpformatter

- status: works
- tags: msl,wprintf
- scope: MSL_C wprintf
- source: claude/msl-text wprintf 2026-10-09

symptom: swprintf 94.3%; __wpformatter 83->88.7 after param drop
cause: ss 5-arg formatter with is_secure; early-return layout
fix: drop is_secure param (local const int = 0); swprintf writes NUL if written<maxlen else dst[max-1]=0 and written=-1, single return; delete ss-only vsnwprintf_s; __wStringWrite non-static
