# regsearch: validated register-order search; Texture 99.53 -> 99.72; colour order is vreg identity

- status: works
- tags: regsearch,permuter,ef_animcurve,Texture,U8,colouring,tool
- source: xfer-1028

symptom: decomp-permuter fails on C++ and large float fns; hand declaration sweeps (~250 builds) plateaued on ef_animcurve
cause: tools/regsearch.py compiles real variants with the unit ninja command and scores opcode/shape equality plus per-role colour-rank displacement vs the original; validated by rediscovering the known __CalcLFO fix in 9 generations (score 0 = verify 7/7). Texture: hoisting t/count/n to function scope + 2 independent swaps gives 99.72 (32 -> 21 lines). regroles shows Texture differs by one 3-role rotation: the pHeader/pCmdList saved copy (mr r31,r3) is coloured first in the original, last in ours. U8 roles have identical live ranges/use counts/loop weights in both builds yet different colour order and neither follows weight*(2*uses+defs): the order is IR vreg identity/age, not final-code features
fix: Use regsearch for any register-order wall (docs/regsearch.md); read rank and lines, not only score (first metric rewarded opcode alignment alone and mis-ranked a variant). Remaining Texture gap: make pHeader a vreg that is not merged with the incoming parameter copy
