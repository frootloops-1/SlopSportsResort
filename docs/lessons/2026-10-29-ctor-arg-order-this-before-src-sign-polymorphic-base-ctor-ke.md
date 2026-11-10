# Ctor arg order: this before src/sign = polymorphic base ctor keeps this in a vreg

- status: works
- tags: scheduler,ctor,this,arg-order,rpbox
- scope: mwcc
- source: claude/y-box8360-1029

symptom: inline derived ctor calling out-of-line base ctor: orig addi r3,r1,X; mr r4; mr r8 and lis temps avoid r3; ours mr r4; mr r8; addi r3 (pre-RA scheduler moves mr first)
cause: with a polymorphic base class (virtual dtor) the front end keeps the derived ctor's this in a vreg (addi rT,r1,X; mr r3,rT; member accesses via rT), so the scheduler keeps this first; an extern C init call with this substituted directly does not
fix: real fix: base class with virtual dtor and out-of-line ctor (needs symbol renames). In-unit emulation: BoxStat* self = this; and route the call and every member access through self (copying this only for the call does nothing)
