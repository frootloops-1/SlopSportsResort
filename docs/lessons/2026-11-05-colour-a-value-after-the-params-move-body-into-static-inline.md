# Colour a value after the params: move body into static inline, keep early values as caller locals by reference

- status: works
- tags: rpgol,rpgolplayer,regalloc
- scope: Pack/RPSports/RPGolScene/RPGolPlayer

symptom: fn_8029FC08 col coloured before params (retail r27 after mask/ok/out/self)
cause: inline locals colour after caller params; order: inline getter results > named locals > params > inline locals > shared global temps; inline locals stacked in reverse decl order
fix: static inline Body(self,out,u32& mask,bool& ok,f32& ang); wrapper under #pragma auto_inline off/reset (dont_inline also blocks inner inline)
