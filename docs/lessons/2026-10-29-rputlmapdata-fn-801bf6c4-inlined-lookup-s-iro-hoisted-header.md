# RPUtlMapData fn_801BF6C4: inlined lookup's IRO-hoisted header/count coloured before caller count; pass named caller locals into a helper

- status: works
- tags: regalloc,inline,mapdata,r12,iro-hoist,named-locals
- scope: src/Pack/RPUtility/RPUtlMapData.cpp

symptom: count r30 / lookup header r31 / entryCount r12; target count r12, entryCount r31, header r30 (14 lines)
cause: inlined fn_801BF564's header (@3997, r63) and loop bound entryCount (@3977, r67) are IRO loop-bound/CSE temps numbered above every named local, so they are coloured before the caller's named count (r40). Target needs count coloured between the lookup's inline vars (r69-r74 = r6-r11) and entryCount, which no named-local or getter spelling reaches (getter expansions come before the lookup, cast/type/LICM variants are not hoisted)
fix: declare u16 count; u16 entryCount; MapHeader* pEntryHeader; at function top (that order), assign pEntryHeader=pMap->header; entryCount=pEntryHeader->entryCount; per iteration and call static inline findEntry(pMap, pEntryHeader, entryCount, i); use pEntryHeader->paths too (else CSE replaces pEntryHeader with an @ temp, H1: wrong order). 4/4. fn_801BF564 itself through the helper regresses to 96.6, hand-inlined loop 99.2; marked MATCH-PENDING (R17)
