# fn_801F9150 closed: struct copy from a by-value class param, not a pointer

- status: works
- tags: regalloc,colour,struct-copy,by-value,RPSports_801f9150
- scope: Pack/RPSports/RPSportsCommon/RPSports_801f9150

symptom: r30/r31 swap (obj vs n/a) plus copy temps ascending r5,r0,r6.. vs target descending r12..r0; field-by-field from src pointer interleaves lwz/stw (86.9)
cause: named load temps s4..s20 got LOW vregs, were pushed in sweep 1 before obj and dropped obj's degree under K, so n (temp r68) coloured first. A pointer src blocks hoisting the loads above the c stores (aliasing).
fix: take src by value (CtorView src) and write c.vptr = vt; c.fN = src.fN; ... -> loads hoisted, temps get late vregs, obj coloured first -> 100, no markers. Diagnosed with mwcc_dbg colouring dump.
