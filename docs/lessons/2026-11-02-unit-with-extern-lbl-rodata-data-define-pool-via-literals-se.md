# Unit with extern lbl_ rodata/data: define pool via literals, seed order with dead static placeholder

- status: works
- tags: data,sdata2,rodata,ctors,pool
- scope: RPSports_801fba3c
- source: flip_gate

symptom: RPSports_801fba3c had .rodata/.data/.sdata/.sbss/.ctors absent and .sdata2 50%
cause: strings read as lbl_803889A0+off, data/sbss/sdata externs; pool order of 4 strings and 0.0f,double,1.0f,-1.0f came from stripped code; static non-inline fn is generated (reverse codegen order) and dead-stripped from DOL, unused static INLINE fns pool nothing; if(0)/dead locals do not pool strings but do pool floats
fix: replace base+off with literals, file-scope const char*[4] with medals first, f32 lbl_804BDD00[2], s32 lbl_804BF750[2], named extern const f32 1.0/-1.0 defined at file end, force_active __declspec(section .ctors) ptr, static SpPoolSeed(l,f32*,double*) after the last-binary function; flip_gate FLIP-OK
