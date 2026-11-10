# EGG Vector3f operator+/-/* not inlined in RP units (calls emitted even with inline_depth)

- status: fails
- tags: Vector3f,inline,RPUtlLoadSaveDataScene
- source: claude/rputl-lsds-1027

symptom: Vector3f-operator version of box builder emits bl __pl__/__mi__/__ml__
cause: operators returning Vector3f by value are not inlined under these flags
fix: failed: use scalar code; whole-vector operator= copies do inline
