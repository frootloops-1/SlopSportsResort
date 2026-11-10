# Explicit Construct<T> specializations get inlined; use one generic template after the ctor

- status: works
- tags: template,specialization,inline,deferred,Construct,instantiation-order
- scope: RPGrpDrawPathManager::ctor
- source: opus worker, verified 2026-10-12

symptom: Construct<T> bodies inlined into the caller / emitted in wrong order
cause: explicit template<> specializations are inlined under -inline deferred even when caller is first
fix: Define one generic template<typename T> after the caller: implicit out-of-line instantiations appear in first-use order. Also: init some members in init list, others in body after local decl to schedule loads; put u16 call result in a named local before passing as u8
