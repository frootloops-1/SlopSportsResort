# resort optimize_for_size inliner: nested calls only expand inside expression-bodied inlines

- status: works
- tags: resort,mwcc,inline,nw4r,rpgrpmodel

symptom: nw4r if-form ResNode::GetID/GetMtxID, ResMat/ResNode::GetName leave IsValid/ptr/ref as weak calls
cause: Resort's nw4r used ternary / ofs_to_ptr<char>(ref().name) forms
fix: Use expression-bodied forms (local helpers in RPGrpModelImplement.cpp for now; nw4r header change pending). Dead end: GetData<T>(handle) is never inlined in Resort and every spelling tried inlines in ours
