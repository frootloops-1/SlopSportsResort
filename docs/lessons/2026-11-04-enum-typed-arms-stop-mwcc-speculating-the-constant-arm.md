# Enum-typed ?: arms stop MWCC speculating the constant arm

- status: works
- tags: ternary,speculation,enum,register,mwcc
- scope: RPSportsCommon/RPSports_80211b60
- source: claude/sp80211-1104 82ddd20e8

symptom: c ? 2 : kind lowers to li rX,2; bne; mr rX,rY; retail has kind already in rX then beq; li rX,2
cause: MWCC front end speculates a leaf int-constant arm of ?: before backend-00; all non-leaf spellings of 2 get folded back to constants. Enum-typed arms build a real branch
fix: Type the variable (or arms) as an enum, e.g. enum SpMailKind {0,1,2} and c ? SP_MAIL_KIND_2 : kind. fn_802131C8 99.7->100
