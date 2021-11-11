/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "RenderWare.h"

class CVector : public RwV3d {
public:

    CVector();
    CVector(float X, float Y, float Z);

    inline CVector(CVector const& src) {
        fX = src.fX; fY = src.fY; fZ = src.fZ;
    }

    inline CVector(RwV3d const &right) {
        FromRwV3d(right);
    }

    // Returns length of vector
    float Magnitude();

    // Returns length of 2d vector
    float Magnitude2D();

    // Normalises a vector
    void Normalise();

    // Normalises a vector and returns length
    float NormaliseAndMag();

    // Performs cross calculation
    void Cross(const CVector& left, const CVector &right);

    // Adds left + right and stores result
    void Sum(const CVector& left, const CVector &right);

    // Subtracts left - right and stores result
    void Difference(const CVector& left, const CVector &right);

    void operator=(const CVector& right);
    void operator+=(const CVector& right);
    void operator-=(const CVector& right);
    void operator *= (float multiplier);
    void operator /= (float divisor);

    // matrix * vector multiplication
    void FromMultiply(class CMatrix  const& matrix, CVector const& vector);
    void FromMultiply3x3(class CMatrix  const& matrix, CVector const& vector);

    inline void Set(float X, float Y, float Z) {
        fX = X; fY = Y; fZ = Z;
    }

    inline RwV3d ToRwV3d() const {
        return{ fX, fY, fZ };
    }

    inline void FromRwV3d(RwV3d const &rwvec) {
        fX = rwvec.fX; fY = rwvec.fY; fZ = rwvec.fZ;
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

VALIDATE_SIZE(CVector, 0xC);
