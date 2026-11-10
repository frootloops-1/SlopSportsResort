# Unused named param is build error 10182

- status: works
- tags: param,10182
- scope: RPSportsCommon_unsplit

symptom: build error on pass-through stub
cause: flag set errors on unused named params
fix: leave the parameter unnamed
