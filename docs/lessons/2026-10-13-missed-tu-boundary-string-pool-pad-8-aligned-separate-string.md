# Missed TU boundary: string pool + pad + 8-aligned separate string symbol addressed by lis/addi

- status: works
- tags: split,tu,rodata,drawTimeStamp
- scope: RPSysLoadScene
- source: opus

symptom: drawTimeStamp 94.1%: extra addi / scheduling shift; pool lbl_80382568 followed by separate 8-aligned string lbl_803825B0
cause: two TUs merged in splits.txt; in one TU MWCC pools the literal at @stringBase0+off
fix: split into new unit (RP_80186D30.cpp: .text 80186D30-80186E40, .rodata 803825B0-C0, .sdata2 804C1538-48); define NW4R_G3D_PLATFORM_GPU_H and EGG_GFXE_POST_EFFECT_BLUR_H before includes
