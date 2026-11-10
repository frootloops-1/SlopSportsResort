# Small control-flow idioms: else-return dead b, cases 0/1 break, bool | for cntlzw

- status: works
- tags: mwcc,switch,branches
- scope: RPTns_8023c74c
- source: claude/rptns-2

symptom: orig has 'b X; b ret' dead branch; 'cmpwi 2; beq; bge; b'; cntlzw/or. for state==0||state==1
cause: source shapes
fix: if(c){...}else{return;}; switch{case 0: case 1: break; case 2: ...}; inline bool f(){return (s==0)|(s==1);}
