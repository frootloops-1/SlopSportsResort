# dont_inline on a function also blocks its callees' inlining

- status: works
- tags: mwcc,inline,dont_inline

symptom: restart()/stop() inside a dont_inline region become bl
cause: pragma applies to inlining inside the region
fix: hand-expand the inline bodies with raw offset stores, or keep the pragma off the caller
