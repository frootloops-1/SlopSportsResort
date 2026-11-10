# Chained a=b=c=0.0f stores z,y,x; tiny vtable-only .data via extern C void* array works

- status: works
- tags: store-order,vtable
- source: RPBsb_8026e440

symptom: default ctor store order x,y,z vs orig z,y,x
cause: separate assignments store in source order
fix: posX = posY = posZ = 0.0f; manual extern C void* lbl[4]={0,0,fn,0} lands at .data 0 when TU has no jumptables
