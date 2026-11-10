/* Search-only C descriptions. The compiler still uses the real C++ headers.
 * Names use the C++ adapter's namespace encoding. RigidDynamics.angularStep
 * describes a method's return/argument types, not the C++ object's ABI layout.
 */
typedef struct nw4r__math__VEC3 {
    float x, y, z;
} nw4r__math__VEC3;

typedef struct nw4r__math__QUAT {
    float x, y, z, w;
} nw4r__math__QUAT;

typedef struct nw4r__math__MTX34 {
    float _00, _01, _02, _03;
    float _10, _11, _12, _13;
    float _20, _21, _22, _23;
} nw4r__math__MTX34;

typedef struct RigidOrientation {
    unsigned char unknown_0x00[0xA4];
    nw4r__math__QUAT orientation;
} RigidOrientation;

typedef struct RigidDynamics {
    void (*angularStep)(nw4r__math__QUAT*);
} RigidDynamics;
