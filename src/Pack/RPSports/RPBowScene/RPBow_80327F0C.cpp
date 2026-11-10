// Resort (RZTE01_01) port of Wii Sports RPBow_80327F0C.cpp (ogws source, CC0).
// fn_ names: Resort addresses where the function is matched to its ogws counterpart;
// ogws_fn_<ogws addr>: ogws function not located in Resort yet. NonMatching first pass.

// RPBow_80327F0C: a bowling rigid-body helper (position/velocity plus a 3x3
// orientation basis with per-frame min/max impulse accumulators).
// The owning class has a vtable at 0x0 (lbl_803CA640: fn_804EBB64 = update,
// fn_804EBF58 = reset); its real name is unknown, so the functions keep their
// fn_ names and take the object as an explicit pointer. Field names are
// inferred from use only.
// Functions are written in DESCENDING address order: MWCC emits them (and
// their .sdata2 pool entries) in reverse source order.
// Matching notes: the axis rows must be reached through a BowBodyState*
// (st->axis[i]) so MWCC keeps the addi'd row pointers; d in fn_804EB220 is
// written through an out-pointer helper so it stays in memory.

struct BowVec3Base {
    f32 x, y, z;
};

static inline void BowPsScale(register BowVec3Base* pOut, register const BowVec3Base* pIn,
                              register f32 scale);
static inline void BowPsAdd(register BowVec3Base* pOut, register const BowVec3Base* pA,
                            register const BowVec3Base* pB);
static inline void BowPsSub(register BowVec3Base* pOut, register const BowVec3Base* pA,
                            register const BowVec3Base* pB);

struct BowVec3 : BowVec3Base {
    BowVec3() {}
    BowVec3(f32 fx, f32 fy, f32 fz) {
        x = fx;
        y = fy;
        z = fz;
    }

