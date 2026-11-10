# Vptr after data fields: plain data base struct then virtual-declaring struct with dummy virtuals

- status: works
- tags: vtable,view,virtual
- source: RPBsb_8026e8d4

symptom: vptr at +0x68/+0x44 not at 0, virtual slot at high offset
cause: view struct needs vptr in the middle
fix: struct Data{u8 pad[0x68]}; struct View:Data{ virtual dummies for slots (off-8)/4; real virtual }; unused f32 left in f1 before a virtual call is a passthrough arg
