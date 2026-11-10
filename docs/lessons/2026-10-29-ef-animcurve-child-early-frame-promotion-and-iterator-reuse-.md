# ef_animcurve Child early frame promotion and iterator reuse do not close colouring

- status: fails
- tags: ef_animcurve,Child,register-allocation,coalescing
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: Child 97.88188, 696 normalized changed lines; pKeys coalesces to late pKey2 vreg38 r31, header to parameter r28.
cause: Early integer promotion changes global graph; removing final iterator name selects another coalesced base representative.
fix: Cache s32 nextFrame before pKeys assignment and use in comparisons: 96.52867, 868 changed lines. Walk pKeys directly in final loop: identical 97.88188, 696 lines. Both reverted after two no-gain tries.
