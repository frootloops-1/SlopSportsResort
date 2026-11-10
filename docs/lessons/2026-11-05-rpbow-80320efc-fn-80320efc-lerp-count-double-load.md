# RPBow_80320EFC fn_80320EFC lerp count double load

- status: open
- tags: RPBow_80320EFC,fn_80320EFC,lerp,LICM,const-array

symptom: loop preheader loads const int[1] table count twice (one for hoisted n-1, one kept in r31 for later CSE); target loads once
cause: unknown; copy propagation of a const-array load into the inline param
fix: partial: Tbl2 lerps reading lbl_804C5DCC inline (no n2 local) fixed GPR colouring 98.2->98.6 but size +8. Dead: enum/long/short/const/volatile n locals, helper param last=n-1, int n local inside helper
