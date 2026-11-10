# DrawPathDOF: inline getter args are pre-evaluated and hoisted; hoisted loop-constant FPR colours follow creation order of the constant's first use

- status: works
- tags: drawpathdof,regalloc,fpr,scheduler,debugger
- scope: egg/gfxe/eggDrawPathDOF

symptom: Standard: GetNearZ/GetFarZ loads hoisted above the fog colour copy; Lite: f26/f28 swapped between the unsigned magic double and 0.5f, alloc width/height temp slots swapped
cause: initial pcode shows inline-getter results evaluated first as @N temps (so loaded first, scheduled first); hoisted loop constants (0.5f, 1.0f, unsigned-int magic) get vregs in order of first use in the loop body and are coloured highest-first, and the u16->float conversion that first needs the magic double sat after dist; alloc args are evaluated height-first and the scheduler then emits width first
fix: Standard: raw +0x18/+0x1C reads (marker) 9 -> 3 lines. Lite: int iw=width*scale first, then ih (68 -> 54); sh = height*absZ, sw = width*absZ before dist, inv = 1.0f/tan before dist (-> 30); zero declared in the loop (-> 26). regsearch hand sites/orders ranked these wrongly (its metric ignores FPR colour): use asm_diff line counts
