# E464 closes unit: schedulable copies and preseeded float pool

- status: works
- tags: E464,inline-asm,pool,R17,Matching
- scope: Pack/RPSports/RPSportsCommon/RPSports_8020b340
- source: codex-e464-match; scratch/e464/matching-gate.json and relocated-proof.json

symptom: Main E464 at 94.6; Claude committed C++ snapshot reaches 96.3. Remaining reload/float scheduling and named e.a allocation differ.
cause: Fully serialized incoming argument copies do not interleave with compiler-generated saves. Assembler 60.0f/magic literals create pool entries before the later C878 seed helper.
fix: Marked whole-body fallback leaves its first two GPR copies schedulable, keeps compiler frame/saves, then serializes the rest. Move unused seedLineConstants before E464 and seed all 15 retail floats. E464 independently matches 296 bytes / 74 instructions / 3 relocations. Unit 39/39 and all sections 100; source-unit Matching link DOL 0 bytes, only known collisions. No E464 opwords. Original C++ recovery pending; Claude checkout preserved.
