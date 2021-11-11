/*
    Plugin-SDK (Grand Theft Auto 3) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"
#include <math.h>

class CVector {
public:
    float fX, fY, fZ;

    inline CVector() {}

    inline CVector(float X, float Y, float Z) {
        fX = X; fY = Y; fZ = Z;
    }

    inline CVector(CVector const& src) {
        fX = src.fX; fY = src.fY; fZ = src.fZ;
    }

    inline CVector(RwV3d const &right) {
        FromRwV3d(right);
    }

    inline void Cross(CVector &a, CVector &b) {
        this->fX = b.fZ * a.fY - a.fZ * b.fY;
        this->fY = a.fZ * b.fX - a.fX * b.fZ;
        this->fZ = a.fX * b.fY - b.fX * a.fY;
    }

    inline float Magnitude() {
        return sqrtf(this->fX * this->fX + this->fY * this->fY + this->fZ * this->fZ);
    }

    inline void Sum(CVector &a, CVector &b) {
        this->fX = a.fX + b.fX;
        this->fY = a.fY + b.fY;
        this->fZ = a.fZ + b.fZ;
    }

    inline void Difference(CVector &a, CVector &b) {
        this->fX = a.fX - b.fX;
        this->fY = a.fY - b.fY;
        this->fZ = a.fZ - b.fZ;
    }

    inline void operator=(const CVector& right) {
        this->fX = right.fX;
        this->fY = right.fY;
        this->fZ = right.fZ;
    }

    inline void operator+=(const CVector& right) {
        this->fX += right.fX;
        this->fY += right.fY;
        this->fZ += right.fZ;
    }

    inline void operator-=(const CVector& right) {
        this->fX -= right.fX;
        this->fY -= right.fY;
        this->fZ -= right.fZ;
    }

    inline void operator *= (float multiplier) {
        this->fX *= multiplier;
        this->fY *= multiplier;
        this->fZ *= multiplier;
    }

    inline void operator /= (float divisor) {
        this->fX /= divisor;
        this->fY /= divisor;
        this->fZ /= divisor;
    }

    float Normalise();

    inline RwV3d ToRwV3d() const {
        return{ fX, fY, fZ };
    }

    inline void FromRwV3d(RwV3d const &rwvec) {
        fX = rwvec.fX; fY = rwvec.fY; fZ = rwvec.fZ;
    }

    inline void Set(float X, float Y, float Z) {
        fX = X; fY = Y; fZ = Z;
    }
};

inline CVector operator-(const CVector& vecOne, const CVector& vecTwo) {
    return CVector(vecOne.fX - vecTwo.fX, vecOne.fY - vecTwo.fY, vecOne.fZ - vecTwo.fZ);
}

inline CVector operator+(const CVector& vecOne, const CVector& vecTwo) {
    return CVector(vecOne.fX + vecTwo.fX, vecOne.fY + vecTwo.fY, vecOne.fZ + vecTwo.fZ);
}

inline CVector operator*(const CVector& vec, float multiplier) {
    return CVector(vec.fX * multiplier, vec.fY * multiplier, vec.fZ * multiplier);
}

inline CVector operator*(float multiplier, const CVector& vec) {
    return CVector(vec.fX * multiplier, vec.fY * multiplier, vec.fZ * multiplier);
}

inline float DistanceBetweenPoints(const CVector &pointOne, const CVector &pointTwo) {
    CVector diff = pointTwo - pointOne;
    return diff.Magnitude();
}