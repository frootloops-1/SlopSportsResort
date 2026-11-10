# self-recursive fn inlined 8 deep by MWCC

- status: works
- tags: recursion,inline,rpbsb
- source: RPBsb_8027d3ec 2026-10-16

symptom: huge unrolled chain walk
cause: -inline auto inlines self-recursion 8 levels
fix: write the plain recursive function, no inline keyword; place it right after its first caller in source order
