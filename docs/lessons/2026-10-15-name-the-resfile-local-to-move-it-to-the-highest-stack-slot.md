# Name the ResFile local to move it to the highest stack slot

- status: works
- tags: stack,temporary,ResFile,GetResTex,GetData,slot-order,RPGraphics
- scope: MWCC stack-slot ordering
- source: RPGrpTexture

symptom: RPGrpModelResManager GetData<Type_ResX>(handle,pName) result: the ResFile temp and the result swap stack slots (target has the ResFile at the higher offset)
cause: MWCC gives stack locals and temps slots in creation order, from high to low. Temps created inside an inlined function (the ResFile inside GetData<ResX>) get allocated last, which puts them in the lowest slot
fix: Use 'nw4r::g3d::ResFile file = GetCurrent()->GetData<Type_ResFile>(handle); ResX x = file.GetResX(pName);' (an explicit temp 'ResFile(...).GetResX()' works too). This matched __ct__12RPGrpTextureFUsPCc
