# Empty 'case 0: break;' makes CW switch lower 1/2 as cmpwi1;beq;bge;cmpwi3 chain

- status: works
- tags: switch,cmpwi,RPUtlObject
- scope: RPUtlObject.cpp

symptom: switch(state){case 1;case 2} emitted cmpwi 2 first; orig is cmpwi 1/beq/bge then cmpwi 3 range check
cause: orig switch had a third (empty) case label, probably case 0
fix: add 'case 0: break;' before case 1 (fn_801BFBA8 -> 100%); also reload node->next (not cached next) for next->previous store
