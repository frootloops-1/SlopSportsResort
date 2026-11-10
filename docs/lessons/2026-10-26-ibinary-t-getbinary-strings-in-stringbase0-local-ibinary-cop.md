# IBinary<T>::GetBinary strings in @stringBase0: local IBinary copy with GetBinary declared-only + explicit specialization at end

- status: works
- tags: egg,ibinary,string-pool,eggLightTextureManager

symptom: specialization of IBinary<X>::GetBinary with #line 105 emits weak @STRING@ strings (228B, separate lis/li) instead of base+0xb0/0xbd off @stringBase0
cause: shared eggIBinary.h defines GetBinary inline in-class, so strings go weak; also specialization must be declared before first use
fix: copy eggLightManager.cpp pattern: define EGG_CORE_IBINARY_H and paste a local IBinary with 'void GetBinary(void*) const;' declared only, forward-declare the specialization, define it at file end with #line 105 "eggIBinary.h" EGG_ASSERT(bin); GetBinarySize must be placed after it; rename lbl_ pool to @stringBase0 size = string bytes; vtable/spExtension symbol sizes exclude pad; DOL 0 diff with weak surplus
