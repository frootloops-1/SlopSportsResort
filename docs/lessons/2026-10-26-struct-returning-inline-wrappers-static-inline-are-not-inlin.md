# Struct-returning inline wrappers (static inline) are not inlined: declare extern C callees with const T& params

- status: works
- tags: inline,wrapper,vector3f,deferred,stack-slots

symptom: static inline wrappers around struct-returning calls (negVector/mulVector/divideVector) are emitted as local out-of-line functions (bl negVector); EGG header operators (operator*, unary -) emit extra weak __ml__/__mi__ copies; named temporaries shift stack slots
cause: MWCC does not inline functions returning a class with a dtor by value; header inline operators get emitted weak when called out of line
fix: declare the real callee extern C with const T& params (same ABI as T*) and call it directly with nested rvalue args, e.g. fn_801C4FB0(mulVector(a,b), m) where mulVector is a #define for the extern __ml__ symbol; temporaries then get the original slots (fn_801C5240 99.8->100, fn_801C4C38 ->99.9). Also use ext __ml__/__mi__ for the operators in exact fns to drop weak copies
