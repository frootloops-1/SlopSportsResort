# early-return chain: trailing 'bcc L2; b exit' = one if(A||B||...||(C&&D)) return

- status: works
- tags: branch-shape,early-return,or-chain,addLight,eggLightTexture
- scope: egg/gfxe/eggLightTexture

symptom: first guards 'beq exit' directly, last guard 'cmp; bne L2; b exit; L2:' (target) vs ours 'beq exit'
cause: MWCC leaves the last term of a single || condition chain as bcc-over-b to the return; separate if/return statements each get inverted to a direct bcc
fix: merge all early-out guards into ONE if (!a || !b || !c || (d && e)) return; addLight 99.5->100. Same shape in nw4r lyt TextBox::DrawSelf (A||B||C return). Finder: scan asm for bcc .Lx; b .Lexit; .Lx: preceded by cmp
