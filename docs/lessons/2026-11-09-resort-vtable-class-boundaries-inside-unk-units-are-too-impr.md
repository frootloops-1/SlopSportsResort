# resort: vtable-class boundaries inside unk units are too imprecise to apply (ogws eval)

- status: fails
- tags: resort,splits,game-code,vtable,boundaries
- scope: splits.txt game code
- source: class_bounds.py 2026-11-09

symptom: Wanted name-free file boundaries inside unk/sinit_* game units
cause: ogws game files often hold several classes in separate runs; a class change with no straddling class is a true boundary 85% of the time but exact placement is 44-56% (70% at best), recall ~10%
fix: None applied. Use tools/class_bounds.py eval / tools/file_signals.py to re-test new signals on ogws before applying; split game units from matching evidence instead
