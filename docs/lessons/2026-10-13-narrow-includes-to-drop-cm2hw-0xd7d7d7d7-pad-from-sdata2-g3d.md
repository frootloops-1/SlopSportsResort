# Narrow includes to drop cm2hw/0xD7D7D7D7 pad from .sdata2 (g3d_gpu.h)

- status: works
- tags: sdata2,includes,g3d_gpu,cm2hw
- scope: Pack/RPKernel

symptom: functions 99.x%, reloc-only sdata2 mismatches; leading 8-byte pad in .sdata2
cause: including Pack/RPKernel.h or nw4r/ef.h pulls g3d_gpu.h
fix: include only the unit header; header includes ef_particle.h/ef_particlemanager.h not nw4r/ef.h. Also vtable symbol size 0x38->0x34 fixed .data (alignment pad belongs to split not symbol). Check tools/unit_cmp.py for section scores
