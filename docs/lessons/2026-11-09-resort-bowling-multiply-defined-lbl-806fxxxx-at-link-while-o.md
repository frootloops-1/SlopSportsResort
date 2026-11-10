# resort bowling: multiply-defined lbl_806Fxxxx at link while objdiff is 100

- status: works
- tags: resort,bowling,data,flip

symptom: flip_gate link fails with duplicate sbss/bss labels
cause: unit defines .sbss/.bss objects its splits do not claim
fix: add the .sbss range to the unit split and fix symbol sizes (RPBow_80347D0C)
