# resort: Resort Bowling turns ogws inlines into out-of-line functions

- status: works
- tags: resort,bowling,inline
- scope: resort
- source: bowling-lanes

symptom: ogws inline helpers/copy ctors/struct copies appear as calls (fn_80243A94 vec3 copy, fn_80243A30 mtx34 copy, Vector3f ctors, camera apply-path)
cause: Resort build inlines far less; RPBow_80323790 inlines nothing
fix: declare and call the out-of-line function; RPBow_80323790 uses a file-wide #pragma dont_inline on. Check for an out-of-line copy before forcing an inline
