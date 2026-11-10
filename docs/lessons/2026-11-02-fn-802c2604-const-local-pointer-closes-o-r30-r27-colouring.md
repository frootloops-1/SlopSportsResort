# fn_802C2604: const local pointer closes o r30->r27 colouring

- status: works
- tags: regalloc,const,local,colouring,RPGol
- scope: Pack/RPSports/RPGolScene/RPGol_802c16a4

symptom: pointer local loaded from a global, passed to a call and read after later calls lands in a reused saved reg (r30) instead of the target's r27
cause: mwcc_dbg dump: the non-const initialised local was turned into an expression temp (vreg above all named locals, coloured early); a const local keeps a named-local vreg and is coloured after the loop index
fix: declare it 'T* const o = global;' (99.8 -> 100). Check the dump's initial code: a declared local with no named vreg is a hint to try const
