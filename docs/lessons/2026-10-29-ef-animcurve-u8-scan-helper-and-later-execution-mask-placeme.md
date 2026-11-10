# ef_animcurve U8 scan helper and later execution mask placement are flat

- status: fails
- tags: ef_animcurve,U8,register-allocation,coalescing
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: After successful scan/execution phase split, U8 98.52521 with 494 normalized changed lines.
cause: An inline scan canonicalizes to original allocation; delaying the new mask copy further does not change final scores or normalized diff.
fix: Separate baseline inline FindEnabledMask trial identical 98.44958/524 lines; after retained split, move mask copy after hiFrame declaration identical 98.52521/494 lines. Both reverted; only original pool-order marker retained. Two no-gain tries reached.
