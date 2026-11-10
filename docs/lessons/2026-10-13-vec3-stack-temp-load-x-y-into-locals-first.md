# Vec3 stack temp: load x,y into locals first

- status: works
- tags: vec3,fpr,order
- scope: RPSportsCommon_unsplit

symptom: f1/f2 swapped (97.7 / 54.2%) when copying a Vec3 through a stack temp
cause: direct v.x = pv->x schedules loads differently
fix: f32 x = pv->x; f32 y = pv->y; then v.x = x; v.y = y; field stores from locals
