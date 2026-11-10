# fn_8024929C (RPTns_80249284): 64-subset hoist sweep and 4 copy spellings all <= 98.5 (nogain)

- status: fails
- tags: rptns,8024929c,struct-copy,hoist,nogain
- source: worker nx-929c 2026-10-31

symptom: 98.5%: target loads pos.y,pos.z,target.x,target.y early and target.z late, keeps d.y/d.z as reloads of f50; cur=*target is a 3-reg load-all-then-store copy (ours reuses r0)
cause: scheduling plus aggregate-copy shape, no genuine source form found; TnsVec3 is a plain local 3xf32 struct
fix: Dead: all 64 subsets of hoisted px,py,pz,tx,ty,tz (only full tx,ty,tz = 98.5, p* irrelevant), tnsAdd/tnsSub inline (96.0), copy as assignment 93.0 / member-wise 93.0 / const-ref 96.0 / temp struct 96.0, copy moved ahead of s28 loads 93.5. Untried: check other Tns units for the d=f50-target / cur=*target pattern; u32 punning 98.7 needs R17.
