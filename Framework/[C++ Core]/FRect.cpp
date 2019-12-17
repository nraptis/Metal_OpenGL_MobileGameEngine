//
//  FRect.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/12/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FRect.hpp"
#include "core_includes.h"

FRect::FRect(float pX, float pY, float pWidth, float pHeight) {
    mX = pX;
    mY = pY;
    mWidth = pWidth;
    mHeight = pHeight;
}

FRect::FRect(float pWidth, float pHeight) {
    mX = 0.0f;
    mY = 0.0f;
    mWidth = pWidth;
    mHeight = pHeight;
}

FRect::FRect() {
    mX = 0.0f;
    mY = 0.0f;
    mWidth = 0.0f;
    mHeight = 0.0f;
}

FRect::~FRect() {
    
}

FVec2 FRect::Center() {
    return FVec2(mX + mWidth / 2.0f, mY + mHeight / 2.0f);
}

float FRect::Left() {
    return mX;
}

float FRect::Right() {
    return mX + mWidth;
}

float FRect::Top() {
    return mY;
}

float FRect::Bottom() {
    return mY + mHeight;
}

FRect FRect::FitAspectFit(FRect pRect, float pObjectWidth, float pObjectHeight, float pBorder) {
    FRect aResult;
    float aScale = 1.0f;
    aResult = FitAspectFit(pRect, pObjectWidth, pObjectHeight, pBorder, aScale);
    return aResult;
}

//
FRect FRect::FitAspectFit(FRect pRect, float pObjectWidth, float pObjectHeight, float pBorder, float &pScale) {
    pScale = 1.0f;
    
    float aWidth = 0.0f;
    float aHeight = 0.0f;
    
    float aImageWidth = pObjectWidth;
    float aImageHeight = pObjectHeight;
    
    float aProperWidth = pRect.mWidth - pBorder * 2.0f;
    float aProperHeight = pRect.mHeight - pBorder * 2.0f;
    
    aWidth = aProperWidth;
    aHeight = aProperHeight;
    
    if ((aImageWidth > SQRT_EPSILON) && (aImageHeight > SQRT_EPSILON) && (aProperWidth > SQRT_EPSILON) && (aProperHeight > SQRT_EPSILON)) {
        if ((pObjectWidth / pObjectHeight) > (aProperWidth / aProperHeight)) {
            pScale = aProperWidth / aImageWidth;
            aWidth = aImageWidth * pScale;
            aHeight = aImageHeight * pScale;
            
        } else {
            pScale = aProperHeight / aImageHeight;
            aWidth = aImageWidth * pScale;
            aHeight = aImageHeight * pScale;
        }
    }
    
    float aX = (pRect.mX + pRect.mWidth / 2.0f) - aWidth / 2.0f;
    float aY = (pRect.mY + pRect.mHeight / 2.0f) - aHeight / 2.0f;
    
    return FRect(aX, aY, aWidth, aHeight);
}

FRect FRect::FitAspectFill(FRect pRect, float pObjectWidth, float pObjectHeight, float pBorder) {
    FRect aResult;
    float aScale = 1.0f;
    aResult = FitAspectFill(pRect, pObjectWidth, pObjectHeight, pBorder, aScale);
    return aResult;
}

FRect FRect::FitAspectFill(FRect pRect, float pObjectWidth, float pObjectHeight, float pBorder, float &pScale) {
    pScale = 1.0f;
    
    float aWidth = 0.0f;
    float aHeight = 0.0f;
    
    float aImageWidth = pObjectWidth;
    float aImageHeight = pObjectHeight;
    
    float aProperWidth = pRect.mWidth - pBorder * 2.0f;
    float aProperHeight = pRect.mHeight - pBorder * 2.0f;
    
    aWidth = aProperWidth;
    aHeight = aProperHeight;
    
    if ((aImageWidth > SQRT_EPSILON) && (aImageHeight > SQRT_EPSILON) && (aProperWidth > SQRT_EPSILON) && (aProperHeight > SQRT_EPSILON)) {
        if ((pObjectWidth / pObjectHeight) < (aProperWidth / aProperHeight)) {
            pScale = aProperWidth / aImageWidth;
            aWidth = aImageWidth * pScale;
            aHeight = aImageHeight * pScale;
            
        }
        else
        {
            pScale = aProperHeight / aImageHeight;
            aWidth = aImageWidth * pScale;
            aHeight = aImageHeight * pScale;
        }
    }
    
    float aX = (pRect.mX + pRect.mWidth / 2.0f) - aWidth / 2.0f;
    float aY = (pRect.mY + pRect.mHeight / 2.0f) - aHeight / 2.0f;
    
    return FRect(aX, aY, aWidth, aHeight);
}

bool FRect::Contains(float pX, float pY) {
    return ((pX >= mX) && (pX <= (mX + mWidth)) && (pY >= mY) && (pY <= (mY + mHeight)));
}

bool FRect::Intersects(float pX, float pY, float pWidth, float pHeight) {
    return !(((pX + pWidth) <= mX) || ((pY + pHeight) <= mY) || (pX >= (mX + mWidth)) || (pY >= (mY + mHeight)));
}
