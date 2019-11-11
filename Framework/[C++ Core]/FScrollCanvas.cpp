//
//  FScrollCanvas.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 11/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "FScrollCanvas.hpp"

FScrollCanvas::FScrollCanvas() {
    
    //mClipEnabled = true;
    
    mEnabledX = true;
    mEnabledY = true;
    
    mRubberBandTimeFactor = 0.40f;
    mRubberBandTimeBase = 6;
    mRubberBandTimeMax = 38;
    
    mRubberBandReflectFactor = 0.42f;
    mRubberBandReflectCutoff = 12.0f * gSpriteDrawScale;
    
}

FScrollCanvas::~FScrollCanvas() {
    
}

void FScrollCanvas::BaseUpdate() {
    
    if ((mEnabledX == true) && (mAnimatingX == true) && (mAnimationTypeX == SCROLL_CANVAS_ANIMATION_TYPE_DECAY)) {
        
        float aNextX = mContentOffsetX + mAnimationDecayVelocityX;
        
        if (mAnimationDecayVelocityX > 0) {
            
            if (aNextX > 0.0f) {
                
                int aTicks = mRubberBandTimeBase + (int)(fabsf(mAnimationDecayVelocityX) * mRubberBandTimeFactor);
                if (aTicks > mRubberBandTimeMax) { aTicks = mRubberBandTimeMax; }
                
                int aHandOffType = SCROLL_CANVAS_HAND_OFF_TYPE_DECAY;
                float aReflectVelocity = -(mAnimationDecayVelocityX * mRubberBandReflectFactor);
                
                //if (fabsf(aReflectVelocity) < mRubberBandReflectCutoff) {
                 
                    aHandOffType = SCROLL_CANVAS_HAND_OFF_TYPE_STOP;
                    aReflectVelocity = 0.0f;
                //}
                
                DecelerateAnimationX(0.0f, mAnimationDecayVelocityX, aReflectVelocity, aTicks, aHandOffType);
            }
            
            
        } else {
            
            float aMinX = (mWidth - mContentWidth);
            if (aNextX < aMinX) {

                int aTicks = mRubberBandTimeBase + (int)(fabsf(mAnimationDecayVelocityX) * mRubberBandTimeFactor);
                if (aTicks > mRubberBandTimeMax) { aTicks = mRubberBandTimeMax; }
                int aHandOffType = SCROLL_CANVAS_HAND_OFF_TYPE_DECAY;
                float aReflectVelocity = -(mAnimationDecayVelocityX * mRubberBandReflectFactor);
                //if (fabsf(aReflectVelocity) < mRubberBandReflectCutoff) {
                    aHandOffType = SCROLL_CANVAS_HAND_OFF_TYPE_STOP;
                    aReflectVelocity = 0.0f;
                //}
            
                DecelerateAnimationX(aMinX, mAnimationDecayVelocityX, aReflectVelocity, aTicks, aHandOffType);
            }
        }
    }
    
    
    if ((mEnabledY == true) && (mAnimatingY == true) && (mAnimationTypeY == SCROLL_CANVAS_ANIMATION_TYPE_DECAY)) {
        
        float aNextY = mContentOffsetY + mAnimationDecayVelocityY;
        
        if (mAnimationDecayVelocityY > 0) {
            
            if (aNextY > 0.0f) {
                
                int aTicks = mRubberBandTimeBase + (int)(fabsf(mAnimationDecayVelocityY) * mRubberBandTimeFactor);
                if (aTicks > mRubberBandTimeMax) { aTicks = mRubberBandTimeMax; }
                
                int aHandOffType = SCROLL_CANVAS_HAND_OFF_TYPE_DECAY;
                float aReflectVelocity = -(mAnimationDecayVelocityY * mRubberBandReflectFactor);
                
                //if (fabsf(aReflectVelocity) < mRubberBandReflectCutoff) {
                 
                    aHandOffType = SCROLL_CANVAS_HAND_OFF_TYPE_STOP;
                    aReflectVelocity = 0.0f;
                //}
                
                DecelerateAnimationY(0.0f, mAnimationDecayVelocityY, aReflectVelocity, aTicks, aHandOffType);
            }
            
            
        } else {
            
            float aMinY = (mHeight - mContentHeight);
            if (aNextY < aMinY) {

                int aTicks = mRubberBandTimeBase + (int)(fabsf(mAnimationDecayVelocityY) * mRubberBandTimeFactor);
                if (aTicks > mRubberBandTimeMax) { aTicks = mRubberBandTimeMax; }
                int aHandOffType = SCROLL_CANVAS_HAND_OFF_TYPE_DECAY;
                float aReflectVelocity = -(mAnimationDecayVelocityY * mRubberBandReflectFactor);
                
                //if (fabsf(aReflectVelocity) < mRubberBandReflectCutoff) {
                    aHandOffType = SCROLL_CANVAS_HAND_OFF_TYPE_STOP;
                    aReflectVelocity = 0.0f;
                //}
            
                DecelerateAnimationY(aMinY, mAnimationDecayVelocityY, aReflectVelocity, aTicks, aHandOffType);
            }
        }

        
        
    }
    
    FScrollCanvasGeneric::BaseUpdate();
    
    
    
    
}

void FScrollCanvas::PanBegin(float pX, float pY) {
    
}

void FScrollCanvas::PanMove(float pX, float pY) {
    
    
    if (mEnabledX == true) {
        mContentOffsetX = mPanStartContentOffsetX + mPanDiffX;
        if (IsOutOfBoundsX(mContentOffsetX)) {
            mContentOffsetX = GetDampenedX(mContentOffsetX);
        }
    }
    if (mEnabledY == true) {
        mContentOffsetY = mPanStartContentOffsetY + mPanDiffY;
        if (IsOutOfBoundsY(mContentOffsetY)) {
            mContentOffsetY = GetDampenedY(mContentOffsetY);
        }
    }
    
}

void FScrollCanvas::PanRelease(float pX, float pY, float pSpeedX, float pSpeedY) {
    
    if (mEnabledX) {
        if (IsOutOfBoundsX(mContentOffsetX)) {
            OutOfBoundsSnapToEdgeX();
        } else {
            DecayAnimationX(pSpeedX, false);
        }
    }
    
    if (mEnabledY) {
        if (IsOutOfBoundsY(mContentOffsetY)) {
            OutOfBoundsSnapToEdgeY();
        } else {
            DecayAnimationY(pSpeedY, false);
        }
    }
}


