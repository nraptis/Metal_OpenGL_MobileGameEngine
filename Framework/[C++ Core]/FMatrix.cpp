//
//  FMatrix.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/6/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FMatrix.hpp"
#include "core_includes.h"

FMatrix::FMatrix() {
    m[0] = 1.0f;m[1] = 0.0f;m[2] = 0.0f;m[3] = 0.0f;
    m[4] = 0.0f;m[5] = 1.0f;m[6] = 0.0f;m[7] = 0.0f;
    m[8] = 0.0f;m[9] = 0.0f;m[10]= 1.0f;m[11]= 0.0f;
    m[12]= 0.0f;m[13]= 0.0f;m[14]= 0.0f;m[15]= 1.0f;
}

FMatrix::FMatrix(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33) {
    m[0]=m00;m[1]=m01;m[2]=m02;m[3]=m03;
    m[4]=m10;m[5]=m11;m[6]=m12;m[7]=m13;
    m[8]=m20;m[9]=m21;m[10]=m22;m[11]=m23;
    m[12]=m30;m[13]=m31;m[14]=m32;m[15]=m33;
}

FMatrix::~FMatrix()
{
    
}

void FMatrix::Reset() {
    m[0] = 1.0f;m[1] = 0.0f;m[2] = 0.0f;m[3] = 0.0f;
    m[4] = 0.0f;m[5] = 1.0f;m[6] = 0.0f;m[7] = 0.0f;
    m[8] = 0.0f;m[9] = 0.0f;m[10]= 1.0f;m[11]= 0.0f;
    m[12]= 0.0f;m[13]= 0.0f;m[14]= 0.0f;m[15]= 1.0f;
}

void FMatrix::Set(FMatrix &pMatrix) {
    float *aData = pMatrix.m;
    m[0]  = aData[0] ;m[1]  = aData[1] ;m[2]  = aData[2] ;m[3]  = aData[3];
    m[4]  = aData[4] ;m[5]  = aData[5] ;m[6]  = aData[6] ;m[7]  = aData[7];
    m[8]  = aData[8] ;m[9]  = aData[9] ;m[10] = aData[10];m[11] = aData[11];
    m[12] = aData[12];m[13] = aData[13];m[14] = aData[14];m[15] = aData[15];
}

void FMatrix::SetNormalMatrix(FMatrix &pModelView) {
    
    Set(pModelView);
    InvertAndTranspose();
    
    //FMatrix aMatrix;
    //aMatrix.Set(pModelView);
    //aMatrix.InvertAndTranspose();
    //Set(aMatrix);
}


void FMatrix::Set(int pRow, int pCol, float pValue) {
    int aIndex = pCol * 4 + pRow;
    if((aIndex >= 0) && (aIndex < 16)) {
        m[aIndex] = pValue;
    }
}

void FMatrix::Multiply(FMatrix &pMatrix) {
    *this = FMatrixMultiply(*this, pMatrix);
}

void FMatrix::Add(FMatrix &pMatrix) {
    *this = FMatrixAdd(*this, pMatrix);
}

void FMatrix::Subtract(FMatrix &pMatrix) {
    *this = FMatrixSubtract(*this, pMatrix);
}

void FMatrix::Rotate(float pDegrees, float pAxisX, float pAxisY, float pAxisZ) {
    *this = FMatrixRotate(*this, DEGREES_TO_RADIANS(pDegrees), pAxisX, pAxisY, pAxisZ);
}

void FMatrix::RotateX(float pDegrees) {
    if (pDegrees != 0.0f) {
        *this = FMatrixRotateX(*this, DEGREES_TO_RADIANS(pDegrees));
    }
}

void FMatrix::RotateY(float pDegrees) {
    if (pDegrees != 0.0f) {
        *this = FMatrixRotateY(*this, DEGREES_TO_RADIANS(pDegrees));
    }
}

void FMatrix::RotateZ(float pDegrees) {
    if (pDegrees != 0.0f) {
        *this = FMatrixRotateZ(*this, DEGREES_TO_RADIANS(pDegrees));
    }
}

void FMatrix::ResetRotation(float pDegrees, float pX, float pY, float pZ) {
    float aDist = pX * pX + pY * pY + pZ * pZ;
    if (aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
        pX /= aDist;
        pY /= aDist;
        pZ /= aDist;
    }
    ResetRotationNormalized(pDegrees, pX, pY, pZ);
}

void FMatrix::ResetRotationNormalized(float pDegrees, float pX, float pY, float pZ) {
    float aRads = DEGREES_TO_RADIANS(pDegrees);
    float aCos = cosf(aRads);
    float aCosInv = 1.0f - aCos;
    float aSin = sinf(aRads);
    float aCosInvX = aCosInv * pX;
    float aCosInvY = aCosInv * pY;
    float aCosInvXY = aCosInvX * pY;
    float aCosInvXZ = aCosInvX * pZ;
    float aCosInvYZ = aCosInvY * pZ;
    float aSinX = pX * aSin;
    float aSinY = pY * aSin;
    float aSinZ = pZ * aSin;
    
    m[0 ] = aCos + aCosInvX * pX;
    m[1 ] = aCosInvXY + aSinZ;
    m[2 ] = aCosInvXZ - aSinY;
    m[3 ] = 0.0f;
    
    m[4 ] = aCosInvXY - aSinZ;
    m[5 ] = aCos + aCosInvY * pY;
    m[6 ] = aCosInvYZ + aSinX;
    m[7 ] = 0.0f;
    
    m[8 ] = aCosInvXZ + aSinY;
    m[9 ] = aCosInvYZ - aSinX;
    m[10] = aCos + aCosInv * pZ * pZ;
    m[11] = 0.0f;
    
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
}

void FMatrix::ResetRotationX(float pDegrees) {
    
    float aRads = DEGREES_TO_RADIANS(pDegrees);
    float aCos = cosf(aRads);
    float aSin = sinf(aRads);
    
    
    m[0 ] = 1.0f;
    m[1 ] = 0.0f;
    m[2 ] = 0.0f;
    m[3 ] = 0.0f;
    
    m[4 ] = 0.0f;
    m[5 ] = aCos;
    m[6 ] = aSin;
    m[7 ] = 0.0f;
    
    m[8 ] = 0.0f;
    m[9 ] = -aSin;
    m[10] = aCos;
    m[11] = 0.0f;
    
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
    
}

void FMatrix::ResetRotationY(float pDegrees) {
    float aRads = DEGREES_TO_RADIANS(pDegrees);
    float aCos = cosf(aRads);
    float aSin = sinf(aRads);
    m[0 ] = aCos;
    m[1 ] = 0.0f;
    m[2 ] = -aSin;
    m[3 ] = 0.0f;
    
    m[4 ] = 0.0f;
    m[5 ] = 1.0f;
    m[6 ] = 0.0f;
    m[7 ] = 0.0f;
    
    m[8 ] = aSin;
    m[9 ] = 0.0f;
    m[10] = aCos;
    m[11] = 0.0f;
    
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
}

void FMatrix::ResetRotationZ(float pDegrees) {
    float aRads = DEGREES_TO_RADIANS(pDegrees);
    float aCos = cosf(aRads);
    float aSin = sinf(aRads);
    
    m[0 ] = aCos;
    m[1 ] = aSin;
    m[2 ] = 0.0f;
    m[3 ] = 0.0f;
    
    m[4 ] = -aSin;
    m[5 ] = aCos;
    m[6 ] = 0.0f;
    m[7 ] = 0.0f;
    
    m[8 ] = 0.0f;
    m[9 ] = 0.0f;
    m[10] = 1.0f;
    m[11] = 0.0f;
    
    m[12] = 0.0f;
    m[13] = 0.0f;
    m[14] = 0.0f;
    m[15] = 1.0f;
}

void FMatrix::Translate(float pX, float pY) {
    if ((pX != 0.0f) || (pY != 0.0f)) {
        *this = FMatrixTranslate(*this, pX, pY, 0.0f);
    }
}

void FMatrix::Translate(float pX, float pY, float pZ) {
    if ((pX != 0.0f) || (pY != 0.0f) || (pZ != 0.0f)) {
        *this = FMatrixTranslate(*this, pX, pY, pZ);
    }
}

void FMatrix::SetTranslation(float pX, float pY, float pZ, float pW) {
    m[3] = pX;
    m[7] = pY;
    m[11] = pZ;
    m[15] = pW;
}

void FMatrix::ResetTranslation() {
    SetTranslation(0.0f, 0.0f, 0.0f, 1.0f);
}

FVec2 FMatrix::ProcessVec2(FVec2 pVec) {
    FVec3 aResult = ProcessVec3(FVec3(pVec.mX, pVec.mY, 0.0f));
    return FVec2(aResult.mX, aResult.mY);
}

FVec2 FMatrix::ProcessVec2RotationOnly(FVec2 pVec) {
    FVec3 aResult = ProcessVec3RotationOnly(FVec3(pVec.mX, pVec.mY, 0.0f));
    return FVec2(aResult.mX, aResult.mY);
}

