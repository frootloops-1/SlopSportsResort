# MWCC backend turns a rebuilt bool's li 1 into mr from an earlier li 1 constant

- status: works
- tags: colouring,bool,mwcc_dbg,backend,value-numbering
- source: gol441c2-1102-opus

symptom: bool rebuilt as codegen temp (RebuildLogicalExpressions) still loses r3 when a dominating block has li rK,1 (e.g. slw constant)
cause: backend optimizer replaces li rB,1 with mr rB,rK for codegen-temp bools (not for IRO @var bools); rK is a higher vreg, colours first and interferes with rB
fix: diagnostic only: compare backend-00 vs backend-02 in mwcc_dbg; an @var bool (ECONDASS shape) keeps its own li 1
