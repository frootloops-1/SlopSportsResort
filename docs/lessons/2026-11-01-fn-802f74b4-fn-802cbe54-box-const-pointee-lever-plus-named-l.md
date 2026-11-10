# fn_802F74B4 / fn_802CBE54 (Box): const pointee lever plus named-local/ordering fixes close both functions (no markers)

- status: works
- tags: rpbox,802f74b4,802cbe54,const,fpr,stack-slot,constsweep
- source: worker cs0 2026-10-31 (constsweep)

symptom: fn_802F74B4 96.0% (46 lines): 0.0/1.0 const reg swap f1/f3 vs f2/f1 and hp/product swap f4/f6; fn_802CBE54 98.3% (18 lines): cmpwi scheduled above stw 0x78 and two 8-byte BoxVec2 stack temps in swapped slots 0x8/0x10
cause: constness of the pointee (SbHitter*, BoxStg*) changes alias analysis scheduling; FPR vregs are coloured descending, named locals numbered in reverse declaration order below IRO/back-end temps; a Vec2 returned by value from an inline gives swapped slots, a by-value setter param copy takes the lowest slot
fix: fn_802F74B4: const SbHitter* o in def and thunk fn_802F9F20 (thunk must match or the build fails); f32 s = 1.0f - r moved before self->unk9C = 0.0f; drop hp local (self->unk9C -= dmg) and name the product (f32 pw = o->f28 * o->fF0; f32 dmg = o->fE0 + o->fD0 * pw) - each alone is worse (16 lines). fn_802CBE54: const BoxStg* self (cmpwi order); compute BoxVec3 out and BoxVec2 v in the caller and pass to a by-value inline BoxData::SetPos(BoxVec2 p) instead of a BoxVec2-returning BoxToScreen inline. Units stay NonMatching (RPBox_802f71b0 37/43, RPBox_802cb9cc 25/29).
