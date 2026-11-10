# -inline deferred: pragma state at END of file decides inlining of static inlines

- status: works
- tags: inline,pragma
- scope: RPGol_802aaf88
- source: fn_802ABD50

symptom: static inline helpers emitted as bl
cause: file ends under dont_inline on
fix: end the file with #pragma dont_inline off
