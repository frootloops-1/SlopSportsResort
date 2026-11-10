# virtual with float arg must be declared with it

- status: works
- tags: virtual,float,rpbsb
- source: RPBsb_8026eccc 2026-10-16

symptom: missing lfs f1 before virtual call
cause: prototype lacked f32 param
fix: declare vf30(f32) and pass the value
