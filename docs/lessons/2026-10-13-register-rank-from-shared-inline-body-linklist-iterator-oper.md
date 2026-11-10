# Register rank from SHARED inline body: LinkList::Iterator::operator* needs local ptr + assert statement

- status: works
- tags: linklist,iterator,inline-budget,void0,probe
- scope: Pack/RPKernel/RPSysLayout

symptom: allocStringBuffer pane param ranked wrong at every inline level; 368 source variants failed
cause: include/nw4r/ut/ut_LinkList.h operator* is a single expression; shipped NW4R stores pointer in local and asserts; (void)0 statements count toward inline budget
fix: source-local explicit specialization PaneList::Iterator::operator* (local ptr + one (void)0) + pTextBox declared before pString; proper fix: change ut_LinkList.h (re-verify all LinkList users). Technique: stand-alone mock probe .cpp with same mwcc flags reproduces register signature in ~1s
