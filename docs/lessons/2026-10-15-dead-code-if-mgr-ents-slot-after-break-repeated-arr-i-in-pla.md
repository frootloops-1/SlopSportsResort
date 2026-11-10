# Dead code (if (!(&mgr->ents[slot])) {}) after break + repeated &arr[i] in place of local

- status: works
- tags: permuter,deadcode
- scope: Pack/RPSports

symptom: fn_801F5014 99.1%
cause: original repeated (&mgr->ents[slot])-> and had unreachable null-test
fix: replace ent-> with (&mgr->ents[slot])-> on 3 lines; insert unreachable if(!(&mgr->ents[slot])){} after case 1 break
