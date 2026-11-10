# Direct lwz r12 vtable call needs real virtual member, not fn-ptr cast

- status: works
- tags: virtual
- scope: RPGol_802ae9ec
- source: fn_802AE9EC

symptom: extra temp reg (r6) with (*(void***)m)[n]
cause: manual vtable indexing
fix: declare dummy virtuals so slot offset matches (idx*4+8); separate view struct per call signature
