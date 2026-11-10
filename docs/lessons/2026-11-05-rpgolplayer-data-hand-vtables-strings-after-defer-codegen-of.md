# RPGolPlayer data: hand vtables/strings after defer_codegen off, hand .ctors, sdata2 literal order by first use

- status: works
- tags: rpgol,rpgolplayer
- scope: Pack/RPSports/RPGolScene/RPGolPlayer

symptom: .data 36.8/.ctors 0/.sbss 0/.sdata2 95
cause: vtable/strings/sinit missing; literal pool order = codegen first use
fix: hand arrays __vt__11GolSndActor etc behind #pragma defer_codegen off (RPGolFieldManager pattern); hand .ctors ptr to fn_802A21FC (real __sinit lands after fn_802A2208); dead 25.0f/1.0f locals in fn_8029E6D8; symbols @1304 size 4 + @1305; all R17
