# ShadowTexture Draw: generic regsearch (1739 evals) no gain; wall is where x lands after h/restoreClearColor die

- status: fails
- tags: shadowtexture,draw,regsearch,version-sweep
- scope: egg/gfxe/eggShadowTexture

symptom: Draw 98.4%, 37 DOL bytes: target alpha=r31 h=r29(+x) restoreClearColor=r27 (9-259); ours h=r31 alpha=r29 x joins r27 (9-330)
cause: x is coloured into restoreClearColor's reg in ours and into h's reg in the target; both free at the same point so it is colour-order, not liveness. Older compiler builds are worse (99.43 vs 99.60), so build is not the lever
fix: none: regsearch --generic -j4 12 min, best = baseline 203.5 (op 2 imm 8 reg 30 rank 4). Tool quirk: --fn-hint needs the signature and '{' on ONE source line (multi-line signatures raise StopIteration), and the function arg must be the mangled name because 'Draw' matches DrawShape. Next: hand-written sites.json or a real regalloc model
