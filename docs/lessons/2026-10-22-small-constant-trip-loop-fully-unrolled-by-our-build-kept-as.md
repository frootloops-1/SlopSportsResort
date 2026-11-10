# Small constant-trip loop fully unrolled by our build, kept as ctr loop in target

- status: open
- tags: unroll,loop
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-rpbox-802cb9cc-1022

symptom: 3-trip loop with if/else body fully unrolled; opt_unroll_loops off alone did nothing
cause: unknown; an inner loop at decision time blocks full unroll
fix: opt_unroll_loops off plus a 1-trip inner loop gave 97.4 (fakematch); the natural source is still unknown