    BowVec3& operator=(const BowVec3& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    f32 LenSq() const {
        return x * x + y * y + z * z;
    }

    BowVec3 operator+(const BowVec3& rhs) const {
        BowVec3 out;
        BowPsAdd(&out, this, &rhs);
        return out;
    }
    BowVec3 operator-(const BowVec3& rhs) const {
        BowVec3 out;
        BowPsSub(&out, this, &rhs);
        return out;
    }
    BowVec3 operator*(f32 s) const {
        BowVec3 out;
        BowPsScale(&out, this, s);
        return out;
    }
    BowVec3& operator+=(const BowVec3& rhs) {
        BowPsAdd(this, this, &rhs);
        return *this;
    }
    BowVec3& operator*=(f32 s) {
        BowPsScale(this, this, s);
        return *this;
    }
};

static inline void BowPsScale(register BowVec3Base* pOut, register const BowVec3Base* pIn,
                              register f32 scale) {
    register f32 w0, w1;
    asm {
        psq_l    w0, 0(pIn), 0, 0
        ps_muls0 w1, w0, scale
        psq_st   w1, 0(pOut), 0, 0
        psq_l    w0, 8(pIn), 1, 0
        ps_muls0 w1, w0, scale
        psq_st   w1, 8(pOut), 1, 0
    }
}

static inline void BowPsAdd(register BowVec3Base* pOut, register const BowVec3Base* pA,
                            register const BowVec3Base* pB) {
    register f32 w0, w1, w2;
    asm {
        psq_l  w0, 0(pA), 0, 0
        psq_l  w1, 0(pB), 0, 0
        ps_add w2, w0, w1
        psq_st w2, 0(pOut), 0, 0
        psq_l  w0, 8(pA), 1, 0
        psq_l  w1, 8(pB), 1, 0
        ps_add w2, w0, w1
        psq_st w2, 8(pOut), 1, 0
    }
}

static inline void BowPsSub(register BowVec3Base* pOut, register const BowVec3Base* pA,
                            register const BowVec3Base* pB) {
    register f32 w0, w1, w2;
    asm {
        psq_l  w0, 0(pA), 0, 0
        psq_l  w1, 0(pB), 0, 0
        ps_sub w2, w0, w1
        psq_st w2, 0(pOut), 0, 0
        psq_l  w0, 8(pA), 1, 0
        psq_l  w1, 8(pB), 1, 0
        ps_sub w2, w0, w1
        psq_st w2, 8(pOut), 1, 0
    }
}

static inline f32 BowPsLenSq(register const BowVec3Base* pVec) {
    register f32 yz, x, t, ret;
    asm {
        psq_l   yz, 4(pVec), 0, 0
        psq_l   x, 0(pVec), 1, 0
        ps_mul  yz, yz, yz
        ps_madd t, x, x, yz
        ps_sum0 ret, t, yz, yz
    }
    return ret;
}

static inline f32 BowPsDot(register const BowVec3Base* pA, register const BowVec3Base* pB) {
    register f32 w0, w1, w2, w3, dot;
    asm {
        psq_l   w0, 4(pA), 0, 0
        psq_l   w1, 4(pB), 0, 0
        ps_mul  w0, w0, w1
        psq_l   w3, 0(pA), 1, 0
        psq_l   w2, 0(pB), 1, 0
        ps_madd w1, w3, w2, w0
        ps_sum0 dot, w1, w0, w0
    }
    return dot;
}

static inline f32 BowDot(const BowVec3& a, const BowVec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

struct BowBodyState {
    BowVec3 pos;         // 0x04
    BowVec3 vel;         // 0x10
    BowVec3 prevPos;     // 0x1C
    BowVec3 impulseMin;  // 0x28
    BowVec3 impulseMax;  // 0x34
    BowVec3 forceMin;    // 0x40
    BowVec3 forceMax;    // 0x4C
    f32 velDamp;         // 0x58
    BowVec3 axis[3];     // 0x5C
    BowVec3 spin[3];     // 0x80 (only x/y used)
    BowVec3 spinMin0;    // 0xA4
    BowVec3 spinMax0;    // 0xB0
    BowVec3 spinMin1;    // 0xBC
    BowVec3 spinMax1;    // 0xC8
    BowVec3 spinMin2;    // 0xD4
    BowVec3 spinMax2;    // 0xE0
    f32 spinDamp;        // 0xEC
    f32 unkF0;           // 0xF0
    f32 radius;          // 0xF4
};

struct BowBody {
    void* vtable;        // 0x00
    BowBodyState s;      // 0x04
    u8 unkF8;            // 0xF8
    u8 unkF9;            // 0xF9
};

extern "C" {

double sqrt(double);
void* memset(void*, int, unsigned long);
void PSVECNormalize(const BowVec3Base* in, BowVec3Base* out);

void fn_804EB6E0(BowBody* self);
void fn_804EB5E8(BowBody* self, const BowVec3* v);
void fn_804EB220(BowBody* self, const BowVec3* lever, const BowVec3* torque);
void fn_804EAB80(void*, BowVec3* out0, BowVec3* out1, BowVec3* out2, const BowVec3* pa,
                 const BowVec3* pb);

void fn_804EBF58(BowBody* self) {
    self->s.pos = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.vel = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.axis[0] = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.axis[1] = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.axis[2] = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spin[0] = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spin[1] = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spin[2] = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.impulseMin = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.impulseMax = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.forceMin = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.forceMax = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMin0 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMax0 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMin1 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMax1 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMin2 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMax2 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.prevPos = self->s.pos;
    self->unkF9 = 0;
}

void fn_804EBE5C(BowBody* self, f32 radius, f32 unkF0, f32 velDamp, f32 spinDamp) {
    BowBodyState* s = &self->s;
    memset(s, 0, sizeof(BowBodyState));
    s->velDamp = velDamp;
    s->spinDamp = spinDamp;
    s->radius = radius;
    s->unkF0 = unkF0;
    s->axis[0] = BowVec3(1.0f, 0.0f, 0.0f);
    s->axis[1] = BowVec3(0.0f, 1.0f, 0.0f);
    s->axis[2] = BowVec3(0.0f, 0.0f, 1.0f);
    self->unkF8 = 0;
}

void fn_804EBB64(BowBody* self) {
    self->s.prevPos = self->s.pos;
    self->s.pos += self->s.vel;
    BowBodyState* st = &self->s;
    st->axis[0] += st->axis[1] * st->spin[0].x + st->axis[2] * st->spin[0].y;
    st->axis[1] += st->axis[2] * st->spin[1].x + st->axis[0] * st->spin[1].y;
    st->axis[2] += st->axis[0] * st->spin[2].x + st->axis[1] * st->spin[2].y;
    fn_804EB6E0(self);
    self->s.impulseMin = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.impulseMax = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.forceMin = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.forceMax = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMin0 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMax0 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMin1 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMax1 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMin2 = BowVec3(0.0f, 0.0f, 0.0f);
    self->s.spinMax2 = BowVec3(0.0f, 0.0f, 0.0f);
}

void fn_804EB9B8(BowBody* self) {
    self->s.pos += self->s.impulseMin + self->s.impulseMax;
    self->s.vel *= self->s.velDamp;
    self->s.vel += self->s.forceMin + self->s.forceMax;
    self->s.spin[0] *= self->s.spinDamp;
    self->s.spin[1] *= self->s.spinDamp;
    self->s.spin[2] *= self->s.spinDamp;
    self->s.spin[0].x += self->s.spinMin0.x + self->s.spinMax0.x;
    self->s.spin[0].y += self->s.spinMin0.y + self->s.spinMax0.y;
    self->s.spin[1].x += self->s.spinMin1.x + self->s.spinMax1.x;
    self->s.spin[1].y += self->s.spinMin1.y + self->s.spinMax1.y;
    self->s.spin[2].x += self->s.spinMin2.x + self->s.spinMax2.x;
    self->s.spin[2].y += self->s.spinMin2.y + self->s.spinMax2.y;
}

void fn_804EB6E0(BowBody* self) {
    f32 sum;
    f32 limit = 2.8f;
    do {
        PSVECNormalize(&self->s.axis[0], &self->s.axis[0]);
        PSVECNormalize(&self->s.axis[1], &self->s.axis[1]);
        PSVECNormalize(&self->s.axis[2], &self->s.axis[2]);
        BowVec3* a0 = &self->s.axis[0];
        BowVec3* a1 = &self->s.axis[1];
        BowVec3* a2 = &self->s.axis[2];
        BowVec3 c0;
        BowVec3 c1;
        BowVec3 c2;
        c0.x = a1->y * a2->z - a1->z * a2->y;
        c0.y = a1->z * a2->x - a1->x * a2->z;
        c0.z = a1->x * a2->y - a1->y * a2->x;
        c1.x = a2->y * a0->z - a2->z * a0->y;
        c1.y = a2->z * a0->x - a2->x * a0->z;
        c1.z = a2->x * a0->y - a2->y * a0->x;
        c2.x = a0->y * a1->z - a0->z * a1->y;
        c2.y = a0->z * a1->x - a0->x * a1->z;
        c2.z = a0->x * a1->y - a0->y * a1->x;
        f32 len = sqrt(c0.LenSq());
        sum = len;
        f32 inv = 1.0f / len;
        a0->x = 0.5f * (inv * c0.x + a0->x);
        a0->y = 0.5f * (inv * c0.y + a0->y);
        a0->z = 0.5f * (inv * c0.z + a0->z);
        len = sqrt(c1.LenSq());
        sum += len;
        inv = 1.0f / len;
        a1->x = 0.5f * (inv * c1.x + a1->x);
        a1->y = 0.5f * (inv * c1.y + a1->y);
        a1->z = 0.5f * (inv * c1.z + a1->z);
        len = sqrt(c2.LenSq());
        sum += len;
        inv = 1.0f / len;
        a2->x = 0.5f * (inv * c2.x + a2->x);
        a2->y = 0.5f * (inv * c2.y + a2->y);
        a2->z = 0.5f * (inv * c2.z + a2->z);
    } while (sum < limit);
}

void fn_804EB664(BowBody* self, const BowVec3* v) {
    if (v->x < self->s.impulseMin.x) {
        self->s.impulseMin.x = v->x;
    } else if (v->x > self->s.impulseMax.x) {
        self->s.impulseMax.x = v->x;
    }
    if (v->y < self->s.impulseMin.y) {
        self->s.impulseMin.y = v->y;
    } else if (v->y > self->s.impulseMax.y) {
        self->s.impulseMax.y = v->y;
    }
    if (v->z < self->s.impulseMin.z) {
        self->s.impulseMin.z = v->z;
    } else if (v->z > self->s.impulseMax.z) {
        self->s.impulseMax.z = v->z;
    }
}

void fn_804EB5E8(BowBody* self, const BowVec3* v) {
    if (v->x < self->s.forceMin.x) {
        self->s.forceMin.x = v->x;
    } else if (v->x > self->s.forceMax.x) {
        self->s.forceMax.x = v->x;
    }
    if (v->y < self->s.forceMin.y) {
        self->s.forceMin.y = v->y;
    } else if (v->y > self->s.forceMax.y) {
        self->s.forceMax.y = v->y;
    }
    if (v->z < self->s.forceMin.z) {
        self->s.forceMin.z = v->z;
    } else if (v->z > self->s.forceMax.z) {
        self->s.forceMax.z = v->z;
    }
}

static inline void BowClampMinMax(f32 v, f32& min, f32& max) {
    if (v < min) {
        min = v;
    } else if (v > max) {
        max = v;
    }
}

static inline void BowRotDelta(BowVec3* out, const BowVec3& m0, const BowVec3& m1,
                               const BowVec3& m2, const BowVec3& v) {
    out->x = m0.x * v.x + m1.x * v.y + m2.x * v.z - v.x;
    out->y = m0.y * v.x + m1.y * v.y + m2.y * v.z - v.y;
    out->z = m0.z * v.x + m1.z * v.y + m2.z * v.z - v.z;
}


void fn_804EB220(BowBody* self, const BowVec3* lever, const BowVec3* torque) {
    BowVec3 m0(1.0f, 0.0f, 0.0f);
    BowVec3 m1(0.0f, 1.0f, 0.0f);
    BowVec3 m2(0.0f, 0.0f, 1.0f);
    BowVec3 d;
    BowBodyState* st = &self->s;
    BowVec3* a0 = &st->axis[0];
    BowVec3* a1 = &st->axis[1];
    BowVec3* a2 = &st->axis[2];

    fn_804EAB80(self, &m0, &m1, &m2, lever, torque);

    f32 w;

    BowRotDelta(&d, m0, m1, m2, *a0);
    w = 1.0f / (1.0f + d.x * self->s.axis[0].x + d.y * self->s.axis[0].y + d.z * self->s.axis[0].z);
    BowClampMinMax(w * BowDot(d, *a1), self->s.spinMin0.x, self->s.spinMax0.x);
    BowClampMinMax(w * BowDot(d, *a2), self->s.spinMin0.y, self->s.spinMax0.y);

    BowRotDelta(&d, m0, m1, m2, *a1);
    w = 1.0f / (1.0f + d.x * self->s.axis[1].x + d.y * self->s.axis[1].y + d.z * self->s.axis[1].z);
    BowClampMinMax(w * BowDot(d, *a2), self->s.spinMin1.x, self->s.spinMax1.x);
    BowClampMinMax(w * BowDot(d, *a0), self->s.spinMin1.y, self->s.spinMax1.y);

    BowRotDelta(&d, m0, m1, m2, *a2);
    w = 1.0f / (1.0f + d.x * self->s.axis[2].x + d.y * self->s.axis[2].y + d.z * self->s.axis[2].z);
    BowClampMinMax(w * BowDot(d, *a0), self->s.spinMin2.x, self->s.spinMax2.x);
    BowClampMinMax(w * BowDot(d, *a1), self->s.spinMin2.y, self->s.spinMax2.y);
}

void fn_804EAEC0(BowBody* self, const BowVec3* point, const BowVec3* force, int applyForce,
                 int applyTorque, f32 limit) {
    BowVec3 r;
    BowVec3 v;
    f32 invR = 1.0f / self->s.radius;
    BowVec3 c = self->s.pos;
    f32 maxv = self->s.unkF0;
    f32 kTorque = 3.17f;
    if (limit >= 0.0f) {
        maxv = limit;
    }
    f32 len = sqrt(BowPsLenSq(force));
    if (len <= 1e-5f) {
        return;
    }
    f32 inv = 1.0f / len;
    v = *force * inv;
    r = *point - c;
    f32 rlen2 = BowPsLenSq(&r);
    f32 dot = BowPsDot(&v, &r);
    f32 perp2 = rlen2 - dot * dot;
    f32 dist;
    if (perp2 < 1e-6f) {
        dist = 0.0f;
    } else {
        dist = sqrt(perp2);
    }
    if (0.0f == dist) {
        if (applyForce) {
            fn_804EB5E8(self, force);
        }
        return;
    }
    f32 k = 1.0f - dist * invR;
    if (k > 0.0f) {
        if (k > 1.0f) {
            k = 1.0f;
        }
        v = *force * k;
        if (applyForce) {
            fn_804EB5E8(self, &v);
        }
    }
    if (applyTorque) {
        f32 rinv = 1.0f / (f32)sqrt(rlen2);
        r *= rinv;
        invR *= maxv;
        f32 d = BowPsDot(&r, force);
        v = (*force - r * d) * invR * kTorque;
        fn_804EB220(self, &r, &v);
    }
}

void fn_804EAE34(BowBody* self, const BowVec3* point, const BowVec3* force, f32 limit, f32 scale) {
    BowVec3 scaled;
    BowPsScale(&scaled, force, scale);
    fn_804EB5E8(self, &scaled);
    fn_804EAEC0(self, point, force, 0, 1, limit);
}

void fn_804EAB80(void*, BowVec3* out0, BowVec3* out1, BowVec3* out2, const BowVec3* pa,
                 const BowVec3* pb) {
    BowVec3 a;
    BowVec3 b;
    BowVec3 c;
    a = *pa;
    b = *pb;
    f32 len = sqrt(b.LenSq());
    if (0.0f == len) {
        *out0 = BowVec3(1.0f, 0.0f, 0.0f);
        *out1 = BowVec3(0.0f, 1.0f, 0.0f);
        *out2 = BowVec3(0.0f, 0.0f, 1.0f);
    } else {
        f32 inv = 1.0f / len;
        b.x *= inv;
        b.y *= inv;
        b.z *= inv;
        c.x = a.y * b.z - a.z * b.y;
        c.y = a.z * b.x - a.x * b.z;
        c.z = a.x * b.y - a.y * b.x;
        f32 sx = a.x + pb->x;
        f32 sy = a.y + pb->y;
        f32 sz = a.z + pb->z;
        len = sqrt(sx * sx + sy * sy + sz * sz);
        len = 1.0f / len;
        f32 k = len * (sx * a.x + sy * a.y + sz * a.z);
        // Declaration order (xz first) sets the FPR colouring of the
        // off-diagonal terms; assignments follow the store order.
        f32 xz, xy, yz, xm, ym, zm;
        len *= (sx * b.x + sy * b.y + sz * b.z);
        out0->x = c.x * c.x + k * (a.x * a.x + b.x * b.x);
        out1->y = c.y * c.y + k * (a.y * a.y + b.y * b.y);
        out2->z = c.z * c.z + k * (a.z * a.z + b.z * b.z);
        xy = c.x * c.y + k * (a.x * a.y + b.x * b.y);
        zm = c.z * len;
        yz = c.y * c.z + k * (a.y * a.z + b.y * b.z);
        xm = c.x * len;
        xz = c.x * c.z + k * (a.x * a.z + b.x * b.z);
        ym = c.y * len;
        out0->y = xy + zm;
        out1->x = xy - zm;
        out1->z = yz + xm;
        out2->y = yz - xm;
        out2->x = xz + ym;
        out0->z = xz - ym;
    }
}

// The owning class's vtable (slot 0 = RTTI, slot 1 = this-offset, then
// update/reset). The class is not modelled yet, so the table is written out as
// data, like lbl_803CA6B0 in RPBow_8032ADD8.
void* lbl_803CA640[] = {
    0, 0, (void*)fn_804EBB64, (void*)fn_804EBF58,
};

}  // extern "C"
