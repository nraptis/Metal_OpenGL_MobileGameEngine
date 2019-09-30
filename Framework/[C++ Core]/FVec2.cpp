//
//  FVec2.cpp
//  SRT
//
//  Created by Nick Raptis on 10/8/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FVec2.hpp"
#include "core_includes.h"

float FVec2::Length() {
    float aLength = mX * mX + mY * mY;
    if(aLength > SQRT_EPSILON)aLength = sqrtf(aLength);
    return aLength;
}

float FVec2::LengthSquared() {
    return mX * mX + mY * mY;
}

void FVec2::Normalize() {
    float aLength = mX * mX + mY * mY;
    if (aLength > SQRT_EPSILON) {
        aLength = sqrtf(aLength);
        mX /= aLength;
        mY /= aLength;
    } else {
        mX = 0.0f;
        mY = -1.0f;
    }
}

FVec2 FVec2Lerp(FVec2 vectorStart, FVec2 vectorEnd, float t) {
    FVec2 aResult;
    aResult.mX = vectorStart.mX + ((vectorEnd.mX - vectorStart.mX) * t);
    aResult.mY = vectorStart.mY + ((vectorEnd.mY - vectorStart.mY) * t);
    return aResult;
}
