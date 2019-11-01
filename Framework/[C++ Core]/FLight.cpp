//
//  FLight.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/15/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FLight.hpp"

FLight::FLight() {
    mIntensity = 1.0f;
}

FLightAmbient::FLightAmbient() {
    mRed = 1.0f;
    mGreen = 1.0f;
    mBlue = 1.0f;    
    mAmbientIntensity = 1.0f;
}

FLightDiffuse::FLightDiffuse() {
    mRed = 1.0f;
    mGreen = 1.0f;
    mBlue = 1.0f;
    
    mAmbientIntensity = 0.35f;
    mDiffuseIntensity = 0.65f;
    
    mDirX = 0.0f;
    mDirY = 0.0f;
    mDirZ = -1.0f;
}

FLightPhong::FLightPhong() {
    mRed = 1.0f;
    mGreen = 1.0f;
    mBlue = 1.0f;
    
    mAmbientIntensity = 0.0f;
    mDiffuseIntensity = 0.25f;
    mSpecularIntensity = 0.75f;
    
    mDirX = 0.0f;
    mDirY = 0.0f;
    mDirZ = -1.0f;
    
    mShininess = 8.0f;
}

FLightSimpleSpotlight::FLightSimpleSpotlight() {
    mRed = 1.0f;
    mGreen = 1.0f;
    mBlue = 1.0f;
    
    mAmbientIntensity = 0.0f;
    mDiffuseIntensity = 0.25f;
    mSpecularIntensity = 0.75f;
    
    mSpotlightX = 10.0f;
    mSpotlightY = -10.0f;
    mSpotlightZ = 0.0f;
    
    mDirX = 0.0f;
    mDirY = 0.0f;
    mDirZ = -1.0f;
    
    mShininess = 8.0f;
    mEmissions = 0.0f;
}


