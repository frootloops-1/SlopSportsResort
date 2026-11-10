# RPBsb fn_8026E62C stuck at 97.7: loop-body load order x,dist,y,z not reproducible

- status: fails
- tags: near-miss,float,operator
- source: RPBsb_8026e62c

symptom: orig loads x,dist,y,z; ours dist first, z before y
cause: unknown; vec temp construction form
fix: Dead ends: ctor init-list vs body, nw4r VEC3/EGG Vector3f, friend/scalar-first operator*, NRVO, const-ref params, reversed args, accessor, indexed loop, 6 decl orders (96.1-97.8), aggregate vec. Best copy: scratchpad best977.cpp. Next: permuter once C++ parser works