FVec3 FMatrix::ProcessVec3(FVec3 pVec) {
    float aX = m[0] * pVec.mX + m[4] * pVec.mY + m[8 ] * pVec.mZ + m[12];
    float aY = m[1] * pVec.mX + m[5] * pVec.mY + m[9 ] * pVec.mZ + m[13];
    float aZ = m[2] * pVec.mX + m[6] * pVec.mY + m[10] * pVec.mZ + m[14];
    float aW = m[3] * pVec.mX + m[7] * pVec.mY + m[11] * pVec.mZ + m[15];
    
    if (fabsf(aW) > SQRT_EPSILON) {
        float aScale = 1.0 / aW;
        return FVec3(aX * aScale, aY * aScale, aZ * aScale);
    }
    
    return FVec3(aX, aY, aZ);
}

FVec3 FMatrix::ProcessVec3RotationOnly(FVec3 pVec) {
    float aX = m[0] * pVec.mX + m[4] * pVec.mY + m[8 ] * pVec.mZ;
    float aY = m[1] * pVec.mX + m[5] * pVec.mY + m[9 ] * pVec.mZ;
    float aZ = m[2] * pVec.mX + m[6] * pVec.mY + m[10] * pVec.mZ;
    return FVec3(aX, aY, aZ);
}

/*
 GLK_INLINE GLKFVec3 GLKMatrix4MultiplyAndProjectFVec3(GLKMatrix4 pMatrixLeft, GLKFVec3 vectorRight)
 {
 GLKVector4 v4 = GLKMatrix4MultiplyVector4(pMatrixLeft, GLKVector4Make(vectorRight.v[0], vectorRight.v[1], vectorRight.v[2], 1.0f));
 return GLKFVec3MultiplyScalar(GLKFVec3Make(v4.v[0], v4.v[1], v4.v[2]), 1.0f / v4.v[3]);
 }
 
 
 GLK_INLINE GLKVector4 GLKMatrix4MultiplyVector4(GLKMatrix4 pMatrixLeft, GLKVector4 vectorRight)
 {
 #if defined(__ARM_NEON__)
 float32x4x4_t iMatrix = *(float32x4x4_t *)&pMatrixLeft;
 float32x4_t v;
 
 iMatrix.val[0] = vmulq_n_f32(iMatrix.val[0], (float32_t)vectorRight.v[0]);
 iMatrix.val[1] = vmulq_n_f32(iMatrix.val[1], (float32_t)vectorRight.v[1]);
 iMatrix.val[2] = vmulq_n_f32(iMatrix.val[2], (float32_t)vectorRight.v[2]);
 iMatrix.val[3] = vmulq_n_f32(iMatrix.val[3], (float32_t)vectorRight.v[3]);
 
 iMatrix.val[0] = vaddq_f32(iMatrix.val[0], iMatrix.val[1]);
 iMatrix.val[2] = vaddq_f32(iMatrix.val[2], iMatrix.val[3]);
 
 v = vaddq_f32(iMatrix.val[0], iMatrix.val[2]);
 
 return *(GLKVector4 *)&v;
 #elif defined(GLK_SSE3_INTRINSICS)
 const __m128 v = _mm_load_ps(&vectorRight.v[0]);
 
 const __m128 r = _mm_load_ps(&pMatrixLeft.m[0])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0))
 + _mm_load_ps(&pMatrixLeft.m[4])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1))
 + _mm_load_ps(&pMatrixLeft.m[8])  * _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2))
 + _mm_load_ps(&pMatrixLeft.m[12]) * _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));
 
 GLKVector4 ret;
 *(__m128*)&ret = r;
 return ret;
 #else
 GLKVector4 v = { pMatrixLeft.m[0] * vectorRight.v[0] + pMatrixLeft.m[4] * vectorRight.v[1] + pMatrixLeft.m[8] * vectorRight.v[2] + pMatrixLeft.m[12] * vectorRight.v[3],
 pMatrixLeft.m[1] * vectorRight.v[0] + pMatrixLeft.m[5] * vectorRight.v[1] + pMatrixLeft.m[9] * vectorRight.v[2] + pMatrixLeft.m[13] * vectorRight.v[3],
 pMatrixLeft.m[2] * vectorRight.v[0] + pMatrixLeft.m[6] * vectorRight.v[1] + pMatrixLeft.m[10] * vectorRight.v[2] + pMatrixLeft.m[14] * vectorRight.v[3],
 pMatrixLeft.m[3] * vectorRight.v[0] + pMatrixLeft.m[7] * vectorRight.v[1] + pMatrixLeft.m[11] * vectorRight.v[2] + pMatrixLeft.m[15] * vectorRight.v[3] };
 return v;
 #endif
 }
 
 
 GLK_INLINE GLKFVec3 GLKFVec3MultiplyScalar(GLKFVec3 vector, float value)
 {
 GLKFVec3 v = { vector.v[0] * value,
 vector.v[1] * value,
 vector.v[2] * value };
 return v;
 }
 */


void FMatrix::Scale(float pScale) {
    if (pScale != 1.0f) {
        m[0] *= pScale;
        m[1] *= pScale;
        m[2] *= pScale;
        m[3] *= pScale;
        m[4] *= pScale;
        m[5] *= pScale;
        m[6] *= pScale;
        m[7] *= pScale;
        m[8] *= pScale;
        m[9] *= pScale;
        m[10] *= pScale;
        m[11] *= pScale;
    }
}

void FMatrix::Scale(float pScaleX, float pScaleY, float pScaleZ) {
    if (pScaleX != 1.0f) {
        m[0] *= pScaleX;
        m[1] *= pScaleX;
        m[2] *= pScaleX;
        m[3] *= pScaleX;
    }
    if (pScaleY != 1.0f) {
        m[4] *= pScaleY;
        m[5] *= pScaleY;
        m[6] *= pScaleY;
        m[7] *= pScaleY;
    }
    if (pScaleZ != 1.0f) {
        m[8] *= pScaleZ;
        m[9] *= pScaleZ;
        m[10] *= pScaleZ;
        m[11] *= pScaleZ;
    }
}

void FMatrix::Transpose() {
    *this = FMatrixTranspose(*this);
}



