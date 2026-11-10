# fn_801C6464 matrix transpose: nested for loop reloads source, flat statements forward constants

- status: works
- tags: transpose,matrix,forwarding,loop,unroll,Matrix34f,fn_801C6464
- scope: Pack/RPUtility/RPSportsUtlModelRigid
- source: claude/modelrigid-1026

symptom: Target copies basis->transpose with lfs from self->basis after storing constants; source emits stfs of the constant registers directly (copy propagation), ~93%
cause: MWCC forwards stored values for straight-line field copies (also through static-inline helpers with Mtx params), but not for an unrolled nested loop
fix: Write transpose as for(i<3) for(j<3) dst(i,j) = src(j,i); basis built with EGG::Matrix34f::setBase/setTranslation. 93.0 -> 100, DOL 0 diff
