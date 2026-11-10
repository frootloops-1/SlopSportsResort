# fn_80320EFC: MWCC simplify model reproduces colouring exactly; m local stuck in pass 2

- status: works
- tags: RPBow_80320EFC,fn_80320EFC,regalloc,fpr,model
- scope: fn_80320EFC

symptom: loop-1 15.0f/m f18/f19 swap and panel locals f19 vs f25 / j-loop x f29 vs f19 (79 harness lines)
cause: Allocator: repeated ascending passes remove nodes with degree (phys+unremoved vregs) < 32 (FPR; GPR 27-29); colour in reverse removal; callee-saved = lowest used free else new from top. Named m (34 nbrs) stuck in pass 2 so coloured before the panel locals and took f19
fix: Pass BowMapAngle() straight into BowCos (carrier = inline return @var), reassign the param in MapAngle's last branch (one fewer temp neighbour -> carrier degree 31 -> pass 1), declare panel locals ox,oy,w,h,sx,sy: harness 79 -> 12. Simulate graph edits offline from regalloc-*-assigned.txt before editing source