void FMatrix::Invert() {
    
    bool aInvertable = false;
    FMatrix aInvertedMatrix = FMatrixInvert(*this, &aInvertable);
    if (aInvertable) {
        *this = aInvertedMatrix;
    }
    
    /*
    float b00 = pMatrix.m[0] * pMatrix.m[5] - pMatrix.m[1] * pMatrix.m[4];
    float b01 = pMatrix.m[0] * pMatrix.m[6] - pMatrix.m[2] * pMatrix.m[4];
    float b02 = pMatrix.m[0] * pMatrix.m[7] - pMatrix.m[3] * pMatrix.m[4];
    float b03 = pMatrix.m[1] * pMatrix.m[6] - pMatrix.m[2] * pMatrix.m[5];
    float b04 = pMatrix.m[1] * pMatrix.m[7] - pMatrix.m[3] * pMatrix.m[5];
    float b05 = pMatrix.m[2] * pMatrix.m[7] - pMatrix.m[3] * pMatrix.m[6];
    float b06 = pMatrix.m[8] * pMatrix.m[13] - pMatrix.m[9] * pMatrix.m[12];
    float b07 = pMatrix.m[8] * pMatrix.m[14] - pMatrix.m[10] * pMatrix.m[12];
    float b08 = pMatrix.m[8] * pMatrix.m[15] - pMatrix.m[11] * pMatrix.m[12];
    float b09 = pMatrix.m[9] * pMatrix.m[14] - pMatrix.m[10] * pMatrix.m[13];
    float b10 = pMatrix.m[9] * pMatrix.m[15] - pMatrix.m[11] * pMatrix.m[13];
    float b11 = pMatrix.m[10] * pMatrix.m[15] - pMatrix.m[11] * pMatrix.m[14];
    
    // Calculate the determinant (inlined to avoid double-caching)
    float determinant = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
    if (isInvertable != NULL) {
        *isInvertable = determinant != 0;
    }
    
    if (determinant == 0) {
        return GLKMatrix4Identity;
    }
    
    float invDet = 1.0f / determinant;
    GLKMatrix4 m;
    
    m.m[0] = (pMatrix.m[5] * b11 - pMatrix.m[6] * b10 + pMatrix.m[7] * b09) * invDet;
    m.m[1] = (-pMatrix.m[1] * b11 + pMatrix.m[2] * b10 - pMatrix.m[3] * b09) * invDet;
    m.m[2] = (pMatrix.m[13] * b05 - pMatrix.m[14] * b04 + pMatrix.m[15] * b03) * invDet;
    m.m[3] = (-pMatrix.m[9] * b05 + pMatrix.m[10] * b04 - pMatrix.m[11] * b03) * invDet;
    m.m[4] = (-pMatrix.m[4] * b11 + pMatrix.m[6] * b08 - pMatrix.m[7] * b07) * invDet;
    m.m[5] = (pMatrix.m[0] * b11 - pMatrix.m[2] * b08 + pMatrix.m[3] * b07) * invDet;
    m.m[6] = (-pMatrix.m[12] * b05 + pMatrix.m[14] * b02 - pMatrix.m[15] * b01) * invDet;
    m.m[7] = (pMatrix.m[8] * b05 - pMatrix.m[10] * b02 + pMatrix.m[11] * b01) * invDet;
    m.m[8] = (pMatrix.m[4] * b10 - pMatrix.m[5] * b08 + pMatrix.m[7] * b06) * invDet;
    m.m[9] = (-pMatrix.m[0] * b10 + pMatrix.m[1] * b08 - pMatrix.m[3] * b06) * invDet;
    m.m[10] = (pMatrix.m[12] * b04 - pMatrix.m[13] * b02 + pMatrix.m[15] * b00) * invDet;
    m.m[11] = (-pMatrix.m[8] * b04 + pMatrix.m[9] * b02 - pMatrix.m[11] * b00) * invDet;
    m.m[12] = (-pMatrix.m[4] * b09 + pMatrix.m[5] * b07 - pMatrix.m[6] * b06) * invDet;
    m.m[13] = (pMatrix.m[0] * b09 - pMatrix.m[1] * b07 + pMatrix.m[2] * b06) * invDet;
    m.m[14] = (-pMatrix.m[12] * b03 + pMatrix.m[13] * b01 - pMatrix.m[14] * b00) * invDet;
    m.m[15] = (pMatrix.m[8] * b03 - pMatrix.m[9] * b01 + pMatrix.m[10] * b00) * invDet;
    
    return m;
    */
    
    /*
    m[0]=m[6]*m[11]*m[13]-m[7]*m[10]*m[13]+m[7]*m[9]*m[14]-m[5]*m[11]*m[14]-m[6]*m[9]*m[15]+m[5]*m[10]*m[15];
    m[1]=m[3]*m[10]*m[13]-m[2]*m[11]*m[13]-m[3]*m[9]*m[14]+m[1]*m[11]*m[14]+m[2]*m[9]*m[15]-m[1]*m[10]*m[15];
    m[2]=m[2]*m[7]*m[13]-m[3]*m[6]*m[13]+m[3]*m[5]*m[14]-m[1]*m[7]*m[14]-m[2]*m[5]*m[15]+m[1]*m[6]*m[15];
    m[3]=m[3]*m[6]*m[9]-m[2]*m[7]*m[9]-m[3]*m[5]*m[10]+m[1]*m[7]*m[10]+m[2]*m[5]*m[11]-m[1]*m[6]*m[11];
    m[4]=m[7]*m[10]*m[12]-m[6]*m[11]*m[12]-m[7]*m[8]*m[14]+m[4]*m[11]*m[14]+m[6]*m[8]*m[15]-m[4]*m[10]*m[15];
    m[5]=m[2]*m[11]*m[12]-m[3]*m[10]*m[12]+m[3]*m[8]*m[14]-m[0]*m[11]*m[14]-m[2]*m[8]*m[15]+m[0]*m[10]*m[15];
    m[6]=m[3]*m[6]*m[12]-m[2]*m[7]*m[12]-m[3]*m[4]*m[14]+m[0]*m[7]*m[14]+m[2]*m[4]*m[15]-m[0]*m[6]*m[15];
    m[7]=m[2]*m[7]*m[8]-m[3]*m[6]*m[8]+m[3]*m[4]*m[10]-m[0]*m[7]*m[10]-m[2]*m[4]*m[11]+m[0]*m[6]*m[11];
    m[8]=m[5]*m[11]*m[12]-m[7]*m[9]*m[12]+m[7]*m[8]*m[13]-m[4]*m[11]*m[13]-m[5]*m[8]*m[15]+m[4]*m[9]*m[15];
    m[9]=m[3]*m[9]*m[12]-m[1]*m[11]*m[12]-m[3]*m[8]*m[13]+m[0]*m[11]*m[13]+m[1]*m[8]*m[15]-m[0]*m[9]*m[15];
    m[10]=m[1]*m[7]*m[12]-m[3]*m[5]*m[12]+m[3]*m[4]*m[13]-m[0]*m[7]*m[13]-m[1]*m[4]*m[15]+m[0]*m[5]*m[15];
    m[11]=m[3]*m[5]*m[8]-m[1]*m[7]*m[8]-m[3]*m[4]*m[9]+m[0]*m[7]*m[9]+m[1]*m[4]*m[11]-m[0]*m[5]*m[11];
    m[12]=m[6]*m[9]*m[12]-m[5]*m[10]*m[12]-m[6]*m[8]*m[13]+m[4]*m[10]*m[13]+m[5]*m[8]*m[14]-m[4]*m[9]*m[14];
    m[13]=m[1]*m[10]*m[12]-m[2]*m[9]*m[12]+m[2]*m[8]*m[13]-m[0]*m[10]*m[13]-m[1]*m[8]*m[14]+m[0]*m[9]*m[14];
    m[14]=m[2]*m[5]*m[12]-m[1]*m[6]*m[12]-m[2]*m[4]*m[13]+m[0]*m[6]*m[13]+m[1]*m[4]*m[14]-m[0]*m[5]*m[14];
    m[15]=m[1]*m[6]*m[8]-m[2]*m[5]*m[8]+m[2]*m[4]*m[9]-m[0]*m[6]*m[9]-m[1]*m[4]*m[10]+m[0]*m[5]*m[10];
    Scale(1/Determinant());
    */
}

void FMatrix::InvertAndTranspose() {
    bool aInvertable = false;
    FMatrix aInvertedMatrix = FMatrixInvert(*this, &aInvertable);
    if (aInvertable) {
        aInvertedMatrix = FMatrixTranspose(aInvertedMatrix);
        *this = aInvertedMatrix;
    } else {
        FMatrix aResult = FMatrixTranspose(*this);
        *this = aResult;
    }
}

float FMatrix::Determinant() {
    float aValue;
    aValue =
    m[3] * m[6] * m[9] * m[12]-m[2] * m[7] * m[9] * m[12]-m[3] * m[5] * m[10] * m[12]+m[1] * m[7] * m[10] * m[12]+
    m[2] * m[5] * m[11] * m[12]-m[1] * m[6] * m[11] * m[12]-m[3] * m[6] * m[8] * m[13]+m[2] * m[7] * m[8] * m[13]+
    m[3] * m[4] * m[10] * m[13]-m[0] * m[7] * m[10] * m[13]-m[2] * m[4] * m[11] * m[13]+m[0] * m[6] * m[11] * m[13]+
    m[3] * m[5] * m[8] * m[14]-m[1] * m[7] * m[8] * m[14]-m[3] * m[4] * m[9] * m[14]+m[0] * m[7] * m[9] * m[14]+
    m[1] * m[4] * m[11] * m[14]-m[0] * m[5] * m[11] * m[14]-m[2] * m[5] * m[8] * m[15]+m[1] * m[6] * m[8] * m[15]+
    m[2] * m[4] * m[9] * m[15]-m[0] * m[6] * m[9] * m[15]-m[1] * m[4] * m[10] * m[15]+m[0] * m[5] * m[10] * m[15];
    return aValue;
}

void FMatrix::OffsetPerspectiveCenter(float pOffsetX, float pOffsetY) {
    m[8] = pOffsetX / gDeviceWidth2;
    m[9] = -pOffsetY / gDeviceHeight2;
}

void FMatrix::Print() {
    int aIndex = 0;
    for (int n=0;n<4;n++) {
        Log("M[%d-%d] [%.2f %.2f %.2f %.2f]\n", 100, n, m[aIndex + 0], m[aIndex + 1], m[aIndex + 2], m[aIndex + 3]);
        aIndex += 4;
    }
}

