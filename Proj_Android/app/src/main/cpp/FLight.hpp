//
//  FLight.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/15/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FLight_hpp
#define FLight_hpp

class FLight {
public:
    inline FLight(float pIntensity) {
        mIntensity = pIntensity;
    }
    FLight();
    float mIntensity;
};

class FLightAmbient {
public:
    FLightAmbient();
    
    float mRed;
    float mGreen;
    float mBlue;
    
    float mAmbientIntensity;
};

class FLightDiffuse {
public:
    
    FLightDiffuse();

    float mRed;
    float mGreen;
    float mBlue;
    
    float mAmbientIntensity;
    float mDiffuseIntensity;
    
    float mDirX;
    float mDirY;
    float mDirZ;
};

class FLightPhong {
public:
    
    FLightPhong();
    
    float mRed;
    float mGreen;
    float mBlue;
    
    float mAmbientIntensity;
    float mDiffuseIntensity;
    float mSpecularIntensity;
    
    float mDirX;
    float mDirY;
    float mDirZ;
    
    float mShininess;
};

class FLightSimpleSpotlight {
public:
    
    FLightSimpleSpotlight();
    
    float mSpotlightX;
    float mSpotlightY;
    float mSpotlightZ;
    
    float mRed;
    float mGreen;
    float mBlue;
    
    float mAmbientIntensity;
    float mDiffuseIntensity;
    float mSpecularIntensity;
    
    float mDirX;
    float mDirY;
    float mDirZ;
    
    float mShininess;
    float mEmissions;
    
};


#endif
