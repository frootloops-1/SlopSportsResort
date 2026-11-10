# ef_animcurve Rotate: key-setup reg order and dual-random hash add order not reachable by reshaping

- status: fails
- tags: ef_animcurve,rotate,register
- scope: nw4r/ef/ef_animcurve
- source: worker a98dbf84, 2026-10-27

symptom: Rotate 98.5%: orig v0=k0+0xc in r6 early so k1 multiply lands r7; ours multiply r6, k1 r11. Dual-random branch orig add(loop*C3, seed*C1+hdr*C2) then +(cmd*C4+K), random0 in r9 vs ours r4
cause: unknown; allocation/operand-order choice of compiler
fix: dead: 5 key-setup statement reorders 97.7-98.4; hash as one expr loop*C3+(S+H)+(C+K) fixes add order but swaps C3/C4 const regs (98.4); S+H separate statement same as baseline; flat/other shapes 96.2-98.4. Permuter not run on Rotate yet
