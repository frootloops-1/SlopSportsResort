# Objdiff 100% but DOL FAILED: check emission order (reverse source order)

- status: works
- tags: inline-deferred,dol,order
- source: RPBsb_8027383c

symptom: fn at start of TU emitted last; bl targets shift 0x100, main.dol FAILED though all fns 100%
cause: -inline deferred emits small fns after larger; dont_inline pragma does not help
fix: write definitions in descending address order, then ninja must print main.dol: OK before flipping Matching
