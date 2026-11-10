# Struct assign of s16[4] emits lhz but orig lha; copy members individually (RPGolMapObjBase)

- status: works
- tags: golf,s16,lha,RPGolMapObjBase
- scope: RPGolMapObjBase
- source: sonnet

symptom: lhz vs lha
cause: struct copy uses unsigned halfword
fix: copy s16 members one by one into locals then store; compute dst=e->items+idx right after e
