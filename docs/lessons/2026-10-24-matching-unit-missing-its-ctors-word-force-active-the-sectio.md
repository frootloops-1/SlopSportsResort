# Matching unit missing its .ctors word: force_active the section-pointer static

- status: works
- tags: ctors,force_active,dol,flip
- scope: RPBow
- source: claude

symptom: unit 100% code but DOL 4 bytes short; the unit's .ctors entry (fn_80347574 pointer) missing
cause: mwld drops an unreferenced .ctors word
fix: wrap '__declspec(section ".ctors") static void (*x)(void)=fn;' in #pragma force_active on/reset (RPBowPlayerLaneNpc flipped to Matching 2026-10-24)
