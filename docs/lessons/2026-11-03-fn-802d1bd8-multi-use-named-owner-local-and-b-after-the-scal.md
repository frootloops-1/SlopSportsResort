# fn_802D1BD8: multi-use named owner local and b after the scale call (62 -> 34, plain source)

- status: works
- tags: fn_802D1BD8,RPBox_802cf93c,regalloc,vreg-order
- scope: mwcc GC/3.0a5.2
- source: docs/tasks/RPBoxScene.md tenth pass

symptom: owner/&local GPR pair swapped (owner r7 vs target r8) and s.y/s.x/v.x FPR loads coloured in the wrong order
cause: self->owner re-read in the if(state==8..) block was a codegen temp (high vreg, coloured first); address-of-stack temp is lower. FPR load vregs are created in source order (b first), target creates s.x, v.x before s.y
fix: BoxPl* ow = self->owner; used 4x in the block (a multi-use named local is a real low vreg, coloured last); move f32 b = y*s.y after PodVEC3Scale(&out->pos,&X,s.x*v.x+cw). Remaining 34 lines are psq temp FPR colours in PodSub/PodProject/PodAdd; pointer locals pa/pb (48) and body local (54) are worse
