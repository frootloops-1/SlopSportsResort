# ALIGN(n) on an unrelated file-scope array flips CSE and arg-addi order in Draw (ef_drawfreestrategy)

- status: works
- tags: ef,drawfreestrategy,align,cse,addi,attribute
- scope: src/nw4r/ef/drawstrategy/ef_drawfreestrategy.cpp

symptom: Draw 99.66%: target reloads mParticleManager after Draw_GetSizeY switch and emits addi r5 before r4 for PSMTXConcat; ours did not (volatile hack left 2 lines)
cause: static u8 free_tex0_u8[] declared without __attribute__((aligned)); any aligned(4/8/32) changes MWCC's behaviour for the whole TU (as in the billboard strategy)
fix: static u8 free_tex0_u8[] ALIGN(32) = {...}; plain pParticle->Draw_GetSizeY(), no volatile, no inline_depth pragma. DOL 0 bytes, unit Matching. Method: compile matching sibling source in place of the file and cut down until the quirk disappears. The user-supplied reference had the ALIGN(32) all along.
