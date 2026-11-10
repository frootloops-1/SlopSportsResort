# Find the pool-order culprit by @NNN number, then put the dead literal there

- status: works
- tags: sdata2,literal-order,link-flip,dead-expression,objdump
- scope: Pack/RPSports/RPSportsCommon/RPSysNunchukCheckScene
- source: claude/nm-link-1 2026-10-15

symptom: RPSysNunchukCheckScene flip: 10 DOL bytes, .sdata2 had the 0x4330 double before 1.0f (orig: 1.0f first). Dead '1.0f;' at the top of Configure or fn_801E3A5C changed nothing.
cause: The double was created by Calculate (last in source). Anonymous pool labels are numbered in creation order, so the lowest @NNN shows which function created it first, which is not necessarily the first function in the source or in .text.
fix: objdump -dr the built .o and list SDA21 relocs per function; put the dead literal statement at the top of the function that references the lowest-numbered constant (here Calculate). 21/21 exact, DOL SHA-1 OK.
