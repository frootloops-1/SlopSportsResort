# resort: drop unused object definitions instead of hiding their sinit

- status: works
- tags: resort,bowling,data,flip

symptom: duplicate symbol at link from a POD hack
cause: unit defined an object it does not own to dodge __sinit
fix: delete the definition; an extern declaration emits no sinit (RPBowManagerContext)
