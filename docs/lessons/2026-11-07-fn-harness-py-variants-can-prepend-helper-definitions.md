# fn_harness.py variants can prepend helper definitions

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBsbScene/RPBsb_8024e9a4

symptom: fn_harness.py variants can prepend helper definitions
cause: fn_harness.py variants can prepend helper definitions
fix: start variant with } to close extern C, reopen after
