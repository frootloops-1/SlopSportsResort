# tiny blr stub at a proposer cut trails the previous TU; check callers when a function drops after a split

- status: works
- tags: split,proposer,cut
- scope: RPSportsCommon_unsplit

symptom: propose_splits cut lands on a 4-byte blr function; one fn scored 99.1 before and 100 after moving the cut to its caller's start
cause: Empty virtual stubs belong to the previous class TU; callers that straddle the cut point at a wrong boundary
fix: Move the cut past the blr stub; when a ctor-shaped fn calls the function right at the cut, cut before the ctor (801EB388 not 801EB498)
