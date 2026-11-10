# resort: .sbss objects emit in definition order; a 4-byte gap = unreferenced static

- status: works
- tags: resort,rp

symptom: sbss gap between singletons
cause: unused static still emitted
fix: define the unreferenced static (spHomeMenuArcMgr 0x806F4D54, inferred)
