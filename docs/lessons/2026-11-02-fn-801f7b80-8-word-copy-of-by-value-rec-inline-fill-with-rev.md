# fn_801F7B80 (8-word copy of by-value rec): inline fill with reversed params gives loads w0..w7 hoisted, only vt vreg number off

- status: fails
- tags: RPSports,colouring,inline-args,fn_801F7B80
- scope: RPSports_801f6ebc

symptom: target vt in r12, w0 r11 .. w7 r0; ours vt r5, w0 r12 .. w7 r0
cause: named locals a..h are numbered in reverse declaration order (a highest) and first-loaded gets r0; global-address lis/addi vreg is created lazily at the store so it outnumbers w loads, coloured first. Inline fn with params (h..a) and args (w7..w0) fixes w order (same 93.7) but vt stays highest
fix: tried: named locals either order, SpRecObj copy-ctor (87.8), 8-iteration loop (87.8), SpRecBody struct copy (86.6), vt as rightmost/leftmost param, named vt local, comma-expr vt store (stw too early), double inline wrapper. Open: need vt lis vreg created before the w loads while its stw is scheduled after them
