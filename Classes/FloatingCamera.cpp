//
//  FloatingCamera.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/15/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FloatingCamera.hpp"
#include "core_includes.h"

FloatingCamera::FloatingCamera() {
    mFOV = M_PI_2;
    
    mAspect = gDeviceWidth / gDeviceHeight;
    //mAspect = 1.0f;
    
    mTarget = FVec3(0.0f, 0.0f, 0.0f);
    mDirection = FVec3(0.0f, 1.0f, 0.0f);
    
    mCenterOffset = FVec2(0.0f, 0.0f);
    
    mDistance = 24.0f;
    mRotationPrimary = 0.0f;
    mRotationSecondary = 0.0f;
}

FloatingCamera::~FloatingCamera() {
    
}

void FloatingCamera::Print() {
    Log("*** BEGIN FloatingCamera ***\n");
    Log("mFOV = %f;\n", mFOV);
    Log("mTarget = FVec3(%f, %f, %f);\n", mTarget.mX, mTarget.mY, mTarget.mZ);
    Log("mDirection = FVec3(%f, %f, %f);\n", mDirection.mX, mDirection.mY, mDirection.mZ);
    Log("mDistance = %f;\n", mDistance);
    Log("mRotationPrimary = %f;\n", mRotationPrimary);
    Log("mRotationSecondary = %f;\n", mRotationSecondary);
    Log("*** END FloatingCamera ***\n");
}

FMatrix FloatingCamera::GetProjection() {
    
    mAspect = gDeviceWidth / gDeviceHeight;
    
    FMatrix aPerspective = FMatrixCreatePerspective(mFOV, mAspect, 0.01f, 255.0f);
    //The screen starts at the bottom in this coordinate space.
    aPerspective.Scale(1.0f, -1.0f, 1.0f);
    aPerspective.OffsetPerspectiveCenter(mCenterOffset.mX, mCenterOffset.mY);
    
    //Rotate your eyeball around your fixed target...
    FVec3 aEye = FVec3(0.0f, 0.0f, 1.0f);
    aEye = Rotate3D(aEye, FVec3(1.0f, 0.0f, 0.0f), mRotationSecondary);
    aEye = Rotate3D(aEye, FVec3(0.0f, 1.0f, 0.0f), mRotationPrimary);
    
    //We are always looking at 0,0,0, direction is usually (0.0f, 1.0f, 0.0f) for us...
    FMatrix aCamera = FMatrixCreateLookAt(aEye.mX * mDistance, aEye.mY * mDistance, aEye.mZ * mDistance,
                                          mTarget.mX, mTarget.mY, mTarget.mZ,
                                          mDirection.mX, mDirection.mY, mDirection.mZ);
    
    return FMatrixMultiply(aPerspective, aCamera);
}
