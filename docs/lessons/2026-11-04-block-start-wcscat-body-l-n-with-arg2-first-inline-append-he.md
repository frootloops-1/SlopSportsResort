# Block-start wcscat(body, L"\n") with arg2 first = inline append helper taking (buf, s) params (right-to-left eval)

- status: works
- tags: arg-order,inline-param,dont_inline,rpsports,80211b60
- source: sp8020f-1104

symptom: four block-start calls had addi r4 (literal) before addi r3 (buffer); mid-block calls r3 first
cause: inline params are evaluated right-to-left into temps, so the literal is materialised first
fix: static inline SpAppend(buf, s) at those 4 sites; fn_802131C8 needs dont_inline off + auto_inline off, fn_80212160 auto_inline off (else it auto-inlines)
