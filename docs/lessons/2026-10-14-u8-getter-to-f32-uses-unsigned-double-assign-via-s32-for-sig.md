# u8 getter to f32 uses unsigned double; assign via s32 for signed xoris; reuse local ptr for held-register

- status: works
- tags: int-to-float,regalloc
- source: RPBsb_8027b2d4

symptom: 92.7% unsigned 0x43300000/0 double; 84% reloaded anm pointers
cause: u8 conversion constant; repeated self->field->x reloads
fix: s32 fps = getFrameRate(); and BsbAnm* a reused per object (a=self->p0; ...)
