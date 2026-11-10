# Global-field local after loops gets wrong reg: load via static inline getter

- status: works
- tags: regalloc,inline,getter,coalesce
- scope: RPTns_80246eec,RPTns_80247450
- source: opus worker + claude 2026-10-14

symptom: msg = holder->msg in r27 instead of coalesced r30 (99.8); decl order/const/scope fail
cause: inline getter's return temp coalesces with earlier short-lived values
fix: static inline RPSysMessage* GetMsg(){ return holder->msg; } msg = GetMsg(); (fn_8024720C, fn_80247740)
