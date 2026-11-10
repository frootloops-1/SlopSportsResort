# ef_drawfreestrategy: ctor must be emitted first; foreign-decomp pDesc local costs a GPR

- status: works
- tags: ef,drawfreestrategy,order,register
- scope: src/nw4r/ef/drawstrategy/ef_drawfreestrategy.cpp

symptom: order_check: ours DrawQuad first, target __ct first; reference file with EmitterDesc pDesc local gives _savegpr_22 (99.31%)
cause: ctor defined after DrawQuad/DrawGetSizeY; pDesc kept live across the loop adds a saved GPR
fix: Define DrawFreeStrategy::DrawFreeStrategy() {} before DrawQuad (order fixed, merged 059c8b120). Do not keep pDesc live; Draw addi r5/r4 and the 0xc8 reload (needs volatile hack) remain open.
