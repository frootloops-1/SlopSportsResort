# Bare cmplwi with no branch: dead float local self-reassigned under if

- status: works
- tags: dead-code,compare
- scope: RPGol_802b7670
- source: fn_802B7770

symptom: cmplwi with no following branch
cause: dead store to float local survives compare
fix: float d = 0.2f; if (kind == 5) d = 0.2f; (dead ints/empty ifs fold away)
