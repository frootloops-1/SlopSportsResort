# RPSportsKokeshiLyt frame getters and broad inline boundaries do not preserve allocation

- status: fails
- tags: RPSportsKokeshiLyt,regalloc,inline,frame
- scope: Pack/RPSports/RPSportsCommon/RPSportsKokeshiLyt

symptom: EFCC frame r26 vs target r29; count r23 vs r28; replay r25 vs r22.
cause: Getter around branchless ternary leaves frame named; moving the entire body changes stack slots and all local identities. Passing only frame into a state helper helps, but its row and loop indices must remain caller locals.
fix: Do not repeat: ternary/if-return frame getter, const frame or dead comma are flat; s16 adds extsh; duplicate cached-mode expressions retain a new live mode or move computation; entire-update helper falls to 77.8. State helper with local IVs 99.1; references to caller row/i recover 99.6. Named scoreOffset in loop colours too late; declare it before replay.
