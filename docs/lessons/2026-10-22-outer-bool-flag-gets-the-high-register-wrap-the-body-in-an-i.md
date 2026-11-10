# Outer bool flag gets the high register; wrap the body in an inline

- status: works
- tags: regalloc,bool,inline
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-rpbox-802cb9cc-1022

symptom: nested predicate inlines matched except the result flag was r7 vs r4
cause: the caller's flag is allocated after the inline's temporaries
fix: move the body into a static inline returning the flag; the function just returns it
