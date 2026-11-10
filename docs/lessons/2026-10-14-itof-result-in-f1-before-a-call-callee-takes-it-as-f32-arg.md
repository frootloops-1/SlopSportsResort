# itof result in f1 before a call: callee takes it as f32 arg

- status: works
- tags: itof,float,args,signature
- scope: RPTns_80248bb8
- source: opus worker 2026-10-14

symptom: final int-to-float fsubs writes f0 vs orig f1
cause: the converted value is passed to the callee (fn_801F938C(f32 level))
fix: check callee's real signature and pass the float (fn_80248D00/EBC)
