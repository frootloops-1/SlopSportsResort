# Hoisted 0.0f const gets top FPR colour; retail has it lowest: route all zeros through a named local

- status: works
- tags: egg,PostEffectBlur,PostEffectBlurSimple,fpr,regalloc,hoist,loop
- scope: egg/gfxe
- source: claude

symptom: loop body uses 0.0f in VEC3 ctor/angle/mtx; ours colours 0.0 near f31, target lowest callee-saved (f22/f25); everything else shifted by one
cause: direct 0.0f literals become an LICM-created constant vreg (high priority); a source variable assigned in the loop keeps its own (late, low-priority) vreg when hoisted
fix: f32 zero = 0.0f; VEC3 center(zero, zero, zero); use zero for every zero in the loop (fn_80097394 98.6->100, BlurSimple setMaterialInternal 99.6->100). Same for volatile frsp colours: read center.x/center.y directly instead of f32 cx = center.x
