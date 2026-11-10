# ef_animcurve: fork ef_animcurve.cpp (only U8) compared; out-param getAnimHeaders, fork interp/search shapes give no gain

- status: fails
- tags: ef_animcurve,U8,Texture,Child,getAnimHeaders,fork
- source: xfer-1028 fork file

symptom: Texture 99.53, Child 97.88, U8 98.19 unchanged
cause: A getAnimHeaders-style out-parameter inline (5 table pointers as separate variables) compiles to identical code in Texture and Child, so it does not keep pHeader a separate node. Fork Hermite association (a+(b-a)*(3-2p)*p*p, grouped p2/p1 polynomial) is normalised by MWCC (same 298 wrong lines). searchKey u16 mdFrame / mid=(lo+hi)/2 / std fabs: no change or worse. The fork's whole U8 body scores 91.9 in our build (_savegpr_17, params r29-r31, further from target r16/r23-r26 than ours)
fix: none; do not retry. U8 target colours mask (r26) after pRangeTbl r30/pRandomTbl r29/loop r28, ours colours mask second (r30): weight of mask vs table pointers in the loop is the residue
