# Bow markers 37/38/45/46/54/57/58 retired via real owner types

- status: works
- tags: markers,rpbow,retire,accessor
- scope: RPBowScene
- source: claude/mr-c-1101

symptom: 7 invented holders/accessors/helpers in RPBowScene units
cause: real owners exist: Bowling::PinStatus at ctx+0xC20 (getter called INSIDE the loop condition; into a named local 99.8; direct mBits.Test 96.2), shared int GetAnmFrame() (s32 return gives 99.8), RPSysLytAnmObj::playFromEnd() member (same body as GolPlayEnd), PinPhysicsBody::SetRackPose() member inline
fix: commit fca238484; rows 44 (const at()/wrap() loses capacity CSE, 99.9) and 72 (GetSpheres getter 94.9, named locals 96.0) stay. Untested hint: RPBow_803536C4/80353214 frame=-u8 problem may close with GetAnmFrame()
