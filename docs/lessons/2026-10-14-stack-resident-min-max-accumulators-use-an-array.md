# Stack-resident min/max accumulators: use an array

- status: works
- tags: stack,float,array
- scope: RPTns_80224cf8
- source: sonnet worker 2026-10-14

symptom: orig keeps accumulators in stack memory, ours in FPRs
cause: scalars get registers
fix: f32 d[2]; later-declared arrays get lower stack addresses; oversized frame = padded local struct
