# Enum-typed ternary arms are not if-converted

- status: works
- tags: ternary,if-conversion,enum
- scope: Pack/RPSports/RPBoxScene/RPBox_802cb9cc
- source: claude-rpbox-802cb9cc-1022

symptom: k ? 0 : 12 became neg/or/srawi/andc; the target has li/beq/li
cause: MWCC if-converts int-constant ternaries that have a 0 arm
fix: use enum constants in the arms (or int n = 2; if (c) n = 1;)
