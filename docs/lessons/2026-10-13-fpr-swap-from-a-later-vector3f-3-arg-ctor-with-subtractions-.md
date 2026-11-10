# FPR swap from a later Vector3f 3-arg ctor with subtractions; split Rect scaling into const Rect& pane -> separate rect

- status: works
- tags: fpr,vector3f,ctor,rect,callee-saved
- scope: Pack/RPKernel/RPSysLytBounding

symptom: two sqrt lengths in swapped f30/f31; rect right/top swap
cause: 3-arg ctor with two subtraction args changes allocation; in-place rect.f*=s ordering
fix: default ctor + .x/.y/.z field assignment; write rect.left/right/top/bottom = pane.f*l from const Rect& pane; bisect by compiling cut-down copies standalone
