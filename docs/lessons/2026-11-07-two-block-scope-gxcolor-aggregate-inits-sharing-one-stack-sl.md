# Two block-scope GXColor aggregate inits sharing one stack slot in C++

- status: works
- tags: RPBox,GXColor,stack-slot,sdata2,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc

symptom: target shares sp+8 for two GXColor inits; C++ gives separate slots
cause: C++ aggregate init temporaries get distinct slots; C mode shares them but #pragma cplusplus off failed DOL gate earlier. C struct copy from non-const sdata2 static materialises the address. __declspec(section) rejected on function-local statics (33057)
fix: one function-scope GXColor, file-scope __declspec(section ".sdata2") static stand-ins at the anonymous-constant positions, symbolic asm lbz of the 4 bytes (sweep decl order) + C field stores; .sdata2 and DOL identical
