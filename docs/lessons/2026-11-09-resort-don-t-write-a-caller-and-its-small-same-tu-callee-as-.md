# resort: don't write a caller and its small same-TU callee as extern C functions (deferred inliner folds it)

- status: fails
- tags: resort,inline,first-pass
- scope: resort
- source: basketball

symptom: original keeps bl to a base dtor/small ctor; ours inlines it
cause: -inline deferred inlines small same-TU functions
fix: write the callee in another TU or as a real member with the right linkage; a 12-byte float struct returned by value copies via lwz 8+4, *out = *v gives lfs/stfs
