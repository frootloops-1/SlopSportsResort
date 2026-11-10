# resort: 0x80240C78 is popDpdCtrlStackAll, 0x80240E18 is stopMotorAll

- status: works
- tags: resort,rp

symptom: stopMotorAll scored 100 against the wrong address
cause: earlier misnaming
fix: renamed; stopMotorAll now 81 against its real body (open)
