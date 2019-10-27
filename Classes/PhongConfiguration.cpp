//
//  PhongConfiguration.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nicholas Raptis on 2/27/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "PhongConfiguration.hpp"
#include "core_includes.h"

PhongConfiguration::PhongConfiguration() {
    
    mDirectionRotationPrimary = 30.0f;
    mDirectionRotationSecondary = 225.0f;
    
    mUniform.mLight.mAmbientIntensity = 0.05f;
    mUniform.mLight.mDiffuseIntensity = 0.15f;
    mUniform.mLight.mSpecularIntensity = 2.25f;
    mUniform.mLight.mRed = 1.0f;
    mUniform.mLight.mGreen = 1.0f;
    mUniform.mLight.mBlue = 1.0f;
}

PhongConfiguration::~PhongConfiguration() {
    
}

void PhongConfiguration::Print() {
    
    Log("**** BEGIN PhongConfiguration... ***\n");
    
    Log("mDirectionRotationPrimary = %f;\n", mDirectionRotationPrimary);
    Log("mDirectionRotationSecondary = %f;\n", mDirectionRotationSecondary);

    
    mUniform.Print();
    
    Log("**** END PhongConfiguration... ***\n");
    
}

void PhongConfiguration::Compute() {
    
    FVec3 aDir = FVec3(0.0f, 0.0f, 1.0f);
    aDir = Rotate3D(aDir, FVec3(1.0f, 0.0f, 0.0f), mDirectionRotationSecondary);
    aDir = Rotate3D(aDir, FVec3(0.0f, 1.0f, 0.0f), mDirectionRotationPrimary);
    
    mUniform.mLight.mDirX = aDir.mX;
    mUniform.mLight.mDirY = aDir.mY;
    mUniform.mLight.mDirZ = aDir.mZ;
}



