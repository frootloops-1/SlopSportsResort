# addLight bne+b-to-return residue: if/else, early return, nested if, goto, one-case switch all fail

- status: fails (SUPERSEDED: solved by one || chain, see 2026-10-26-early-return-chain-trailing-bcc-l2-b-exit-*)
- tags: branch-shape,switch,addLight,eggLightTexture
- scope: egg/gfxe/eggLightTexture

symptom: target 'cmplwi r0,1; bne L2; b L1' vs ours 'cmplwi; beq L1' for 'if(cnt>=2 && (u8)type==1) return'
cause: switch forms give cmpwi (signed) + extra b, worse (99.2); if/else-empty, early return, nested if, goto end all give same beq L1 (99.5)
fix: none with separate if/return statements (parked at 99.5); a single `if (A || B || C || D) return;` chain matches 100.0
