# RPBsb_80285870 / 8026a198: lumped .data symbol = N x 12-byte ptmf locals; trailing zero word after a float table is padding

- status: works
- tags: symbols,ptmf,data-split,padding,RPBsb_80285870,RPBsb_8026a198
- scope: RPBsb_80285870 RPBsb_8026a198

symptom: RPBsb_80285870 .data 0%, held items 'target bytes not zero and owned by no compiler symbol' / '@10510 referenced at inconsistent target offsets'; RPBsb_8026a198 lbl_8038CE88 24!=20
cause: lbl_803C72E0 (0x198 = 34 x 0xC) was one lumped symbol; our object emits 34 local 12-byte pointer-to-member constants @10508..@10541 tiling it exactly (same pattern as @2352.. in RPBsb_802656a4). lbl_8038CE88 holds 5 floats (0x14) plus a 4-byte alignment-pad word.
fix: symbols.txt: replace lbl_803C72E0 with @10508..@10541 at 0x803C72E0+0xC*k, type:object size:0xC scope:local data:4byte (get the @N numbers from nm of our built object); shrink lbl_8038CE88 to 0x14. Result: 80285870 .data 0->66%, fn_80288E90 83.3->84.3, 119/120 syms; 8026a198 .rodata 100%; DOL 0. Remaining in both units is source-side data definitions (vtables lbl_803C7478/7520 and lbl_803C5F58/5FB8, .sdata float tables, .sdata2), not symbols/splits. data_fix.py plan found no mechanical fix for 8026a198 and held 12 for 80285870 (all explained by the lump).
