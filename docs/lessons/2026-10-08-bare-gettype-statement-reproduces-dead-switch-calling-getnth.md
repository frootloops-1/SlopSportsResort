# Bare getType(); statement reproduces dead switch calling getNthController

- status: works
- tags: dead-code,inline

symptom: orig has switch whose only effect is getNthController, result unused
cause: inlined getType() with unused result
fix: write a bare self->getType(); (fn_801E1880/1D14)
