# Ctor float loads hoisted above int stores: take struct param as const T& not T*

- status: works
- tags: ctor,scheduling,reference,float
- source: RPBsb_80275104

symptom: 89.7%: loads of pos x,y,z,zero interleaved with stores; orig loads zero,x,y,z first
cause: pointer param keeps loads next to their stores; no local ordering reproduces it
fix: extern C ctor(self, const BsbVec& pos) with plain field-order stores -> 100%; same body with pointer 83%. Param type does not change extern C symbol. Also: out-param Vec fn declared void(Vec* out, void*) not by-value; float->int result assigned before following if
