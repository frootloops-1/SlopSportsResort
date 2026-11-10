# PMF constants: let the compiler generate them

- status: works
- tags: ptmf,data,rpbsb
- source: RPBsb_8026eccc 2026-10-16

symptom: manual PMF record array gives 59% ctor
cause: virtual PMF records {0,vtbl_off,vptr_off} need compiler emission
fix: write &Cls::vfXX; .data matches; manual void*[] only for non-virtual {0,-1,fn}
