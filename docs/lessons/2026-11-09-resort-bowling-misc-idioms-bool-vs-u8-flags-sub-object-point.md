# resort: Bowling misc idioms (bool vs u8 flags, sub-object pointer, unnamed unused params)

- status: works
- tags: resort,bowling,idioms
- scope: resort
- source: bowling-lanes

symptom: cntlzw+srwi 5 vs extrwi; addi rX,this,0x10 then addis; -w unused errors
cause: bool fields give srwi 5; base folding; -w unused is an error
fix: declare flags bool; local Inner* in=&self->in for sub-object access; leave unused params unnamed. Loop shape int i=0; if(n>0) for(;i<n;i++) for guard + bottom test
