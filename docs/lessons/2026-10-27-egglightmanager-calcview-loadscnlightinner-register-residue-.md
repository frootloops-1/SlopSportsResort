# eggLightManager CalcView/LoadScnLightInner register residue: 3 more reshapes each no gain

- status: fails
- tags: register,calcview,loadscnlightinner,egg
- scope: egg/gfxe/eggLightManager

symptom: CalcView r23/r25 swap (pObjSet vs u16 index); LoadScnLightInner clear-loop r3/r4/r5 offset/pp/obj
cause: vreg ordering; unknown source shape
fix: tried: &pObjSet[i] induction 99.4, pObjSet before m_currentView store 98.9, &m_pObjSet[GetCurrentView()*8] same; subscript-ternary inline identical, u32 i 98.7 (pointer induction), static inline helper 96.4. Parked
