# Avoid eggController.h for one button read

- status: works
- tags: header,weak,text-size
- source: RPTns_80216810

symptom: 600 extra bytes of weak static inlines in .text
cause: Header static inline functions emitted
fix: Declare getNthController/sInstance as raw externs plus a local view struct
