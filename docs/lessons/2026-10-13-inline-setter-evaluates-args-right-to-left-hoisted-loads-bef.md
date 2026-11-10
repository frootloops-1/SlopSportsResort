# Inline setter evaluates args right-to-left (hoisted loads before stores)

- status: works
- tags: inline,setter,order
- scope: RPSportsCommon_unsplit

symptom: loads hoisted before 3 stores
cause: original was an inline member called with args
fix: write as inline member in class body; needs dont_inline off
