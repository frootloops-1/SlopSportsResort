# Load a pointer before a struct copy: make the copy target address-taken (kill)

- status: works
- tags: colouring,IRO,propagation,kill,steering-cast,R17,RPGol,fn_802926EC
- scope: Pack/RPSports/RPGolScene/RPGolFieldManager
- source: golfield-fn-1102

symptom: pointer used as the base of a 3-word struct copy is coloured before the 9 earlier copy temps and takes r6/r3 instead of r28
cause: IRO expression propagation moves a single-read load to its use (after the basis struct copy) because stores into a non-address-taken local are not kills; the load becomes a codegen temp numbered above the copy temps. Stores into an address-taken object (m, or a frame viewed through a cast of &f) are kills, so the load is done at the ctor-argument point
fix: pass the expression directly as the ctor arg (no named local) and read the frame through (const f32 (*)[3])&fr in the inline matrix builder (R17 marker, ledger 78). Union views, &fr.r.x.x, pointer params and named locals with dead extra reads do not work
