# Draw: alpha/h/simple/x register permutation (r31/r29/r27) not reachable by simple source reshuffles

- status: fails
- tags: register,callee-saved,draw
- scope: egg/gfxe/eggShadowTexture
- source: shadow-1026

symptom: 98.4: target alpha=r31,w=r30,h=r29 (x reuses r29, simple=r27); ours h=r31,alpha=r29,x=r27,simple=r31
cause: interference-graph colouring order
fix: tried: alpha before w/h; h before w; x,y hoisted to top (98.2); bool alpha (97.9); inline enable test (96.6); simple declared at top; x/y from pScreen->GetDataEfb() twice (96.0). none gained