/*
 
 FMatrix FMatrixCreate(float m00, float m01, float m02, float m03,
 float m10, float m11, float m12, float m13,
 float m20, float m21, float m22, float m23,
 float m30, float m31, float m32, float m33)
 {
 FMatrix m = { m00, m01, m02, m03,
 m10, m11, m12, m13,
 m20, m21, m22, m23,
 m30, m31, m32, m33 };
 return m;
 }
 
 FMatrix FMatrixCreateAndTranspose(float m00, float m01, float m02, float m03,
 float m10, float m11, float m12, float m13,
 float m20, float m21, float m22, float m23,
 float m30, float m31, float m32, float m33)
 {
 FMatrix m = { m00, m10, m20, m30,
 m01, m11, m21, m31,
 m02, m12, m22, m32,
 m03, m13, m23, m33 };
 return m;
 }
 
 FMatrix FMatrixCreateWithArray(float values[16])
 {
 FMatrix m = { values[0], values[1], values[2], values[3],
 values[4], values[5], values[6], values[7],
 values[8], values[9], values[10], values[11],
 values[12], values[13], values[14], values[15] };
 return m;
 }
 
 FMatrix FMatrixCreateTranslation(float tx, float ty, float tz)
 {
 FMatrix m;
 m.m[12] = tx;
 m.m[13] = ty;
 m.m[14] = tz;
 return m;
 }
 
 FMatrix FMatrixCreateScale(float sx, float sy, float sz)
 {
 FMatrix m;
 m.m[0] = sx;
 m.m[5] = sy;
 m.m[10] = sz;
 return m;
 }
 
 FMatrix FMatrixCreateRotation(float pRadians, float x, float y, float z)
 {
 float cos = cosf(pRadians);
 float cosp = 1.0f - cos;
 float sin = sinf(pRadians);
 
 float aDist = x * x + y * y + z * z;
 
 if(aDist > 0.01f)
 {
 aDist = sqrtf(aDist);
 x /= aDist;
 y /= aDist;
 z /= aDist;
 }
 
 FMatrix m = { cos + cosp * x * x,
 cosp * x * y + z * sin,
 cosp * x * z - y * sin,
 0.0f,
 cosp * x * y - z * sin,
 cos + cosp * y * y,
 cosp * y * z + x * sin,
 0.0f,
 cosp * x * z + y * sin,
 cosp * y * z - x * sin,
 cos + cosp * z * z,
 0.0f,
 0.0f,
 0.0f,
 0.0f,
 1.0f };
 
 return m;
 }
 
 FMatrix FMatrixCreateXRotation(float pRadians)
 {
 float cos = cosf(pRadians);
 float sin = sinf(pRadians);
 
 FMatrix m = { 1.0f, 0.0f, 0.0f, 0.0f,
 0.0f, cos, sin, 0.0f,
 0.0f, -sin, cos, 0.0f,
 0.0f, 0.0f, 0.0f, 1.0f };
 
 return m;
 }
 
 FMatrix FMatrixCreateYRotation(float pRadians)
 {
 float cos = cosf(pRadians);
 float sin = sinf(pRadians);
 
 FMatrix m = { cos, 0.0f, -sin, 0.0f,
 0.0f, 1.0f, 0.0f, 0.0f,
 sin, 0.0f, cos, 0.0f,
 0.0f, 0.0f, 0.0f, 1.0f };
 
 return m;
 }
 
 FMatrix FMatrixCreateZRotation(float pRadians)
 {
 float cos = cosf(pRadians);
 float sin = sinf(pRadians);
 
 FMatrix m = { cos, sin, 0.0f, 0.0f,
 -sin, cos, 0.0f, 0.0f,
 0.0f, 0.0f, 1.0f, 0.0f,
 0.0f, 0.0f, 0.0f, 1.0f };
 
 return m;
 }
 
 FMatrix FMatrixCreatePerspective(float fovyRadians, float aspect, float nearZ, float farZ)
 {
 float cotan = 1.0f / tanf(fovyRadians / 2.0f);
 
 FMatrix m = { cotan / aspect, 0.0f, 0.0f, 0.0f,
 0.0f, cotan, 0.0f, 0.0f,
 0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f,
 0.0f, 0.0f, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0f };
 
 return m;
 }
 
 FMatrix FMatrixCreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ)
 {
 float ral = right + left;
 float rsl = right - left;
 float tsb = top - bottom;
 float tab = top + bottom;
 float fan = farZ + nearZ;
 float fsn = farZ - nearZ;
 
 FMatrix m = { 2.0f * nearZ / rsl, 0.0f, 0.0f, 0.0f,
 0.0f, 2.0f * nearZ / tsb, 0.0f, 0.0f,
 ral / rsl, tab / tsb, -fan / fsn, -1.0f,
 0.0f, 0.0f, (-2.0f * farZ * nearZ) / fsn, 0.0f };
 
 return m;
 }
 
 FMatrix FMatrixCreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
 {
 float ral = right + left;
 float rsl = right - left;
 float tab = top + bottom;
 float tsb = top - bottom;
 float fan = farZ + nearZ;
 float fsn = farZ - nearZ;
 
 FMatrix m = { 2.0f / rsl, 0.0f, 0.0f, 0.0f,
 0.0f, 2.0f / tsb, 0.0f, 0.0f,
 0.0f, 0.0f, -2.0f / fsn, 0.0f,
 -ral / rsl, -tab / tsb, -fan / fsn, 1.0f };
 
 return m;
 }
 
 FMatrix FMatrixCreateLookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
 {
 float aNX = eyeX - centerX;
 float aNY = eyeY - centerY;
 float aNZ = eyeZ - centerZ;
 
 float aDist = aNX * aNX + aNY * aNY + aNZ * aNZ;
 
 if(aDist > 0.01f)
 {
 aDist = sqrtf(aDist);
 aNX /= aDist;
 aNY /= aDist;
 aNZ /= aDist;
 }
 
 float aUX = upY * aNZ - upZ * aNY;
 float aUY = upZ * aNX - upX * aNZ;
 float aUZ = upX * aNY - upY * aNX;
 
 aDist = aUX * aUX + aUY * aUY + aUZ * aUZ;
 if(aDist > 0.01f)
 {
 aDist = sqrtf(aDist);
 aUX /= aDist;
 aUY /= aDist;
 aUZ /= aDist;
 }
 
 float aVX = aNY * aUZ - aNZ * aUY;
 float aVY = aNZ * aUX - aNX * aUZ;
 float aVZ = aNX * aUY - aNY * aUX;
 
 FMatrix m = {aUX, aVX, aNX, 0.0f,
 aUY, aVY, aNY, 0.0f,
 aUZ, aVZ, aNZ, 0.0f,
 -aUX * eyeX + -aUY * eyeY + -aUZ * eyeZ,
 -aVX * eyeX + -aVY * eyeY + -aVZ * eyeZ,
 -aNX * eyeX + -aNY * eyeY + -aNZ * eyeZ,
 1.0f };
 
 return m;
 }
 
 FMatrix FMatrixTranspose(FMatrix pMatrix)
 {
 FMatrix m = { pMatrix.m[0], pMatrix.m[4], pMatrix.m[8], pMatrix.m[12],
 pMatrix.m[1], pMatrix.m[5], pMatrix.m[9], pMatrix.m[13],
 pMatrix.m[2], pMatrix.m[6], pMatrix.m[10], pMatrix.m[14],
 pMatrix.m[3], pMatrix.m[7], pMatrix.m[11], pMatrix.m[15] };
 return m;
 }
 
 FMatrix FMatrixMultiply(FMatrix pMatrixLeft, FMatrix pMatrixRight)
 {
 FMatrix m;
 
 m.m[0]  = pMatrixLeft.m[0] * pMatrixRight.m[0]  + pMatrixLeft.m[4] * pMatrixRight.m[1]  + pMatrixLeft.m[8] * pMatrixRight.m[2]   + pMatrixLeft.m[12] * pMatrixRight.m[3];
 m.m[4]  = pMatrixLeft.m[0] * pMatrixRight.m[4]  + pMatrixLeft.m[4] * pMatrixRight.m[5]  + pMatrixLeft.m[8] * pMatrixRight.m[6]   + pMatrixLeft.m[12] * pMatrixRight.m[7];
 m.m[8]  = pMatrixLeft.m[0] * pMatrixRight.m[8]  + pMatrixLeft.m[4] * pMatrixRight.m[9]  + pMatrixLeft.m[8] * pMatrixRight.m[10]  + pMatrixLeft.m[12] * pMatrixRight.m[11];
 m.m[12] = pMatrixLeft.m[0] * pMatrixRight.m[12] + pMatrixLeft.m[4] * pMatrixRight.m[13] + pMatrixLeft.m[8] * pMatrixRight.m[14]  + pMatrixLeft.m[12] * pMatrixRight.m[15];
 
 m.m[1]  = pMatrixLeft.m[1] * pMatrixRight.m[0]  + pMatrixLeft.m[5] * pMatrixRight.m[1]  + pMatrixLeft.m[9] * pMatrixRight.m[2]   + pMatrixLeft.m[13] * pMatrixRight.m[3];
 m.m[5]  = pMatrixLeft.m[1] * pMatrixRight.m[4]  + pMatrixLeft.m[5] * pMatrixRight.m[5]  + pMatrixLeft.m[9] * pMatrixRight.m[6]   + pMatrixLeft.m[13] * pMatrixRight.m[7];
 m.m[9]  = pMatrixLeft.m[1] * pMatrixRight.m[8]  + pMatrixLeft.m[5] * pMatrixRight.m[9]  + pMatrixLeft.m[9] * pMatrixRight.m[10]  + pMatrixLeft.m[13] * pMatrixRight.m[11];
 m.m[13] = pMatrixLeft.m[1] * pMatrixRight.m[12] + pMatrixLeft.m[5] * pMatrixRight.m[13] + pMatrixLeft.m[9] * pMatrixRight.m[14]  + pMatrixLeft.m[13] * pMatrixRight.m[15];
 
 m.m[2]  = pMatrixLeft.m[2] * pMatrixRight.m[0]  + pMatrixLeft.m[6] * pMatrixRight.m[1]  + pMatrixLeft.m[10] * pMatrixRight.m[2]  + pMatrixLeft.m[14] * pMatrixRight.m[3];
 m.m[6]  = pMatrixLeft.m[2] * pMatrixRight.m[4]  + pMatrixLeft.m[6] * pMatrixRight.m[5]  + pMatrixLeft.m[10] * pMatrixRight.m[6]  + pMatrixLeft.m[14] * pMatrixRight.m[7];
 m.m[10] = pMatrixLeft.m[2] * pMatrixRight.m[8]  + pMatrixLeft.m[6] * pMatrixRight.m[9]  + pMatrixLeft.m[10] * pMatrixRight.m[10] + pMatrixLeft.m[14] * pMatrixRight.m[11];
 m.m[14] = pMatrixLeft.m[2] * pMatrixRight.m[12] + pMatrixLeft.m[6] * pMatrixRight.m[13] + pMatrixLeft.m[10] * pMatrixRight.m[14] + pMatrixLeft.m[14] * pMatrixRight.m[15];
 
 m.m[3]  = pMatrixLeft.m[3] * pMatrixRight.m[0]  + pMatrixLeft.m[7] * pMatrixRight.m[1]  + pMatrixLeft.m[11] * pMatrixRight.m[2]  + pMatrixLeft.m[15] * pMatrixRight.m[3];
 m.m[7]  = pMatrixLeft.m[3] * pMatrixRight.m[4]  + pMatrixLeft.m[7] * pMatrixRight.m[5]  + pMatrixLeft.m[11] * pMatrixRight.m[6]  + pMatrixLeft.m[15] * pMatrixRight.m[7];
 m.m[11] = pMatrixLeft.m[3] * pMatrixRight.m[8]  + pMatrixLeft.m[7] * pMatrixRight.m[9]  + pMatrixLeft.m[11] * pMatrixRight.m[10] + pMatrixLeft.m[15] * pMatrixRight.m[11];
 m.m[15] = pMatrixLeft.m[3] * pMatrixRight.m[12] + pMatrixLeft.m[7] * pMatrixRight.m[13] + pMatrixLeft.m[11] * pMatrixRight.m[14] + pMatrixLeft.m[15] * pMatrixRight.m[15];
 
 return m;
 }
 
 FMatrix FMatrixAdd(FMatrix pMatrixLeft, FMatrix pMatrixRight)
 {
 FMatrix m;
 
 m.m[0] = pMatrixLeft.m[0] + pMatrixRight.m[0];
 m.m[1] = pMatrixLeft.m[1] + pMatrixRight.m[1];
 m.m[2] = pMatrixLeft.m[2] + pMatrixRight.m[2];
 m.m[3] = pMatrixLeft.m[3] + pMatrixRight.m[3];
 
 m.m[4] = pMatrixLeft.m[4] + pMatrixRight.m[4];
 m.m[5] = pMatrixLeft.m[5] + pMatrixRight.m[5];
 m.m[6] = pMatrixLeft.m[6] + pMatrixRight.m[6];
 m.m[7] = pMatrixLeft.m[7] + pMatrixRight.m[7];
 
 m.m[8] = pMatrixLeft.m[8] + pMatrixRight.m[8];
 m.m[9] = pMatrixLeft.m[9] + pMatrixRight.m[9];
 m.m[10] = pMatrixLeft.m[10] + pMatrixRight.m[10];
 m.m[11] = pMatrixLeft.m[11] + pMatrixRight.m[11];
 
 m.m[12] = pMatrixLeft.m[12] + pMatrixRight.m[12];
 m.m[13] = pMatrixLeft.m[13] + pMatrixRight.m[13];
 m.m[14] = pMatrixLeft.m[14] + pMatrixRight.m[14];
 m.m[15] = pMatrixLeft.m[15] + pMatrixRight.m[15];
 
 return m;
 }
 
 FMatrix FMatrixSubtract(FMatrix pMatrixLeft, FMatrix pMatrixRight)
 {
 FMatrix m;
 
 m.m[0] = pMatrixLeft.m[0] - pMatrixRight.m[0];
 m.m[1] = pMatrixLeft.m[1] - pMatrixRight.m[1];
 m.m[2] = pMatrixLeft.m[2] - pMatrixRight.m[2];
 m.m[3] = pMatrixLeft.m[3] - pMatrixRight.m[3];
 
 m.m[4] = pMatrixLeft.m[4] - pMatrixRight.m[4];
 m.m[5] = pMatrixLeft.m[5] - pMatrixRight.m[5];
 m.m[6] = pMatrixLeft.m[6] - pMatrixRight.m[6];
 m.m[7] = pMatrixLeft.m[7] - pMatrixRight.m[7];
 
 m.m[8] = pMatrixLeft.m[8] - pMatrixRight.m[8];
 m.m[9] = pMatrixLeft.m[9] - pMatrixRight.m[9];
 m.m[10] = pMatrixLeft.m[10] - pMatrixRight.m[10];
 m.m[11] = pMatrixLeft.m[11] - pMatrixRight.m[11];
 
 m.m[12] = pMatrixLeft.m[12] - pMatrixRight.m[12];
 m.m[13] = pMatrixLeft.m[13] - pMatrixRight.m[13];
 m.m[14] = pMatrixLeft.m[14] - pMatrixRight.m[14];
 m.m[15] = pMatrixLeft.m[15] - pMatrixRight.m[15];
 
 return m;
 }
 
 FMatrix FMatrixTranslate(FMatrix pMatrix, float tx, float ty, float tz)
 {
 FMatrix m = { pMatrix.m[0], pMatrix.m[1], pMatrix.m[2], pMatrix.m[3],
 pMatrix.m[4], pMatrix.m[5], pMatrix.m[6], pMatrix.m[7],
 pMatrix.m[8], pMatrix.m[9], pMatrix.m[10], pMatrix.m[11],
 pMatrix.m[0] * tx + pMatrix.m[4] * ty + pMatrix.m[8] * tz + pMatrix.m[12],
 pMatrix.m[1] * tx + pMatrix.m[5] * ty + pMatrix.m[9] * tz + pMatrix.m[13],
 pMatrix.m[2] * tx + pMatrix.m[6] * ty + pMatrix.m[10] * tz + pMatrix.m[14],
 pMatrix.m[15] };
 return m;
 }
 
 FMatrix FMatrixScale(FMatrix pMatrix, float sx, float sy, float sz)
 {
 FMatrix m = { pMatrix.m[0] * sx, pMatrix.m[1] * sx, pMatrix.m[2] * sx, pMatrix.m[3] * sx,
 pMatrix.m[4] * sy, pMatrix.m[5] * sy, pMatrix.m[6] * sy, pMatrix.m[7] * sy,
 pMatrix.m[8] * sz, pMatrix.m[9] * sz, pMatrix.m[10] * sz, pMatrix.m[11] * sz,
 pMatrix.m[12], pMatrix.m[13], pMatrix.m[14], pMatrix.m[15] };
 return m;
 }
 
 FMatrix FMatrixRotate(FMatrix pMatrix, float pRadians, float x, float y, float z)
 {
 FMatrix rm = FMatrixCreateRotation(pRadians, x, y, z);
 return FMatrixMultiply(pMatrix, rm);
 }
 
 FMatrix FMatrixRotateX(FMatrix pMatrix, float pRadians)
 {
 FMatrix rm = FMatrixCreateXRotation(pRadians);
 return FMatrixMultiply(pMatrix, rm);
 }
 
 FMatrix FMatrixRotateY(FMatrix pMatrix, float pRadians)
 {
 FMatrix rm = FMatrixCreateYRotation(pRadians);
 return FMatrixMultiply(pMatrix, rm);
 }
 
 FMatrix FMatrixRotateZ(FMatrix pMatrix, float pRadians)
 {
 FMatrix rm = FMatrixCreateZRotation(pRadians);
 return FMatrixMultiply(pMatrix, rm);
 }
 
 */











