# ef_animcurve F32 cached flags and frame helper body expansion regress

- status: fails
- tags: ef_animcurve,F32,register-allocation,inline
- scope: nw4r/ef/ef_animcurve
- source: docs/tasks/nw4r_ef.md

symptom: F32 95.615616; helper flags v121 r27 vs target r22, inline n v124 r28 already correct.
cause: Caching flags across helper changes required reload shape; expanding entire helper changes n and flags identities together.
fix: Early caller flags local + delete later load: 94.89089/839 normalized changed lines. Expand CalcCurveFrameF body: 95.45045/808. Reverted after two no-gain tries. Untried: F32-only out-ref flags boundary preserving both loads and inline n; invented boundary needs R17.
