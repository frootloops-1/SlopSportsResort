# RPBow_80320EFC panel locals: sy,ox,oy,w,h,sx order (perm) + sprintf arg via local

- status: works
- tags: RPBow_80320EFC,fn_80320EFC,decl-order,fpr,sprintf
- scope: unit

symptom: debug-panel FPR locals and a sprintf string-base GPR coloured off
cause: function-level sy/h locals and direct self->x518->f58 sprintf arg change vreg order
fix: block-scope all panel locals, 720-perm via fn_harness --perm gave sy,ox,oy,w,h,sx for both panels (99.1->99.3); 'f32 speed = self->x518->f58; sprintf(vbuf, fmt, speed)' fixed string base r4/r5 (121->116 diffs)
