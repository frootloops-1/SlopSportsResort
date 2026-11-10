# Screen view->screen->normalized = GetViewToScreen + inline ConvertToNormalCC; (s16)-hw per ctor arg

- status: works
- tags: egg,screen,float
- scope: RPTns_802318a4
- source: claude/rptns-2

symptom: fn_80231B58 (LU canvas: x-w/2, -(y-h/2), then /(size/2)); screen pos (f32)(s16)GetPosition().x + 0.5f*GetWidth()
cause: EGG::Frustum inline ConvertToNormalCC and GetWidth()=u16(size.x)
fix: scr->GetViewToScreen(out, view); scr->ConvertToNormalCC(out->x,out->y,&out->x,&out->y); for screen pos use s16 px,py locals and out->x = pos.x + ((f32)px + hw); write (s16)-hw inside each new RPGrpScreen(...) argument, not hoisted into a local
