# fn_802CE89C: late-load forms flat; C-mode color control still fails full gate

- status: fails
- tags: RPBox,fn_802CE89C,register-allocation,GXColor,compiler-version
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc fn_802CE89C
- source: docs/tasks/RPBox_802cb9cc.md; /private/tmp/ogws-boxce89c-1102/build/evidence/boxce89c

symptom: 28/29 exact; fn_802CE89C 99.9142 with manager r5/r6 swap and separate white-color stack slots.
cause: Manager backend value r75 precedes table chain r76/r77; ordinary const/local/getter/late-result forms preserve allocation. C++ aggregate temporaries occupy separate slots.
fix: No closure. Six-version sweeps plus table/manager/scalar/reference/getter/late-result variants are flat; setter variants regress. C-mode compound literal reaches 99.922 but source-link gate has 7 differing DOL bytes, so reverted. Retain only void* return/storage correction confirmed by matched callee, byte-identical in text/data/relocations.
