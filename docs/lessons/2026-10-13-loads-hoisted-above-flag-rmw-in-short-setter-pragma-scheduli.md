# Loads hoisted above flag RMW in short setter: #pragma scheduling off

- status: works
- tags: scheduling,pragma,hoist,setter
- scope: Pack/RPKernel

symptom: original keeps loads after stw flags; every source variant hoisted them
cause: MWCC scheduler
fix: #pragma scheduling off/reset around fn; 'f32 x,y; y=a.y; x=a.x;' gives y->f1 x->f0 (init at decl swaps)
