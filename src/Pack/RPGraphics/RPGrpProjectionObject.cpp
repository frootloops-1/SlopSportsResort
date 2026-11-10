#include <Pack/RPGraphics.h>

#include <nw4r/g3d.h>

RPGrpProjectionObject::RPGrpProjectionObject(u8 viewNo) : mViewNo(viewNo) {
    mCamera.Identity();
    mCamera.SetCameraType(RPGrpCamera::ECameraType_Anm);
}

void RPGrpProjectionObject::Calc(nw4r::g3d::Camera cam) {
    mCamera.CalcMatrix();
    mCamera.SaveCameraMatrix();

    cam.SetCameraMtxDirectly(mCamera.GetSavedCameraMatrix());
    mScreen.CopyToG3D(cam);
}

// Matching helper (inferred, not from symbols): passing the scene through a
// by-value inline parameter makes the first call's copy take the lowest stack
// slot, and the reference parameters keep the argument loads after the copy.
static inline void LoadCam(RPGrpCamera& rCamera,
                           const nw4r::g3d::ResAnmScn scn, const u8& rViewNo,
                           const f32& rFrame) {
    rCamera.LoadScnCameraMatrix(scn, rViewNo, rFrame);
}

void RPGrpProjectionObject::LoadScnCamera(RPGrpHandle handle, const char* pName,
                                          f32 frame) {
    nw4r::g3d::ResFile file = RPGrpModelResManager::GetCurrent()
        ->GetData<RPGrpModelResManager::Type_ResFile>(handle);
    nw4r::g3d::ResAnmScn scn = file.GetResAnmScn(pName);

    LoadCam(mCamera, scn, mViewNo, frame);
    mScreen.LoadScnCamera(scn, mViewNo, frame);
}
