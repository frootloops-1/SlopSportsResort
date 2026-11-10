# Camera-switch inline helper and dead bctrl block (RPGolCameraManager)

- status: works
- tags: RPGolCameraManager,inline,virtual

symptom: 6 callers share prev/vf18/vf14 + cur==next + fn_80294A08 + fn_8029B240/BCFC + state=0; fn_8028EF98 had unreachable bctrl block
cause: static inline changeCam(mgr,cam) reproduces r30/r31 alloc; set next=0;cur=0 inline before it and MWCC folds prev to 0 but keeps dead vf18 block
fix: static inline changeCam; no if(0) needed
