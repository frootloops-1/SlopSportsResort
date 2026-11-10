# fn_8020E464: float loop stores interleaved with member load -> compute nx/ny locals then store

- status: works
- tags: scheduling,loop,floats,RPSports_8020b294
- source: RPSports_8020b294

symptom: loop body wrote l->e[i].x then loaded e[i].a before computing y (57%)
cause: store to x blocks hoisting of the later e[i].a load; target computes both values then stores
fix: f32 nx=...; f32 ny=...; e.x=nx; e.y=ny (nx first; ny first drops to 73.7); 57.3 -> 85.5, +base.x/w/h/base.y order -> 88.7
