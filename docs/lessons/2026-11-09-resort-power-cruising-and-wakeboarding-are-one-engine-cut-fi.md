# resort: Power Cruising and Wakeboarding are one engine; cut files without singleton names

- status: works
- tags: resort,splits,jsk,wkb,sport-map
- scope: resort
- source: jsk-wkb

symptom: no fn_80370BD8 singleton strings or class names in 0x8057E310-0x805B5FD8
cause: shared scene vtable 0x806E5360 built by two cases of fn_8022E438; files mix jsk_/wkb_ resources
fix: cut by __sinit ends, MI thunks after __sinit (go to preceding file), duplicate .sdata2 0/1.0, layout shape API->virtuals->ctor->dtor->8-byte tails; attribute layouts by 65xxx_jsk_/66xxx_wkb_ names, the rest by call graph. 0x805B5FD8-0x805B65D8 is Frisbee Dog
