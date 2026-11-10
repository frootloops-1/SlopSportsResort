# Template instances (createShape/deleteShape) emit in reverse of first use; thunk-order dead ends

- status: fails
- tags: template,emission-order,thunk,egg
- scope: egg
- source: claude

symptom: eggModelBoundingInfo: createShape<Sphere>/deleteShape<Sphere> before <AABB>, orig after; eggDrawPathBase: @112@scnProcDraw thunk before @112@__dt thunk, orig reversed
cause: mwcc emits weak template instances in reverse of first reference
fix: unsolved. Tried: reordering if-blocks, struct definition order, explicit instantiation, unused inline member, dtor declared first/last/out-of-line, definition order of scnProcDraw. Making Sphere's first use precede AABB's flips the createShape order but changes call order