FMatrix FMatrixCreate(float m00, float m01, float m02, float m03,
                      float m10, float m11, float m12, float m13,
                      float m20, float m21, float m22, float m23,
                      float m30, float m31, float m32, float m33)
{
    FMatrix m;
    
    
    m.m[0 ] = m00;
    m.m[1 ] = m01;
    m.m[2 ] = m02;
    m.m[3 ] = m03;
    
    m.m[4 ] = m10;
    m.m[5 ] = m11;
    m.m[6 ] = m12;
    m.m[7 ] = m13;
    
    m.m[8 ] = m20;
    m.m[9 ] = m21;
    m.m[10] = m22;
    m.m[11] = m23;
    
    m.m[12] = m30;
    m.m[13] = m31;
    m.m[14] = m32;
    m.m[15] = m33;
    
    return m;
}

FMatrix FMatrixCreateAndTranspose(float m00, float m01, float m02, float m03,
                                  float m10, float m11, float m12, float m13,
                                  float m20, float m21, float m22, float m23,
                                  float m30, float m31, float m32, float m33)
{
    FMatrix m;
    
    m.m[0 ] = m00;
    m.m[1 ] = m10;
    m.m[2 ] = m20;
    m.m[3 ] = m30;
    
    m.m[4 ] = m01;
    m.m[5 ] = m11;
    m.m[6 ] = m21;
    m.m[7 ] = m31;
    
    m.m[8 ] = m02;
    m.m[9 ] = m12;
    m.m[10] = m22;
    m.m[11] = m32;
    
    m.m[12] = m03;
    m.m[13] = m13;
    m.m[14] = m23;
    m.m[15] = m33;
    
    return m;
}


FMatrix FMatrixCreateWithArray(float values[16])
{
    FMatrix m;
    
    m.m[0 ] = values[0 ];
    m.m[1 ] = values[1 ];
    m.m[2 ] = values[2 ];
    m.m[3 ] = values[3 ];
    
    m.m[4 ] = values[4 ];
    m.m[5 ] = values[5 ];
    m.m[6 ] = values[6 ];
    m.m[7 ] = values[7 ];
    
    m.m[8 ] = values[8 ];
    m.m[9 ] = values[9 ];
    m.m[10] = values[10];
    m.m[11] = values[11];
    
    m.m[12] = values[12];
    m.m[13] = values[13];
    m.m[14] = values[14];
    m.m[15] = values[15];
    
    return m;
}

FMatrix FMatrixCreateTranslation(float tx, float ty, float tz)
{
    FMatrix m;
    m.m[12] = tx;
    m.m[13] = ty;
    m.m[14] = tz;
    return m;
}

FMatrix FMatrixCreateScale(float sx, float sy, float sz)
{
    FMatrix m;
    m.m[0] = sx;
    m.m[5] = sy;
    m.m[10] = sz;
    return m;
}

