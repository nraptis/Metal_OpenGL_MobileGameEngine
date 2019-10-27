//
//  FloatingCamera.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/15/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FloatingCamera_hpp
#define FloatingCamera_hpp

#include "FVec3.hpp"
#include "FMatrix.hpp"

class FloatingCamera {
public:
    FloatingCamera();
    ~FloatingCamera();
    
    void                                        Print();
    
    FMatrix                                     GetProjection();
    
    float                                       mFOV;
    float                                       mAspect;
    
    FVec3                                       mTarget;
    FVec3                                       mDirection;
    
    FVec2                                       mCenterOffset;
    
    float                                       mDistance;
    float                                       mRotationPrimary;
    float                                       mRotationSecondary;
};

#endif

