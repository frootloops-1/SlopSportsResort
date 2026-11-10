# resort bowling: undefined lbl_806DExxx at link for a hand-written vtable

- status: works
- tags: resort,bowling,data,flip

symptom: undefined symbol for vtable array on flip
cause: array still carries the Wii Sports lbl_803CAxxx label
fix: name the array after its Resort .data address, match slots to the unit .s (RPBowActiveBall, RPBow_8033FD0C)