FMatrix FMatrixCreateRotation(float pRadians, float pX, float pY, float pZ) {
    float aCos = cosf(pRadians);
    float aCosInv = 1.0f - aCos;
    float aSin = sinf(pRadians);
    
    float aDist = pX * pX + pY * pY + pZ * pZ;
    
    if(aDist > 0.01f)
    {
        aDist = sqrtf(aDist);
        pX /= aDist;
        pY /= aDist;
        pZ /= aDist;
    }
    
    float aCosInvX = aCosInv * pX;
    float aCosInvY = aCosInv * pY;
    float aCosInvXY = aCosInvX * pY;
    float aCosInvXZ = aCosInvX * pZ;
    float aCosInvYZ = aCosInvY * pZ;
    float aSinX = pX * aSin;
    float aSinY = pY * aSin;
    float aSinZ = pZ * aSin;
    
    FMatrix m = FMatrixCreate(aCos + aCosInvX * pX,
                                aCosInvXY + aSinZ,
                                aCosInvXZ - aSinY,
                                0.0f,
                                aCosInvXY - aSinZ,
                                aCos + aCosInvY * pY,
                                aCosInvYZ + aSinX,
                                0.0f,
                                aCosInvXZ + aSinY,
                                aCosInvYZ - aSinX,
                                aCos + aCosInv * pZ * pZ,
                                0.0f,
                                0.0f,
                                0.0f,
                                0.0f,
                                1.0f );
    
    return m;
}

FMatrix FMatrixCreateXRotation(float pRadians) {
    
    float aCos = cosf(pRadians);
    float aSin = sinf(pRadians);
    
    FMatrix aResult = FMatrixCreate(1.0f, 0.0f, 0.0f, 0.0f,
                              0.0f, aCos, aSin, 0.0f,
                              0.0f, -aSin, aCos, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f );
    
    return aResult;
}

FMatrix FMatrixCreateYRotation(float pRadians) {
    
    float aCos = cosf(pRadians);
    float aSin = sinf(pRadians);
    
    FMatrix aResult = FMatrixCreate(aCos, 0.0f, -aSin, 0.0f,
                              0.0f, 1.0f, 0.0f, 0.0f,
                              aSin, 0.0f, aCos, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f );
    
    return aResult;
}

FMatrix FMatrixCreateZRotation(float pRadians) {
    
    float aCos = cosf(pRadians);
    float aSin = sinf(pRadians);
    
    FMatrix aResult = FMatrixCreate(aCos, aSin, 0.0f, 0.0f,
                              -aSin, aCos, 0.0f, 0.0f,
                              0.0f, 0.0f, 1.0f, 0.0f,
                              0.0f, 0.0f, 0.0f, 1.0f);
    
    return aResult;
}

FMatrix FMatrixCreatePerspective(float fovyRadians, float aspect, float nearZ, float farZ)
{
    float cotan = 1.0f / tanf(fovyRadians / 2.0f);
    
    FMatrix m = FMatrixCreate(cotan / aspect, 0.0f, 0.0f, 0.0f,
                              0.0f, cotan, 0.0f, 0.0f,
                              0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f,
                              0.0f, 0.0f, (2.0f * farZ * nearZ) / (nearZ - farZ), 0.0f );
    
    
    return m;
}

FMatrix FMatrixCreateFrustum(float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float ral = right + left;
    float rsl = right - left;
    float tsb = top - bottom;
    float tab = top + bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    
    FMatrix m = FMatrixCreate(2.0f * nearZ / rsl, 0.0f, 0.0f, 0.0f,
                              0.0f, 2.0f * nearZ / tsb, 0.0f, 0.0f,
                              ral / rsl, tab / tsb, -fan / fsn, -1.0f,
                              0.0f, 0.0f, (-2.0f * farZ * nearZ) / fsn, 0.0f);
    
    
    return m;
}

FMatrix FMatrixCreateOrtho(float left, float right, float bottom, float top, float nearZ, float farZ) {
    float ral = right + left;
    float rsl = right - left;
    float tab = top + bottom;
    float tsb = top - bottom;
    float fan = farZ + nearZ;
    float fsn = farZ - nearZ;
    FMatrix m = FMatrixCreate(2.0f / rsl, 0.0f, 0.0f, 0.0f,
                              0.0f, 2.0f / tsb, 0.0f, 0.0f,
                              0.0f, 0.0f, -2.0f / fsn, 0.0f,
                              -ral / rsl, -tab / tsb, -fan / fsn, 1.0f);
    return m;
}

FMatrix FMatrixCreateLookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float aCenterZ, float pUpX, float pUpY, float pUpZ) {
    float aNX = eyeX - centerX;
    float aNY = eyeY - centerY;
    float aNZ = eyeZ - aCenterZ;
    float aDist = aNX * aNX + aNY * aNY + aNZ * aNZ;
    if (aDist > 0.01f) {
        aDist = sqrtf(aDist);
        aNX /= aDist;
        aNY /= aDist;
        aNZ /= aDist;
    }
    //float aUX = upY * aNZ - pUpZ * aNY;
    //float aUY = upZ * aNX - aUpX * aNZ;
    //float aUZ = aUpX * aNY - pUpY * aNX;
    
    
    //Left-Handed...
    float aUX = pUpY * aNZ - pUpZ * aNY;
    float aUY = pUpZ * aNX - pUpX * aNZ;
    float aUZ = pUpX * aNY - pUpY * aNX;
    
    //Right-Handed
    //float aUX = pUpY * aNZ - pUpZ * aNY;
    //float aUY = pUpX * aNZ - pUpZ * aNX;
    //float aUZ = pUpX * aNY - pUpY * aNX;
    
    aDist = aUX * aUX + aUY * aUY + aUZ * aUZ;
    if (aDist > 0.01f) {
        aDist = sqrtf(aDist);
        aUX /= aDist;
        aUY /= aDist;
        aUZ /= aDist;
    }
    
    float aVX = aNY * aUZ - aNZ * aUY;
    float aVY = aNZ * aUX - aNX * aUZ;
    float aVZ = aNX * aUY - aNY * aUX;
    
    /*
     vec3 zaxis = normal(eye - target);    // The "forward" vector.
     vec3 xaxis = normal(cross(up, zaxis));// The "right" vector.
     vec3 yaxis = cross(zaxis, xaxis);     // The "up" vector.
     
     // Create a 4x4 orientation pMatrix from the right, up, and forward vectors
     // This is transposed which is equivalent to performing an inverse
     // if the pMatrix is orthonormalized (in this case, it is).
     mat4 orientation = {
     vec4( xaxis.x, yaxis.x, zaxis.x, 0 ),
     vec4( xaxis.y, yaxis.y, zaxis.y, 0 ),
     vec4( xaxis.z, yaxis.z, zaxis.z, 0 ),
     vec4(   0,       0,       0,     1 )
     };
     
     // Create a 4x4 translation pMatrix.
     // The eye position is negated which is equivalent
     // to the inverse of the translation pMatrix.
     // T(v)^-1 == T(-v)
     mat4 translation = {
     vec4(   1,      0,      0,   0 ),
     vec4(   0,      1,      0,   0 ),
     vec4(   0,      0,      1,   0 ),
     vec4(-eye.x, -eye.y, -eye.z, 1 )
     };
     
     // Combine the orientation and translation to compute
     // the final view pMatrix. Note that the order of
     // multiplication is reversed because the matrices
     // are already inverted.
     return ( orientation * translation );
     */
    
    
    FMatrix m = FMatrixCreate(aUX, aVX, aNX, 0.0f,
                              aUY, aVY, aNY, 0.0f,
                              aUZ, aVZ, aNZ, 0.0f,
                              -aUX * eyeX + -aUY * eyeY + -aUZ * eyeZ,
                              -aVX * eyeX + -aVY * eyeY + -aVZ * eyeZ,
                              -aNX * eyeX + -aNY * eyeY + -aNZ * eyeZ,
                              1.0f );
    
    return m;
}

FMatrix FMatrixTranspose(FMatrix pMatrix)
{
    
    FMatrix m = FMatrixCreate(pMatrix.m[0], pMatrix.m[4], pMatrix.m[8], pMatrix.m[12],
                              pMatrix.m[1], pMatrix.m[5], pMatrix.m[9], pMatrix.m[13],
                              pMatrix.m[2], pMatrix.m[6], pMatrix.m[10], pMatrix.m[14],
                              pMatrix.m[3], pMatrix.m[7], pMatrix.m[11], pMatrix.m[15]);
    return m;
}

