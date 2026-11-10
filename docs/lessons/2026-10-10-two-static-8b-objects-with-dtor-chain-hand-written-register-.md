# Two static 8B objects with dtor-chain: hand-written __register_global_object init + force_active .ctors ptr

- status: works
- tags: rpgolmath,static-init,ctors,register_global_object
- scope: RPGolMath
- source: sonnet

symptom: static class ctor path mismatched
cause: compiler generated ctor/dtor structure differs
fix: file-static Vec2 + u8[0xC] link, call __register_global_object(&obj,(void*)dtor,link) in extern C fn; force_active pointer in .ctors
