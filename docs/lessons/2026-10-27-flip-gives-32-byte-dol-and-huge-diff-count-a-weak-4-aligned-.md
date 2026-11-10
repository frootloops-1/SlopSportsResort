# Flip gives +32 byte DOL and huge diff count: a weak 4-aligned object belongs at the end of the previous unit's .data

- status: works
- tags: flip,splits,data,alignment,weak,vtable,RPBox_80305e0c
- source: RPBox_80305e0c b17fc48e3

symptom: Unit 100% in objdiff but flipped DOL is 32 bytes larger with ~33k differing bytes (first diffs early in the image).
cause: Built .data is 8-aligned (MWCC aligns any .data object >=8 bytes to 8 for the section) but retail has a 4-aligned 0xC weak vtable at 4 mod 8 straight after the previous unit's jump table; the split started one 12-byte object too far right, shifting later data.
fix: Compare each built .o's section alignment/size to the dtk split .o. Define the weak vtable __declspec(weak) in the previous unit and move the splits.txt boundary to the next 8-aligned address (D1C -> D28); no symbols.txt change. Dead ends: shrinking vtable to [3], weak on both, aligned(4), struct members. The big diff count is mostly a downstream shift.
