# fn_801FF0CC: (col+3)%3 / (row+5)%5 assign back to vars before the combine closes scheduling

- status: works
- tags: scheduling,mod,modulo
- scope: RPSports_801fdbc0
- source: worker

symptom: 96.8%: add/mulli order and mulli dest reg differ in x%3 + y%5*3 wrap
cause: expression form
fix: col = (col + 3) % 3; row = (row + 5) % 5; *(s32*)(self+0x90) = col + row * 3; (single-expression, rr/cc new locals, inline wrap helper and swapped operand orders all stayed 96.8)
