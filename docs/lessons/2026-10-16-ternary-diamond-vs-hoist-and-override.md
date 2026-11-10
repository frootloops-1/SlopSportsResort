# ternary diamond vs hoist-and-override

- status: works
- tags: ternary,branch-shape,rpbsb
- source: RPBsb_8026eccc 2026-10-16

symptom: orig bne; lwz A; b; lwz B diamond but ours loads B then overrides
cause: plain global-load arms get hoisted
fix: arms with arithmetic on a field (G0 - self->cnt) give the diamond; local cnt + ternary lim gives the hoist shape
