# Negated tangent: compute v-p*n in x,y,z then *= -1.0f per component

- status: works
- tags: mwcc,schedule,fmuls,vec3
- scope: Pack/RPUtility/RPUtlRigid fn_801B9EC0

symptom: loads x,y,z but fnmsubs y,z,x order; source wrote (v.y-p*n.y)*-1 in y,z,x
cause: single-expression per component
fix: tangent.x = v->x - p*n.x; ...y; ...z; then tangent.x *= -1.0f; .y; .z (100 -> 42 lines); and compute each rotated scale right before its accumulate
