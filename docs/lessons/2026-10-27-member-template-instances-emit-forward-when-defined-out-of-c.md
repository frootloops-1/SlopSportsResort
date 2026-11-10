# Member template instances emit forward when defined out of class (non-inline), reverse when in-class never_inline

- status: works
- tags: template,emission-order,weak,egg
- scope: egg/gfxe/eggModelBoundingInfo
- source: mbi-1027

symptom: createShape<Sphere>/deleteShape<Sphere> emitted before <AABB> (retail after); in-class definitions with __attribute__((never_inline)) and dummy instantiations/dead refs did not change it
cause: in-class (implicitly inline) member templates kept out of line are queued in reverse of first use; out-of-class non-inline member template definitions are emitted in forward first-use order
fix: declare createShape/deleteShape in the class, define them out of class after the class (no inline, no never_inline) -> AABB before Sphere, code unchanged, DOL 0 bytes, no marker
