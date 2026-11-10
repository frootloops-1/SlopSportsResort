# RPBsb_80268f8c closed: defer_codegen flush plus extern declarations places vtables after PMF records

- status: works
- tags: RPBsb,vtable,data-order,defer_codegen,pmf,flip
- scope: Pack/RPSports/RPBsbScene/RPBsb_80268f8c
- source: codex-bsb68-data-1101, base 93b6fb8b7

symptom: 35/35 code exact but .data 32.8125%; two extern vtable arrays were undefined in source. Earlier weak array definitions preserved addressing but preceded PMF records.
cause: Deferred codegen emits explicit data while parsing, then PMF records during deferred function compilation. Changing only definition placement without flushing cannot reproduce the target data order.
fix: Append #pragma defer_codegen off, then plain extern declarations for both tables, then their 33-word and 10-word definitions. The extern declaration triggers the flush before the definitions are visible: functions retain named extern references and PMF records precede the arrays. Every section and 83/83 scored symbols now100, no function-body/headers/maps/splits changes. FLIP-OK, DOL0 and only three known collisions; Matching. Existing R17 constructor marker row14 remains; no new marker. Evidence /private/tmp/ogws-bsb68-data-1101/build/evidence/bsb68-data/.
