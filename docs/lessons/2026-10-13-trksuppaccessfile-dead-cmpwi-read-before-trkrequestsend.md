# TRKSuppAccessFile dead cmpwi read before TRKRequestSend

- status: works
- tags: trk,metrotrk,support,ternary
- scope: MetroTRK

symptom: orig computes !(read && fh==0) before loading TRKRequestSend args with an extra unused cmpwi read
cause: msg-type arg written as identical-arm ternary read ? 5 : 5
fix: TRKRequestSend(buffer, &id, read ? 5 : 5, 3, b == 0): 91.9 -> 98.9. Remaining: replyBuffer r28 vs orig r22 (params shifted); 800 random decl orders, inner-block scope, register kw, for-loop form, u16 replyLength, dead inits: no fix
