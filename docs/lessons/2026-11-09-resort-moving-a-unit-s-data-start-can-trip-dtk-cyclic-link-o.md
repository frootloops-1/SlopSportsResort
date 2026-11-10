# resort: moving a unit's .data start can trip dtk cyclic link order

- status: works
- tags: resort,splits,dtk
- scope: resort
- source: bowling-rest

symptom: Cyclic dependency encountered while resolving link order
cause: .data order disagrees with .text order (GlobalLaneManager 0x806DED78 vs RPBow_80323790 0x806DEE20)
fix: check neighbours' .data starts before reassigning data; drop the move if orders disagree
