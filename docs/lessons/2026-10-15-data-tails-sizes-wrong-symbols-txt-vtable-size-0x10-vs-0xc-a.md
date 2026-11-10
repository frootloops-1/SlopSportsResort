# Data tails/sizes: wrong symbols.txt vtable size (0x10 vs 0xC) and a missing initializer

- status: works
- tags: symbols,data,vtable
- scope: nw4r/ef,revolution/VF

symptom: ef_disc, d_vf_sys code 100% but data not 100%
cause: symbols.txt vtable size inflated by alignment pad (Disc/Cylinder 0x10, siblings 0xC); static struct had an initializer {fn, 0} in .sdata, ours was zero-init sbss
fix: set size:0xC; static PDM_INIT_DISK l_dev_nandflash_init_info = {VFi_nanddrv_init_drv_tbl, 0}
