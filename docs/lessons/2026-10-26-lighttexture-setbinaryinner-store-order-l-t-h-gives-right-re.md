# LightTexture SetBinaryInner: store order L,T,H gives right regs (99.8) but swaps sth order

- status: fails
- tags: SetBinaryInner,eggLightTexture,register-wall,store-order
- scope: egg/gfxe/eggLightTexture
- source: lt-data-1026

symptom: regs r5/r0 right only when drawType is defined/stored before hi; then stores come out lo,cmplw,type,hi instead of hi,cmplw,type,lo
cause: scheduler follows source store order; reg colouring follows vreg def order; need both H-T-L emission and T-before-H colouring
fix: tried all 6 H/T/L permutations, SetMask helper (pairs hi+lo), SetMaskHi helper, local type/mask in 4 forms: best LTH 99.8; remaining 2 store-order lines
