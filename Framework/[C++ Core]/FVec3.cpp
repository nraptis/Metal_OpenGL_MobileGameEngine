//
//  FVec3.cpp
//  SRT
//
//  Created by Nick Raptis on 10/8/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FVec3.hpp"
#include "core_includes.h"

float FVec3::Length() {
    float aLength = mX * mX + mY * mY + mZ * mZ;
    if (aLength > SQRT_EPSILON) { aLength = sqrtf(aLength); }
    return aLength;
}

float FVec3::LengthSquared() {
    return mX * mX + mY * mY;
}

void FVec3::Normalize() {
    float aLength = mX * mX + mY * mY + mZ * mZ;
    if (aLength > SQRT_EPSILON) {
        aLength = sqrtf(aLength);
        mX /= aLength;
        mY /= aLength;
        mZ /= aLength;
    } else {
        mX = 0.0f;
        mY = -1.0f;
        mZ = 0.0f;
    }
}

float FVec3::Dot(FVec3 &pVector) {
    return mX * pVector.mX + mY * pVector.mY + mZ * pVector.mZ;
}

FVec3 FVec3::Cross(FVec3 &pVector) {
    FVec3 aResult;
    aResult.mX = (mY * pVector.mZ) - (pVector.mY * mZ);
    aResult.mY = -(mX * pVector.mZ) + (pVector.mX * mZ);
    aResult.mZ = (mX * pVector.mY) - (mY * pVector.mX);
    return aResult;
}

FMatrix cVectorRotationMatrix;
FVec3 FVec3::RotateX(float pDegrees) {
    cVectorRotationMatrix.ResetRotationX(pDegrees);
    return cVectorRotationMatrix.ProcessVec3(*this);
}

FVec3 FVec3::RotateY(float pDegrees) {
    cVectorRotationMatrix.ResetRotationY(pDegrees);
    return cVectorRotationMatrix.ProcessVec3(*this);
}

FVec3 FVec3::RotateZ(float pDegrees) {
    cVectorRotationMatrix.ResetRotationZ(pDegrees);
    return cVectorRotationMatrix.ProcessVec3(*this);
}

FVec3 FVec3::GetPerp() {
    
    //Pick the "optimal" orthogonal...
    float aFactorX = fabsf(mX);
    float aFactorY = fabsf(mY);
    float aFactorZ = fabsf(mZ);
    
    // (1, 1, 1)
    //   Ortho (-1, 1, 1)
    
    FVec3 aResult;
    
    if (aFactorX < 0.00025f) {
        if (aFactorY < 0.00025f) {
            //Z only, go straight up or left...
            aResult.mX = 0.0f;
            aResult.mY = 1.0f;
            aResult.mZ = 0.0f;
        } else {
            //Y and Z only, flip them...
            aResult.mX = 0.0f;
            aResult.mY = -mZ;
            aResult.mZ = mY;
        }
    } else if (aFactorY < 0.00025f) {
        
        if (aFactorZ < 0.00025f) {
            //X only, go straight up or in...
            aResult.mX = 0.0f;
            aResult.mY = -1.0f;
            aResult.mZ = 0.0f;
        } else {
            //X and Z only, flip them...
            aResult.mX = -mZ;
            aResult.mY = 0.0f;
            aResult.mZ = mX;
        }
    } else if (aFactorZ < 0.00025f) {
        //X and Y only, flip them...
        aResult.mX = -mY;
        aResult.mY = mX;
        aResult.mZ = 0.0f;
    } else {
        aResult.mX = 1.0f;
        aResult.mY = 1.0f;
        aResult.mZ = -((mX + mY) / mZ);
    }
    
    aResult.Normalize();
    
    return aResult;
}

FVec3 FVec3::GetProjected(FVec3 pPlaneOrigin, FVec3 pPlaneNormal) {
    
    FVec3 aDiff;
    aDiff.mX = mX - pPlaneOrigin.mX;
    aDiff.mY = mY - pPlaneOrigin.mY;
    aDiff.mZ = mZ - pPlaneOrigin.mZ;
    
    float aDist = aDiff.Dot(pPlaneNormal);
    
    FVec3 aResult;
    
    aResult.mX = mX - pPlaneNormal.mX * aDist;
    aResult.mY = mY - pPlaneNormal.mY * aDist;
    aResult.mZ = mZ - pPlaneNormal.mZ * aDist;
    
    return aResult;
    
}


