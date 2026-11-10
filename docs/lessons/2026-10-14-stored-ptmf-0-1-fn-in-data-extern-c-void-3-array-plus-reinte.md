# Stored ptmf {0,-1,fn} in .data: extern C void*[3] array plus reinterpret_cast to PMF

- status: works
- tags: ptmf,data,callback
- source: RPBsb_80259bbc

symptom: 3-word .data record {0,-1,fn} copied via lwzu/lwz/lwz
cause: pointer-to-member constant
fix: extern "C" void* lbl[3]={0,(void*)-1,fn}; cond = *reinterpret_cast<Cls::PMF*>(lbl); call (self->*self->cond)(arg)
