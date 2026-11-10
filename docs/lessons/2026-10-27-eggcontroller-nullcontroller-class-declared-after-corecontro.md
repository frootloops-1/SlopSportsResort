# eggController: NullController class declared after CoreControllerMgr fixes .data vtable order

- status: works
- tags: eggController,vtable,data-order
- scope: egg/core/eggController
- source: claude/controller-1027

symptom: Flip test: __vt__NullController emitted after T__Disposer vtable, orig has it between ControllerRumbleUnit and CoreControllerMgr (1957 DOL bytes)
cause: Vtable order follows reverse class-declaration order; NullController was declared before CoreControllerMgr
fix: Move class NullController below CoreControllerMgr in include/egg/core/eggController.h
