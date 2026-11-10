# EGG::Vector3f by-value ops never inline (dtor); use a POD vector with explicit operator=

- status: works
- tags: vector,inline,egg
- scope: mwcc
- source: RPTns_802390b0

symptom: weak __pl__/__ml__/__dt__Q23EGG8Vector3f copies and __construct_array in big fns
cause: temporaries of a class with a destructor block inlining
fix: local struct {f32 x,y,z; memberwise operator=}: assignment -> lfs/stfs, implicit copy-ctor -> lwz/stw; write by-value math per component; compound x *= s via inline param gives var-first fmuls
