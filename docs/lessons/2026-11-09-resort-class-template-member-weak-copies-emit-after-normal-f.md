# resort: class-template member weak copies emit after normal functions in member declaration order

- status: works
- tags: resort,template,weak,ordering
- scope: resort
- source: swf-template-batch-2026-11-09

symptom: Unk_StateMachine<T> weak copies in the wrong place
cause: implicit instantiations are emitted after all normal functions, in class member declaration order; a file-scope explicit instantiation emits like a normal definition (reverse source order under -inline deferred)
fix: order members in the shared header as retail emits them; explicit instantiations only as R17 stand-ins for unwritten callers (#28)
