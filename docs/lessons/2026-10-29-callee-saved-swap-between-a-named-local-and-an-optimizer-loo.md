# Callee-saved swap between a named local and an optimizer loop temp: give the local a LATE vreg via an inline getter (RPBox_803048c4 fn_80304B58)

- status: works
- tags: regalloc,vreg,inline-getter,mwcc_dbg,RPBox_803048c4,data-order
- scope: RPBox_803048c4

symptom: fn_80304B58 99.4%: body r22/table ptr r23 vs target body r23/ptr r22, tail iterators shifted one register
cause: MWCC colours in descending vreg number. Named locals get early numbers; loop strength-reduction temps (@354) come later, so the temp was coloured before body. Values produced by inlined functions get late numbers (hAvatar etc. were r64+).
fix: static inline RPGrpModel* BoxBodyModel(BoxView*, int i){return v->slot[i].obj->m[1];} and 'RPGrpModel* body = BoxBodyModel(self,i);' -> function identical. Separate trap: objdiff showed .data 100% but DOL had 65 bytes off: .data object ORDER differed (lbl_803C9C08 defined after the tables). Always flip + dol_diff, and compare symbol addresses in .data, not only per-symbol percent. mwcc_dbg.sh loop is ~10s.
