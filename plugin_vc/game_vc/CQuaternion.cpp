/*
    Plugin-SDK (Grand Theft Auto Vice City) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CQuaternion.h"

// Converted from thiscall void CQuaternion::Get(RwMatrixTag *) 0x4DFD30
void CQuaternion::Get(RwMatrixTag* out) {
    plugin::CallMethod<0x4DFD30, CQuaternion *, RwMatrixTag*>(this, out);
}

// Converted from thiscall void CQuaternion::Set(RwV3d *axis, float angle) 0x4DFE20
void CQuaternion::Set(RwV3d* axis, float angle) {
    plugin::CallMethod<0x4DFE20, CQuaternion *, RwV3d*, float>(this, axis, angle);
}

// Converted from thiscall void CQuaternion::Slerp(CQuaternion const& from,CQuaternion const& to, float halftheta, float sintheta_inv, float t) 0x4DFBE0
void CQuaternion::Slerp(CQuaternion const& from, CQuaternion const& to, float halftheta, float sintheta_inv, float t) {
    plugin::CallMethod<0x4DFBE0, CQuaternion *, CQuaternion const&, CQuaternion const&, float, float, float>(this, from, to, halftheta, sintheta_inv, t);
}

void CQuaternion::operator*=(float multiplier) {
    imag.fX *= multiplier;
    imag.fY *= multiplier;
    imag.fZ *= multiplier;
    real *= multiplier;
}

void CQuaternion::operator+=(CQuaternion const& right) {
    imag.fX += right.imag.fX;
    imag.fY += right.imag.fY;
    imag.fZ += right.imag.fZ;
    real += right.real;
}

void CQuaternion::operator-=(CQuaternion const& right) {
    imag.fX -= right.imag.fX;
    imag.fY -= right.imag.fY;
    imag.fZ -= right.imag.fZ;
    real -= right.real;
}

void CQuaternion::operator=(CQuaternion const& right) {
    imag.fX = right.imag.fX;
    imag.fY = right.imag.fY;
    imag.fZ = right.imag.fZ;
    real = right.real;
}

void CQuaternion::Normalise() {
    float d = imag.fX * imag.fX + imag.fY * imag.fY + imag.fZ * imag.fZ + real * real;
    if (d == 0.0f)
        real = 1.0f;
    else {
        float r = 1.0f / sqrtf(d);
        imag.fX *= r;
        imag.fY *= r;
        imag.fZ *= r;
        real *= r;
    }
}

void CQuaternion::Conjugate() {
    imag.fX = -imag.fX;
    imag.fY = -imag.fY;
    imag.fZ = -imag.fZ;
}

void CQuaternion::Get(RwV3d *axis, float *angle) {
    float a = acosf(real + real);
    *angle = a;
    float r = 1.0f / sinf(a);
    axis->fX = r * imag.fX;
    axis->fY = r * imag.fY;
    axis->fZ = r * imag.fZ;
}

void CQuaternion::Set(RwMatrix  const& m) {
    float a = m.up.fY + m.right.fX + m.at.fZ;
    if (a < 0.0f) {
        float b = m.right.fX - m.up.fY - m.at.fZ;
        if (b < 0.0f) {
            float c = m.up.fY - m.right.fX - m.at.fZ;
            if (c < 0.0f) {
                float d = sqrtf(m.at.fZ - (m.up.fY + m.right.fX) + 1.0f);
                imag.fZ = 0.5f * d;
                float e = 0.5f / d;
                real = (m.right.fY - m.up.fX) * e;
                imag.fX = (m.at.fX + m.right.fZ) * e;
                imag.fY = (m.at.fY + m.up.fZ) * e;
            }
            else {
                float f = sqrtf(c + 1.0f);
                imag.fY = 0.5f * f;
                float g = 0.5f / f;
                real = (m.at.fX - m.right.fZ) * g;
                imag.fX = (m.up.fX - m.right.fY) * g;
                imag.fZ = (m.at.fY + m.up.fZ) * g;
            }
        }
        else {
            float h = sqrtf(b + 1.0f);
            imag.fX = 0.5f * h;
            float i = 0.5f / h;
            imag.fY = (m.up.fX + m.right.fY) * i;
            imag.fZ = (m.at.fX + m.right.fZ) * i;
            real = (m.up.fZ - m.at.fY) * i;
        }
    }
    else {
        float j = sqrtf(a + 1.0f);
        real = 0.5f * j;
        float k = 0.5f / j;
        imag.fX = (m.up.fZ - m.at.fY) * k;
        imag.fY = (m.at.fX - m.right.fZ) * k;
        imag.fZ = (m.right.fY - m.up.fX) * k;
    }
}

void CQuaternion::Multiply(CQuaternion const& a, CQuaternion const& b) {
    imag.fX = b.imag.fZ * a.imag.fY - a.imag.fZ * b.imag.fY;
    imag.fY = imag.fZ * b.imag.fX - imag.fX * b.imag.fZ;
    imag.fZ = imag.fX * b.imag.fY - b.imag.fX * imag.fY;
    imag.fX = b.real * imag.fX + real * b.imag.fX + imag.fX;
    imag.fY = real * b.imag.fY + b.real * imag.fY + imag.fY;
    imag.fZ = imag.fZ * b.real + real * b.imag.fZ + imag.fZ;
    real = real * b.real - (imag.fX * b.imag.fX + imag.fZ * b.imag.fZ + a.imag.fY * b.imag.fY);
}