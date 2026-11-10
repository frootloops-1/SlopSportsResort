# sdata2 pool order: constant in a local variable / division in an inline

- status: works
- tags: sdata2,pool,order,constants
- scope: Pack/RPSports/RPTnsScene/RPTns_8022a740
- source: claude-opus

symptom: 13.913043f pooled last; 2.0 pooled before 16383
cause: pool order follows codegen order
fix: f32 step = 13.913043f next to z = -160; RandS() inline returning (r-0x4000)/16383.0f then 2.0f*RandS()
