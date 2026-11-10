# Dead cmplwi before real compare: self-copy plus ternary

- status: works
- tags: cmplwi,ternary,switch
- source: RPBsb_802734e0

symptom: orig has cmplwi 0x11 then cmplwi 0x10; bne; b
cause: switch on unsigned emits signed cmpwi; if/else chains differ
fix: f32 x=value; if(id==0x11){x=value;} value=(id==0x10)?x:k*x+c;
