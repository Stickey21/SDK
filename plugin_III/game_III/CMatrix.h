/*
    Plugin-SDK (Grand Theft Auto 3) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "RenderWare.h"

class PLUGIN_API CMatrix {
public:
    CVector right;
    unsigned int flags;
    CVector up;
    unsigned int pad1;
    CVector at;
    unsigned int pad2;
    CVector pos;
    unsigned int pad3;
    RwMatrix *m_pAttachMatrix;
    bool m_bOwnsAttachedMatrix; //!< do we need to delete attaching matrix at detaching

    SUPPORTED_10EN_11EN_STEAM CMatrix();

    SUPPORTED_10EN_11EN_STEAM CMatrix(RwMatrix *rwMatrix, bool deleteOnDetach);

    SUPPORTED_10EN_11EN_STEAM CMatrix(CMatrix const &matrix);

    SUPPORTED_10EN_11EN_STEAM ~CMatrix();

    SUPPORTED_10EN_11EN_STEAM void operator+=(CMatrix const &right);
    SUPPORTED_10EN_11EN_STEAM void operator=(CMatrix const &right);

    SUPPORTED_10EN_11EN_STEAM void Attach(RwMatrix *rwMatrix, bool deleteOnDetach);
    SUPPORTED_10EN_11EN_STEAM void AttachRW(RwMatrix *rwMatrix, bool deleteOnDetach);
    SUPPORTED_10EN_11EN_STEAM void CopyOnlyMatrix(CMatrix const &matrix);
    SUPPORTED_10EN_11EN_STEAM void Detach();
    SUPPORTED_10EN_11EN_STEAM void Reorthogonalise();
    SUPPORTED_10EN_11EN_STEAM void ResetOrientation();
    SUPPORTED_10EN_11EN_STEAM void Rotate(float x, float y, float z);
    SUPPORTED_10EN_11EN_STEAM void RotateX(float angle);
    SUPPORTED_10EN_11EN_STEAM void RotateZ(float angle);
    SUPPORTED_10EN_11EN_STEAM void SetRotate(float x, float y, float z);
    SUPPORTED_10EN_11EN_STEAM void SetRotateX(float angle);
    SUPPORTED_10EN_11EN_STEAM void SetRotateXOnly(float angle);
    SUPPORTED_10EN_11EN_STEAM void SetRotateY(float angle);
    SUPPORTED_10EN_11EN_STEAM void SetRotateYOnly(float angle);
    SUPPORTED_10EN_11EN_STEAM void SetRotateZ(float angle);
    SUPPORTED_10EN_11EN_STEAM void SetRotateZOnly(float angle);
    SUPPORTED_10EN_11EN_STEAM void SetScale(float factor);
    SUPPORTED_10EN_11EN_STEAM void SetTranslate(float x, float y, float z);
    SUPPORTED_10EN_11EN_STEAM void SetTranslate(CVector *pos);
    SUPPORTED_10EN_11EN_STEAM void SetTranslateOnly(float x, float y, float z);
    SUPPORTED_10EN_11EN_STEAM void SetUnity();
    SUPPORTED_10EN_11EN_STEAM void Update();
    SUPPORTED_10EN_11EN_STEAM void UpdateRW();
};

VALIDATE_SIZE(CMatrix, 0x48);

inline CVector operator*(const CMatrix &mat, const CVector &vec) {
    return CVector(mat.right.fX * vec.fX + mat.up.fX * vec.fY + mat.at.fX * vec.fZ + mat.pos.fX,
        mat.right.fY * vec.fX + mat.up.fY * vec.fY + mat.at.fY * vec.fZ + mat.pos.fY,
        mat.right.fZ * vec.fX + mat.up.fZ * vec.fY + mat.at.fZ * vec.fZ + mat.pos.fZ);
};

inline CMatrix operator*(const CMatrix &m1, const CMatrix &m2) {
    CMatrix out;
    out.right.fX = m1.right.fX * m2.right.fX + m1.up.fX * m2.right.fY + m1.at.fX * m2.right.fZ;
    out.right.fY = m1.right.fY * m2.right.fX + m1.up.fY * m2.right.fY + m1.at.fY * m2.right.fZ;
    out.right.fZ = m1.right.fZ * m2.right.fX + m1.up.fZ * m2.right.fY + m1.at.fZ * m2.right.fZ;
    out.up.fX = m1.right.fX * m2.up.fX + m1.up.fX * m2.up.fY + m1.at.fX * m2.up.fZ;
    out.up.fY = m1.right.fY * m2.up.fX + m1.up.fY * m2.up.fY + m1.at.fY * m2.up.fZ;
    out.up.fZ = m1.right.fZ * m2.up.fX + m1.up.fZ * m2.up.fY + m1.at.fZ * m2.up.fZ;
    out.at.fX = m1.right.fX * m2.at.fX + m1.up.fX * m2.at.fY + m1.at.fX * m2.at.fZ;
    out.at.fY = m1.right.fY * m2.at.fX + m1.up.fY * m2.at.fY + m1.at.fY * m2.at.fZ;
    out.at.fZ = m1.right.fZ * m2.at.fX + m1.up.fZ * m2.at.fY + m1.at.fZ * m2.at.fZ;
    out.pos.fX = m1.right.fX * m2.pos.fX + m1.up.fX * m2.pos.fY + m1.at.fX * m2.pos.fZ + m1.pos.fX;
    out.pos.fY = m1.right.fY * m2.pos.fX + m1.up.fY * m2.pos.fY + m1.at.fY * m2.pos.fZ + m1.pos.fY;
    out.pos.fZ = m1.right.fZ * m2.pos.fX + m1.up.fZ * m2.pos.fY + m1.at.fZ * m2.pos.fZ + m1.pos.fZ;
    return out;
};

inline CVector Multiply3x3(const CMatrix &mat, const CVector &vec) {
    return CVector(mat.right.fX * vec.fX + mat.up.fX * vec.fY + mat.at.fX * vec.fZ,
        mat.right.fY * vec.fX + mat.up.fY * vec.fY + mat.at.fY * vec.fZ,
        mat.right.fZ * vec.fX + mat.up.fZ * vec.fY + mat.at.fZ * vec.fZ);
};

inline CVector Multiply3x3(const CVector &vec, const CMatrix &mat) {
    return CVector(mat.right.fX * vec.fX + mat.right.fY * vec.fY + mat.right.fZ * vec.fZ,
        mat.up.fX * vec.fX + mat.up.fY * vec.fY + mat.up.fZ * vec.fZ,
        mat.at.fX * vec.fX + mat.at.fY * vec.fY + mat.at.fZ * vec.fZ);
};

inline CMatrix& Invert(const CMatrix &src, CMatrix &dst) {
    dst.pos.fX = dst.pos.fY = dst.pos.fZ = 0.0f;
    dst.pad3 = src.pad3;
    dst.right.fX = src.right.fX;
    dst.right.fY = src.up.fX;
    dst.right.fZ = src.at.fX;
    *(float *)dst.flags = src.pos.fX;
    dst.up.fX = src.right.fY;
    dst.up.fY = src.up.fY;
    dst.up.fZ = src.at.fY;
    *(float *)dst.pad1 = src.pos.fY;
    dst.at.fX = src.right.fZ;
    dst.at.fY = src.up.fZ;
    dst.at.fZ = src.at.fZ;
    *(float *)dst.pad2 = src.pos.fZ;
    dst.pos.fX += dst.right.fX * src.pos.fX;
    dst.pos.fY += dst.right.fY * src.pos.fX;
    dst.pos.fZ += dst.right.fZ * src.pos.fX;
    *(float *)dst.pad3 += *(float *)dst.flags * src.pos.fX;
    dst.pos.fX += dst.up.fX * src.pos.fY;
    dst.pos.fY += dst.up.fY * src.pos.fY;
    dst.pos.fZ += dst.up.fZ * src.pos.fY;
    *(float *)dst.pad3 += *(float *)dst.pad1 * src.pos.fY;
    dst.pos.fX += dst.at.fX * src.pos.fZ;
    dst.pos.fY += dst.at.fY * src.pos.fZ;
    dst.pos.fZ += dst.at.fZ * src.pos.fZ;
    *(float *)dst.pad3 += *(float *)dst.pad2 * src.pos.fZ;
    dst.pos.fX = -dst.pos.fX;
    dst.pos.fY = -dst.pos.fY;
    dst.pos.fZ = -dst.pos.fZ;
    dst.pad3 = src.pad3 - dst.pad3;

    return dst;
};

inline CMatrix Invert(const CMatrix &matrix) {
    CMatrix inv;
    return Invert(matrix, inv);
};

#include "meta/meta.CMatrix.h"
