# Member inline getSpeakerFlag fixes startSystemSeWithRemote reg swap

- status: works
- tags: regalloc,inline

symptom: flag/id registers swapped in startSystemSeWithRemote(name, getSpeakerFlag(player))
cause: argument evaluation/scheduling differs with locals
fix: route the flag through a member inline u32 getSpeakerFlag() const (fn_801DFBF0)