/*

FVec3 FVec3Make(float x, float y, float z)
{
    FVec3 v = { x, y, z };
    return v;
}

FVec3 FVec3MakeWithArray(float pValues[3])
{
    FVec3 v = { pValues[0], pValues[1], pValues[2] };
    return v;
}

FVec3 FVec3Negate(FVec3 pVector)
{
    FVec3 v = { -pVector.mX, -pVector.mY, -pVector.mZ };
    return v;
}

FVec3 FVec3Add(FVec3 pVectorLeft, FVec3 pVectorRight)
{
    FVec3 v = { pVectorLeft.mX + pVectorRight.mX,
        pVectorLeft.mY + pVectorRight.mY,
        pVectorLeft.mZ + pVectorRight.mZ };
    return v;
}

FVec3 FVec3Subtract(FVec3 pVectorLeft, FVec3 pVectorRight)
{
    FVec3 v = { pVectorLeft.mX - pVectorRight.mX,
        pVectorLeft.mY - pVectorRight.mY,
        pVectorLeft.mZ - pVectorRight.mZ };
    return v;
}

FVec3 FVec3Multiply(FVec3 pVectorLeft, FVec3 pVectorRight)
{
    FVec3 v = { pVectorLeft.mX * pVectorRight.mX,
        pVectorLeft.mY * pVectorRight.mY,
        pVectorLeft.mZ * pVectorRight.mZ };
    return v;
}

FVec3 FVec3Divide(FVec3 pVectorLeft, FVec3 pVectorRight)
{
    FVec3 v = { pVectorLeft.mX / pVectorRight.mX,
        pVectorLeft.mY / pVectorRight.mY,
        pVectorLeft.mZ / pVectorRight.mZ };
    return v;
}

FVec3 FVec3AddScalar(FVec3 pVector, float pValue)
{
    FVec3 v = { pVector.mX + pValue,
        pVector.mY + pValue,
        pVector.mZ + pValue };
    return v;
}

FVec3 FVec3SubtractScalar(FVec3 pVector, float pValue)
{
    FVec3 v = { pVector.mX - pValue,
        pVector.mY - pValue,
        pVector.mZ - pValue };
    return v;
}

FVec3 FVec3MultiplyScalar(FVec3 pVector, float pValue)
{
    FVec3 v = { pVector.mX * pValue,
        pVector.mY * pValue,
        pVector.mZ * pValue };
    return v;
}

FVec3 FVec3DivideScalar(FVec3 pVector, float pValue)
{
    FVec3 v = { pVector.mX / pValue,
        pVector.mY / pValue,
        pVector.mZ / pValue };
    return v;
}

float FVec3DotProduct(FVec3 pVectorLeft, FVec3 pVectorRight)
{
    return pVectorLeft.mX * pVectorRight.mX + pVectorLeft.mY * pVectorRight.mY + pVectorLeft.mZ * pVectorRight.mZ;
}

float FVec3Length(FVec3 pVector)
{
    return sqrtf(pVector.mX * pVector.mX + pVector.mY * pVector.mY + pVector.mZ * pVector.mZ);
}

float FVec3Distance(FVec3 pVectorStart, FVec3 pVectorEnd)
{
    return FVec3Length(FVec3Subtract(pVectorEnd, pVectorStart));
}

FVec3 FVec3Lerp(FVec3 pVectorStart, FVec3 pVectorEnd, float t)
{
    FVec3 v = { pVectorStart.mX + ((pVectorEnd.mX - pVectorStart.mX) * t),
        pVectorStart.mY + ((pVectorEnd.mY - pVectorStart.mY) * t),
        pVectorStart.mZ + ((pVectorEnd.mZ - pVectorStart.mZ) * t) };
    return v;
}

FVec3 FVec3CrossProduct(FVec3 pVectorLeft, FVec3 pVectorRight)
{
    FVec3 v = { pVectorLeft.mY * pVectorRight.mZ - pVectorLeft.mZ * pVectorRight.mY,
        pVectorLeft.mZ * pVectorRight.mX - pVectorLeft.mX * pVectorRight.mZ,
        pVectorLeft.mX * pVectorRight.mY - pVectorLeft.mY * pVectorRight.mX };
    return v;
}

FVec3 FVec3Project(FVec3 pVectorToProject, FVec3 projectionVector)
{
    float scale = FVec3DotProduct(projectionVector, pVectorToProject) / FVec3DotProduct(projectionVector, projectionVector);
    FVec3 v = FVec3MultiplyScalar(projectionVector, scale);
    return v;
}

*/
