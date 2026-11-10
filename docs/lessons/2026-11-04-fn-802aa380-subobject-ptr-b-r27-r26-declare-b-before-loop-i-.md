# fn_802AA380 subobject ptr b r27->r26: declare b before loop i in same inline

- status: works
- tags: regalloc,inline,decl-order,RPGol
- source: RPGol_802a7a40 2026-11-04 opus

symptom: ctor inline: subobject ptr b=a+0x10 took r27 (dead player reg) instead of r26 (dead loop i reg)
cause: colouring is descending vreg, each node takes the lowest free already-handed callee-saved reg; b was coloured before i (i in a nested inline). Inline locals: last declared coloured first
fix: move the 3D-actor loop into GolSndCt and declare 'u8* b; int i;' (b first) so i colours before b; 99.5->100