FMatrix FMatrixInvert(FMatrix pMatrix, bool *pInvertable) {
    
    // m = transposed cofactor pMatrix
    float c02070306 = pMatrix.m[2] * pMatrix.m[7] - pMatrix.m[3] * pMatrix.m[6];
    float c02110310 = pMatrix.m[2] * pMatrix.m[11] - pMatrix.m[3] * pMatrix.m[10];
    float c02150314 = pMatrix.m[2] * pMatrix.m[15] - pMatrix.m[3] * pMatrix.m[14];
    float c06110710 = pMatrix.m[6] * pMatrix.m[11] - pMatrix.m[7] * pMatrix.m[10];
    float c06150714 = pMatrix.m[6] * pMatrix.m[15] - pMatrix.m[7] * pMatrix.m[14];
    float c10151114 = pMatrix.m[10] * pMatrix.m[15] - pMatrix.m[11] * pMatrix.m[14];
    FMatrix m = FMatrixCreate(
        pMatrix.m[5] * c10151114 + pMatrix.m[9] * -c06150714 + pMatrix.m[13] * c06110710, // c0
        -pMatrix.m[1] * c10151114 + pMatrix.m[9] * c02150314 - pMatrix.m[13] * c02110310, // c4
        pMatrix.m[1] * c06150714 - pMatrix.m[5] * c02150314 + pMatrix.m[13] * c02070306, // c8
        -pMatrix.m[1] * c06110710 + pMatrix.m[5] * c02110310 - pMatrix.m[9] * c02070306, // c12
        0.0f, // c1
        0.0f, // c5
        0.0f, // c9
        0.0f, // c13
        0.0f, // c2
        0.0f, // c6
        0.0f, // c10
        0.0f, // c14
        0.0f, // c3
        0.0f, // c7
        0.0f, // c11
        0.0f // c15
    );
    // d = pMatrix determinant
    float d = m.m[0] * pMatrix.m[0] + m.m[1] * pMatrix.m[4] + m.m[2] * pMatrix.m[8] + m.m[3] * pMatrix.m[12];
    if (fabsf(d) < FLOAT_EPSILON) {
        if (pInvertable) *pInvertable = false;
        FMatrix aResult;
        return aResult;
    }
    if (pInvertable) *pInvertable = true;
    // d = 1 / pMatrix determinant
    d = 1.0f / d;
    // m = transposed inverse pMatrix = transposed cofactor pMatrix * d
    float c01070305 = pMatrix.m[1] * pMatrix.m[7] - pMatrix.m[3] * pMatrix.m[5];
    float c01110309 = pMatrix.m[1] * pMatrix.m[11] - pMatrix.m[3] * pMatrix.m[9];
    float c01150313 = pMatrix.m[1] * pMatrix.m[15] - pMatrix.m[3] * pMatrix.m[13];
    float c05110709 = pMatrix.m[5] * pMatrix.m[11] - pMatrix.m[7] * pMatrix.m[9];
    float c05150713 = pMatrix.m[5] * pMatrix.m[15] - pMatrix.m[7] * pMatrix.m[13];
    float c09151113 = pMatrix.m[9] * pMatrix.m[15] - pMatrix.m[11] * pMatrix.m[13];
    
    float c01060205 = pMatrix.m[1] * pMatrix.m[6] - pMatrix.m[2] * pMatrix.m[5];
    float c01100209 = pMatrix.m[1] * pMatrix.m[10] - pMatrix.m[2] * pMatrix.m[9];
    float c01140213 = pMatrix.m[1] * pMatrix.m[14] - pMatrix.m[2] * pMatrix.m[13];
    float c05100609 = pMatrix.m[5] * pMatrix.m[10] - pMatrix.m[6] * pMatrix.m[9];
    float c05140613 = pMatrix.m[5] * pMatrix.m[14] - pMatrix.m[6] * pMatrix.m[13];
    float c09141013 = pMatrix.m[9] * pMatrix.m[14] - pMatrix.m[10] * pMatrix.m[13];
    
    m.m[0] *= d; // c0
    m.m[1] *= d; // c4
    m.m[2] *= d; // c8
    m.m[3] *= d; // c12
    m.m[4] = (-pMatrix.m[4] * c10151114 + pMatrix.m[8] * c06150714 - pMatrix.m[12] * c06110710) * d; // c1
    m.m[5] = (pMatrix.m[0] * c10151114 - pMatrix.m[8] * c02150314 + pMatrix.m[12] * c02110310) * d; // c5
    m.m[6] = (-pMatrix.m[0] * c06150714 + pMatrix.m[4] * c02150314 - pMatrix.m[12] * c02070306) * d; // c9
    m.m[7] = (pMatrix.m[0] * c06110710 - pMatrix.m[4] * c02110310 + pMatrix.m[8] * c02070306) * d; // c13
    m.m[8] = (pMatrix.m[4] * c09151113 - pMatrix.m[8] * c05150713 + pMatrix.m[12] * c05110709) * d; // c2
    m.m[9] = (-pMatrix.m[0] * c09151113 + pMatrix.m[8] * c01150313 - pMatrix.m[12] * c01110309) * d; // c6
    m.m[10] = (pMatrix.m[0] * c05150713 - pMatrix.m[4] * c01150313 + pMatrix.m[12] * c01070305) * d; // c10
    m.m[11] = (-pMatrix.m[0] * c05110709 + pMatrix.m[4] * c01110309 - pMatrix.m[8] * c01070305) * d; // c14
    m.m[12] = (-pMatrix.m[4] * c09141013 + pMatrix.m[8] * c05140613 - pMatrix.m[12] * c05100609) * d; // c3
    m.m[13] = (pMatrix.m[0] * c09141013 - pMatrix.m[8] * c01140213 + pMatrix.m[12] * c01100209) * d; // c7
    m.m[14] = (-pMatrix.m[0] * c05140613 + pMatrix.m[4] * c01140213 - pMatrix.m[12] * c01060205) * d; // c11
    m.m[15] = (pMatrix.m[0] * c05100609 - pMatrix.m[4] * c01100209 + pMatrix.m[8] * c01060205) * d; // c15
    return m;
}

FMatrix FMatrixMultiply(FMatrix pMatrixLeft, FMatrix pMatrixRight)
{
    
    /*
     #if defined(__ARM_NEON__)
     
     float32x4x4_t iMatrixRight =
     {{
     {pMatrixRight.m[0], pMatrixRight.m[1], pMatrixRight.m[2], pMatrixRight.m[3]},
     {pMatrixRight.m[4], pMatrixRight.m[5], pMatrixRight.m[6], pMatrixRight.m[7]},
     {pMatrixRight.m[8], pMatrixRight.m[9], pMatrixRight.m[10], pMatrixRight.m[11]},
     {pMatrixRight.m[12], pMatrixRight.m[13], pMatrixRight.m[14], pMatrixRight.m[15]}
     }};
     
     float32x4x4_t iMatrixLeft =
     {{
     {pMatrixLeft.m[0], pMatrixLeft.m[1], pMatrixLeft.m[2], pMatrixLeft.m[3]},
     {pMatrixLeft.m[4], pMatrixLeft.m[5], pMatrixLeft.m[6], pMatrixLeft.m[7]},
     {pMatrixLeft.m[8], pMatrixLeft.m[9], pMatrixLeft.m[10], pMatrixLeft.m[11]},
     {pMatrixLeft.m[12], pMatrixLeft.m[13], pMatrixLeft.m[14], pMatrixLeft.m[15]}
     }};
     
     float32x4x4_t m;
     
     m.val[0] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[0], 0));
     m.val[1] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[1], 0));
     m.val[2] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[2], 0));
     m.val[3] = vmulq_n_f32(iMatrixLeft.val[0], vgetq_lane_f32(iMatrixRight.val[3], 0));
     
     m.val[0] = vmlaq_n_f32(m.val[0], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[0], 1));
     m.val[1] = vmlaq_n_f32(m.val[1], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[1], 1));
     m.val[2] = vmlaq_n_f32(m.val[2], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[2], 1));
     m.val[3] = vmlaq_n_f32(m.val[3], iMatrixLeft.val[1], vgetq_lane_f32(iMatrixRight.val[3], 1));
     
     m.val[0] = vmlaq_n_f32(m.val[0], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[0], 2));
     m.val[1] = vmlaq_n_f32(m.val[1], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[1], 2));
     m.val[2] = vmlaq_n_f32(m.val[2], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[2], 2));
     m.val[3] = vmlaq_n_f32(m.val[3], iMatrixLeft.val[2], vgetq_lane_f32(iMatrixRight.val[3], 2));
     
     m.val[0] = vmlaq_n_f32(m.val[0], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[0], 3));
     m.val[1] = vmlaq_n_f32(m.val[1], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[1], 3));
     m.val[2] = vmlaq_n_f32(m.val[2], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[2], 3));
     m.val[3] = vmlaq_n_f32(m.val[3], iMatrixLeft.val[3], vgetq_lane_f32(iMatrixRight.val[3], 3));
     
     return *(FMatrix *)&(m);
     
     #else
     */
    
    
    FMatrix aMatrix;
    
    aMatrix.m[0]  = pMatrixLeft.m[0] * pMatrixRight.m[0]  + pMatrixLeft.m[4] * pMatrixRight.m[1]  + pMatrixLeft.m[8] * pMatrixRight.m[2]   + pMatrixLeft.m[12] * pMatrixRight.m[3];
    aMatrix.m[4]  = pMatrixLeft.m[0] * pMatrixRight.m[4]  + pMatrixLeft.m[4] * pMatrixRight.m[5]  + pMatrixLeft.m[8] * pMatrixRight.m[6]   + pMatrixLeft.m[12] * pMatrixRight.m[7];
    aMatrix.m[8]  = pMatrixLeft.m[0] * pMatrixRight.m[8]  + pMatrixLeft.m[4] * pMatrixRight.m[9]  + pMatrixLeft.m[8] * pMatrixRight.m[10]  + pMatrixLeft.m[12] * pMatrixRight.m[11];
    aMatrix.m[12] = pMatrixLeft.m[0] * pMatrixRight.m[12] + pMatrixLeft.m[4] * pMatrixRight.m[13] + pMatrixLeft.m[8] * pMatrixRight.m[14]  + pMatrixLeft.m[12] * pMatrixRight.m[15];
    
    aMatrix.m[1]  = pMatrixLeft.m[1] * pMatrixRight.m[0]  + pMatrixLeft.m[5] * pMatrixRight.m[1]  + pMatrixLeft.m[9] * pMatrixRight.m[2]   + pMatrixLeft.m[13] * pMatrixRight.m[3];
    aMatrix.m[5]  = pMatrixLeft.m[1] * pMatrixRight.m[4]  + pMatrixLeft.m[5] * pMatrixRight.m[5]  + pMatrixLeft.m[9] * pMatrixRight.m[6]   + pMatrixLeft.m[13] * pMatrixRight.m[7];
    aMatrix.m[9]  = pMatrixLeft.m[1] * pMatrixRight.m[8]  + pMatrixLeft.m[5] * pMatrixRight.m[9]  + pMatrixLeft.m[9] * pMatrixRight.m[10]  + pMatrixLeft.m[13] * pMatrixRight.m[11];
    aMatrix.m[13] = pMatrixLeft.m[1] * pMatrixRight.m[12] + pMatrixLeft.m[5] * pMatrixRight.m[13] + pMatrixLeft.m[9] * pMatrixRight.m[14]  + pMatrixLeft.m[13] * pMatrixRight.m[15];
    
    aMatrix.m[2]  = pMatrixLeft.m[2] * pMatrixRight.m[0]  + pMatrixLeft.m[6] * pMatrixRight.m[1]  + pMatrixLeft.m[10] * pMatrixRight.m[2]  + pMatrixLeft.m[14] * pMatrixRight.m[3];
    aMatrix.m[6]  = pMatrixLeft.m[2] * pMatrixRight.m[4]  + pMatrixLeft.m[6] * pMatrixRight.m[5]  + pMatrixLeft.m[10] * pMatrixRight.m[6]  + pMatrixLeft.m[14] * pMatrixRight.m[7];
    aMatrix.m[10] = pMatrixLeft.m[2] * pMatrixRight.m[8]  + pMatrixLeft.m[6] * pMatrixRight.m[9]  + pMatrixLeft.m[10] * pMatrixRight.m[10] + pMatrixLeft.m[14] * pMatrixRight.m[11];
    aMatrix.m[14] = pMatrixLeft.m[2] * pMatrixRight.m[12] + pMatrixLeft.m[6] * pMatrixRight.m[13] + pMatrixLeft.m[10] * pMatrixRight.m[14] + pMatrixLeft.m[14] * pMatrixRight.m[15];
    
    aMatrix.m[3]  = pMatrixLeft.m[3] * pMatrixRight.m[0]  + pMatrixLeft.m[7] * pMatrixRight.m[1]  + pMatrixLeft.m[11] * pMatrixRight.m[2]  + pMatrixLeft.m[15] * pMatrixRight.m[3];
    aMatrix.m[7]  = pMatrixLeft.m[3] * pMatrixRight.m[4]  + pMatrixLeft.m[7] * pMatrixRight.m[5]  + pMatrixLeft.m[11] * pMatrixRight.m[6]  + pMatrixLeft.m[15] * pMatrixRight.m[7];
    aMatrix.m[11] = pMatrixLeft.m[3] * pMatrixRight.m[8]  + pMatrixLeft.m[7] * pMatrixRight.m[9]  + pMatrixLeft.m[11] * pMatrixRight.m[10] + pMatrixLeft.m[15] * pMatrixRight.m[11];
    aMatrix.m[15] = pMatrixLeft.m[3] * pMatrixRight.m[12] + pMatrixLeft.m[7] * pMatrixRight.m[13] + pMatrixLeft.m[11] * pMatrixRight.m[14] + pMatrixLeft.m[15] * pMatrixRight.m[15];
    
    return aMatrix;
    
    //#endif
    
}

