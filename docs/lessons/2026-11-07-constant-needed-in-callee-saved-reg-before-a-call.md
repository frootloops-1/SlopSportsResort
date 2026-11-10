# Constant needed in callee-saved reg before a call

- status: works
- tags: RPBox,R17
- scope: Pack/RPSports/RPBoxScene/RPBox_802de63c

symptom: Constant needed in callee-saved reg before a call
cause: Constant needed in callee-saved reg before a call
fix: register local + asm li colours low; whole-asm needed (fn_802E071C)
