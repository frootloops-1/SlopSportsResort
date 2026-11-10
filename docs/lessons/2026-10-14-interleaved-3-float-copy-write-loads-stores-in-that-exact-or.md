# Interleaved 3-float copy: write loads/stores in that exact order

- status: works
- tags: float,copy,scheduling,alias
- scope: RPTns_80241d88
- source: opus worker 2026-10-14

symptom: orig lfs x, lfs y, stfs x, lfs z, stfs y, stfs z; ours sequential pairs
cause: possible aliasing keeps source order
fix: f32 x=p->x; f32 y=p->y; d.x=x; f32 z=p->z; d.y=y; d.z=z; (fn_80241D88)