FMatrix FMatrixAdd(FMatrix pMatrixLeft, FMatrix pMatrixRight)
{
    FMatrix m;
    
    m.m[0] = pMatrixLeft.m[0] + pMatrixRight.m[0];
    m.m[1] = pMatrixLeft.m[1] + pMatrixRight.m[1];
    m.m[2] = pMatrixLeft.m[2] + pMatrixRight.m[2];
    m.m[3] = pMatrixLeft.m[3] + pMatrixRight.m[3];
    
    m.m[4] = pMatrixLeft.m[4] + pMatrixRight.m[4];
    m.m[5] = pMatrixLeft.m[5] + pMatrixRight.m[5];
    m.m[6] = pMatrixLeft.m[6] + pMatrixRight.m[6];
    m.m[7] = pMatrixLeft.m[7] + pMatrixRight.m[7];
    
    m.m[8] = pMatrixLeft.m[8] + pMatrixRight.m[8];
    m.m[9] = pMatrixLeft.m[9] + pMatrixRight.m[9];
    m.m[10] = pMatrixLeft.m[10] + pMatrixRight.m[10];
    m.m[11] = pMatrixLeft.m[11] + pMatrixRight.m[11];
    
    m.m[12] = pMatrixLeft.m[12] + pMatrixRight.m[12];
    m.m[13] = pMatrixLeft.m[13] + pMatrixRight.m[13];
    m.m[14] = pMatrixLeft.m[14] + pMatrixRight.m[14];
    m.m[15] = pMatrixLeft.m[15] + pMatrixRight.m[15];
    
    return m;
}

FMatrix FMatrixSubtract(FMatrix pMatrixLeft, FMatrix pMatrixRight)
{
    FMatrix m;
    
    m.m[0] = pMatrixLeft.m[0] - pMatrixRight.m[0];
    m.m[1] = pMatrixLeft.m[1] - pMatrixRight.m[1];
    m.m[2] = pMatrixLeft.m[2] - pMatrixRight.m[2];
    m.m[3] = pMatrixLeft.m[3] - pMatrixRight.m[3];
    
    m.m[4] = pMatrixLeft.m[4] - pMatrixRight.m[4];
    m.m[5] = pMatrixLeft.m[5] - pMatrixRight.m[5];
    m.m[6] = pMatrixLeft.m[6] - pMatrixRight.m[6];
    m.m[7] = pMatrixLeft.m[7] - pMatrixRight.m[7];
    
    m.m[8] = pMatrixLeft.m[8] - pMatrixRight.m[8];
    m.m[9] = pMatrixLeft.m[9] - pMatrixRight.m[9];
    m.m[10] = pMatrixLeft.m[10] - pMatrixRight.m[10];
    m.m[11] = pMatrixLeft.m[11] - pMatrixRight.m[11];
    
    m.m[12] = pMatrixLeft.m[12] - pMatrixRight.m[12];
    m.m[13] = pMatrixLeft.m[13] - pMatrixRight.m[13];
    m.m[14] = pMatrixLeft.m[14] - pMatrixRight.m[14];
    m.m[15] = pMatrixLeft.m[15] - pMatrixRight.m[15];
    
    return m;
}

FMatrix FMatrixTranslate(FMatrix pMatrix, float tx, float ty, float tz)
{
    FMatrix m = FMatrixCreate(pMatrix.m[0], pMatrix.m[1], pMatrix.m[2], pMatrix.m[3],
                              pMatrix.m[4], pMatrix.m[5], pMatrix.m[6], pMatrix.m[7],
                              pMatrix.m[8], pMatrix.m[9], pMatrix.m[10], pMatrix.m[11],
                              pMatrix.m[0] * tx + pMatrix.m[4] * ty + pMatrix.m[8] * tz + pMatrix.m[12],
                              pMatrix.m[1] * tx + pMatrix.m[5] * ty + pMatrix.m[9] * tz + pMatrix.m[13],
                              pMatrix.m[2] * tx + pMatrix.m[6] * ty + pMatrix.m[10] * tz + pMatrix.m[14],
                              pMatrix.m[15]);
    return m;
}

FMatrix FMatrixScale(FMatrix pMatrix, float sx, float sy, float sz)
{
    FMatrix m = FMatrixCreate(pMatrix.m[0] * sx, pMatrix.m[1] * sx, pMatrix.m[2] * sx, pMatrix.m[3] * sx,
                              pMatrix.m[4] * sy, pMatrix.m[5] * sy, pMatrix.m[6] * sy, pMatrix.m[7] * sy,
                              pMatrix.m[8] * sz, pMatrix.m[9] * sz, pMatrix.m[10] * sz, pMatrix.m[11] * sz,
                              pMatrix.m[12], pMatrix.m[13], pMatrix.m[14], pMatrix.m[15]);
    return m;
}

FMatrix FMatrixRotate(FMatrix pMatrix, float pRadians, float x, float y, float z) {
    FMatrix aRotationMatrix = FMatrixCreateRotation(pRadians, x, y, z);
    return FMatrixMultiply(pMatrix, aRotationMatrix);
}

FMatrix FMatrixRotateX(FMatrix pMatrix, float pRadians) {
    FMatrix aRotationMatrix = FMatrixCreateXRotation(pRadians);
    return FMatrixMultiply(pMatrix, aRotationMatrix);
}

FMatrix FMatrixRotateY(FMatrix pMatrix, float pRadians) {
    FMatrix aRotationMatrix = FMatrixCreateYRotation(pRadians);
    return FMatrixMultiply(pMatrix, aRotationMatrix);
}

FMatrix FMatrixRotateZ(FMatrix pMatrix, float pRadians) {
    FMatrix aRotationMatrix = FMatrixCreateZRotation(pRadians);
    return FMatrixMultiply(pMatrix, aRotationMatrix);
}



