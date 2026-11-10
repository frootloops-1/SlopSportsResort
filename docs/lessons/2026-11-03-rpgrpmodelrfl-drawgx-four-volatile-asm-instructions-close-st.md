# RPGrpModelRfl DrawGX: four volatile asm instructions close store scheduling residue (R17)

- status: works
- tags: RPGrpModelRfl,DrawGX,mwcc,scheduling,inline-asm,R17
- scope: Pack/RPGraphics/RPGrpModelRfl
- source: 2026-11-03; build/evidence/rfl-20261103/third/volatile_four; compiler source src/compiler/backend/InlineAsmPPC.c in doldecomp/mweppc

symptom: 38/39 functions exact; DrawGX 99.652176%, retail stores spDrawModel between lis and lbzx; C++ delays it until after addi.
cause: Normal inline asm is rescheduled like C++. Assembler .scheduling off marks individual instructions as side effects. Applying it only to stw/lbzx fixes their order but leaves lis too late. Four serialized instructions preserve the whole critical sequence.
fix: After exhausting C++ levers, retain a MATCH-PENDING R17 block: C++ initializes register type=mMaterialType, table=TEV_STAGE_NUM and model=this; asm .scheduling off emits lis setting,sDrawCoreSetting@ha; stw model,spDrawModel; lbzx type,table,type; addi setting,setting,sDrawCoreSetting@l. C++ writes setting->tevStageNum and reverseCulling, then passes setting to both RFL load functions. All six GC builds give DrawGX 100%, 39/39 exact and all eight section scores 100%; emission order unchanged. This is a hand-scheduled workaround, not recovered original C++.

Verification: Matching flip gate passed: DOL 0 bytes, equal 3,995,168-byte sizes; three known collisions (__FUNCTION__$1983, CPUFifo, GPFifo). No new emission-order mismatch. Source and ledger retain MATCH-PENDING R17.

References: [compiler inline assembler](https://github.com/doldecomp/mweppc/blob/main/src/compiler/backend/InlineAsmPPC.c) (`IADirective_Scheduling`, `IAFlagsB_Volatile`, `InlineAsm_TranslateIRtoPCode`); [forecast compiler flags](https://github.com/doldecomp/forecast/blob/main/configure.py); [related ScnRfl draw setup](https://github.com/doldecomp/forecast/blob/main/src/nw4r/g3d/g3d_scnrfl.cpp). Forecast has no Pack/RPGrpModelRfl source. Its channel flags are not evidence of SportsPack flags; the required six-version sweep was also run locally.
