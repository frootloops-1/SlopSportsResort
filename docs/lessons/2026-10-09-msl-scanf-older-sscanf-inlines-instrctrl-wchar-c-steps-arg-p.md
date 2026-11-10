# MSL scanf: older sscanf inlines __InStrCtrl; wchar %c steps arg_ptr by 1

- status: works
- tags: msl,scanf
- scope: MSL_C scanf
- source: claude/msl-text scanf 2026-10-09

symptom: sscanf 27%; __sformatter 99.99 with one addi immediate differing
cause: ss-only helpers (isspace_string, vsscanf) added; %c wchar branch used sizeof(wchar_t)
fix: Delete the helpers and inline __InStrCtrl in sscanf; use arg_ptr++ in the %c wchar branch (the %[ branch keeps (wchar_t*)arg_ptr + 1)
