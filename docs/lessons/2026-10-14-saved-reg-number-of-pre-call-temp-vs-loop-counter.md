# Saved-reg number of pre-call temp vs loop counter

- status: works
- tags: regalloc
- scope: RPGol_802ae9ec
- source: fn_802AEAA0

symptom: temp gets lower saved reg than orig
cause: declaration order drives coloring
fix: declare temp before the for, assign inside (void* di; for(..){ di = ..; }); function-scope local assigned in branch also moves it
