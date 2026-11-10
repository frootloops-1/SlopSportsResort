# frsp f0 for fields but stfs f1 for stack: SetScale(VEC3(v,v,v)) with f32 param

- status: works
- tags: mwcc,float,vec3,frsp
- scope: RPGolDrawManager

symptom: fn_802945F4: orig stack stores use f1, field stores f0=frsp f1; f64 param + volatile locals gave f0 everywhere
cause: VEC3 temp constructed from the f32 arg then copied by Frustum::SetScale
fix: f32 param; frustum->SetScale(nw4r::math::VEC3(v,v,v))
