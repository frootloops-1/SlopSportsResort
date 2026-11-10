# Damped tangent: param coalesced into f31 with fsubs; call VEC3Scale directly and move later dot after it

- status: works
- tags: mwcc,fpr,coalesce,VEC3Scale,param
- scope: Pack/RPUtility/RPUtlRigid fn_801BA284

symptom: fsubs f31,f31,f3 (damping-1 reuses damping's callee-saved reg); target puts it in a volatile reg
cause: VEC3 operator*(f32) temp / statement order
fix: nw4r::math::VEC3Scale(&delta, &tangent, damping - 1.0f) explicit call (36->18 lines), then compute 'incoming = VEC3Dot(...)' after delta (->100). Fake copy (new_var = damping) from permuter pointed at it
