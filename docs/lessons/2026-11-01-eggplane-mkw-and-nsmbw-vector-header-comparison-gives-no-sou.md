# eggPlane MKW and NSMBW vector-header comparison gives no source gain

- status: fails
- tags: egg,plane,reference,header,mkw,nsmbw
- scope: egg/geom/eggPlane
- source: codex-eggplane-1101

symptom: project 73.17073%, helper exact; final EGG unit remains open.
cause: MKW lib/egg/math/eggVector.hpp and mathTypes.hpp use the same POD/VEC3 inheritance and scalar member dot; direct component ctor differs from our base ctor. NSMBW include/lib/egg/math/eggVector.h uses set-based ctor. Both ctor forms preserve baseline. Omitting the user destructor regresses project to 25.80488-30.48780; MKW non-Broadway output-style subtraction in a return expression gives 34.02439 or worse. MKW paired-single static dot is incompatible with the target scalar instruction shape. No matching Plane implementation found in these source trees.
fix: No header/source changes retained; six GC builds agree for all compilable probes. References and revision plus header-results.json and header-probes.py under /private/tmp/ogws-eggplane-1101/build/evidence/eggplane-reference/. Move to source-linked unit closeouts; require new original-source evidence before revisiting Plane.
