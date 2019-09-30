//
//  FScrollCanvasPaged.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FScrollCanvasPaged.hpp"

#include "core_includes.h"

FScrollCanvasPaged::FScrollCanvasPaged() {
    mClipEnabled = false;
    //mRecievesConsumedTouches = true;
    
    mScrollPanStartThreshold = 14.0f;
    mScrollPanSwitchDirectionThreshold = 32.0f;
    
    mScrollPanning = false;
    mScrollHorizontal = false;
    
    mScrollEnabledHorizontal = true;
    mScrollEnabledVertical = true;
    
    mScrollCurrentPageH = 0;
    mScrollCurrentPageV = 0;
    
    mScrollAnimating = false;
    mScrollPanDirectionPicked = false;
    
    mScrollAnimationTimeTotal = 0;
    mScrollAnimationTimer = 0;
    
    mSpeedThresholdFlingTo = 20.0f;
    mSpeedThresholdNudgeBack = 6.0f;
    
    mScrollPageCountH = 1;
    mScrollPageCountV = 1;
    
    if((gDeviceWidth < 700) || (gDeviceHeight < 500))
    {
        mSpeedThresholdFlingTo *= 0.85f;
        mSpeedThresholdNudgeBack *= 0.85f;
    }
    
    for(int i=0;i<2;i++)
    {
        mScrollOffset[i] = 0.0f;
        mScrollOffsetPanShift[i] = 0.0f;
        mScrollOffsetPanStart[i] = 0.0f;
    }
    
    mAnimationDirection = 0;
    mFinishAnimationDirection = 0;
    mFinishAnimation = false;
    mScrollAnimationPercent = 0.0f;
    mScrollAnimationPercentTarget = 0.0f;
}

FScrollCanvasPaged::~FScrollCanvasPaged()
{
    
}

void FScrollCanvasPaged::SetPageCountHorizontal(int pCount)
{
    mScrollPageCountH = pCount;
}

void FScrollCanvasPaged::SetPageCountVertical(int pCount)
{
    mScrollPageCountV = pCount;
}


void FScrollCanvasPaged::BaseUpdate() {
    FGestureCanvas::BaseUpdate();
    
    if (mScrollAnimating) {
        if (mFinishAnimation) {
            mScrollAnimationPercent = 0.0f;
            mScrollAnimating = false;
            
            int aDir = mFinishAnimationDirection;
            
            int aPreviousPageH = mScrollCurrentPageH;
            int aPreviousPageV = mScrollCurrentPageV;
            
            if (mScrollHorizontal) {
                mScrollCurrentPageH += aDir;
                mScrollOffset[0] = ((float)(-mScrollCurrentPageH)) * mWidth;
            } else {
                mScrollCurrentPageV += aDir;
                
                mScrollOffset[1] = ((float)(-mScrollCurrentPageV)) * mHeight;
            }
            
            ScrollFinished();
            
            if(mScrollHorizontal)ScrollFinishedHorizontal(aPreviousPageH, mScrollCurrentPageH);
            else ScrollFinishedVertical(aPreviousPageV, mScrollCurrentPageV);
        } else {
            mFinishAnimationDirection = 0;
            if (mAnimationDirection == 1) {
                if(mScrollAnimationPercentTarget > mScrollAnimationPercent)mScrollAnimationPercent += (mScrollAnimationPercentTarget - mScrollAnimationPercent) / 16.0f;
                mScrollAnimationPercent += 0.025f;
                if(mScrollAnimationPercent >= mScrollAnimationPercentTarget)
                {
                    mScrollAnimationPercent = mScrollAnimationPercentTarget;
                    mFinishAnimation = true;
                    if(mScrollAnimationPercentTarget > (0.5f))mFinishAnimationDirection = -1;
                }
            } else {
                if(mScrollAnimationPercent > mScrollAnimationPercentTarget)mScrollAnimationPercent -= (mScrollAnimationPercent - mScrollAnimationPercentTarget) / 16.0f;
                mScrollAnimationPercent -= 0.025f;
                if (mScrollAnimationPercent <= mScrollAnimationPercentTarget) {
                    mScrollAnimationPercent = mScrollAnimationPercentTarget;
                    mFinishAnimation = true;
                    if(mScrollAnimationPercentTarget < (-0.5f))mFinishAnimationDirection = 1;
                }
            }
            
            if (mScrollHorizontal) {
                float aScrollBaseStartOffset = ((float)(-mScrollCurrentPageH)) * mWidth;
                mScrollOffset[0] = aScrollBaseStartOffset + mScrollAnimationPercent * mWidth;
            } else {
                float aScrollBaseStartOffset = ((float)(-mScrollCurrentPageV)) * mHeight;
                mScrollOffset[1] = aScrollBaseStartOffset + mScrollAnimationPercent * mHeight;
            }
        }
    }
    
    EnumList(FCanvas, aCanvas, mChildren) {
        aCanvas->SetTransformTranslate(mScrollOffset[0], mScrollOffset[1]);
    }
    
}

void FScrollCanvasPaged::PanBegin(float pX, float pY) {
    if (mScrollAnimating) {
        mScrollPanning = false;
    } else {
        mAnimationDirection = 0;
        mFinishAnimation = false;
        mScrollAnimationPercent = 0.0f;
        mScrollAnimationPercentTarget = 0.0f;
        
        mScrollPanDirectionPicked = false;
        mScrollPanning = true;
        
        for (int i=0;i<2;i++) {
            mScrollOffsetPanStart[i] = mScrollOffset[i];
            mScrollOffsetPanShift[i] = 0.0f;
        }
    }
}

void FScrollCanvasPaged::Pan(float pX, float pY) {
    if (mScrollPanning) {
        mScrollOffsetPanShift[0] = mGesturePanDistX;
        mScrollOffsetPanShift[1] = mGesturePanDistY;
        
        float aManhattanDistanceX = fabsf(mScrollOffsetPanShift[0]);
        float aManhattanDistanceY = fabsf(mScrollOffsetPanShift[1]);
        float aMaximumManhattanDistance = aManhattanDistanceX;
        
        if(mScrollEnabledVertical)
        {
            if(mScrollEnabledHorizontal)
            {
                if(aManhattanDistanceY > aMaximumManhattanDistance)aMaximumManhattanDistance = aManhattanDistanceY;
            }
            else
            {
                aMaximumManhattanDistance = aManhattanDistanceY;
            }
        }
        
        if(aMaximumManhattanDistance < mScrollPanSwitchDirectionThreshold)
        {
            if(mScrollPanDirectionPicked == false)
            {
                if((aManhattanDistanceX > aManhattanDistanceY) || (mScrollEnabledVertical == false))
                {
                    if(mScrollEnabledHorizontal)
                    {
                        if(aManhattanDistanceX > mScrollPanStartThreshold)
                        {
                            //Log("Picked X!\n");
                            
                            mScrollPanDirectionPicked = true;
                            mScrollHorizontal = true;
                        }
                    }
                }
                else
                {
                    if(mScrollEnabledVertical)
                    {
                        if(aManhattanDistanceY > mScrollPanStartThreshold)
                        {
                            //Log("Picked Y!\n");
                            
                            mScrollPanDirectionPicked = true;
                            mScrollHorizontal = false;
                        }
                    }
                }
            }
        }
        
        if(mScrollPanDirectionPicked)
        {
            bool aEdge = false;
            
            if(mScrollHorizontal)
            {
                if(mScrollOffsetPanShift[0] > 0.0f)
                {
                    if(mScrollCurrentPageH <= 0)aEdge = true;
                }
                else
                {
                    if(mScrollCurrentPageH >= (mScrollPageCountH - 1))aEdge = true;
                }
                
                float aOffset = mScrollOffsetPanShift[0];
                if(aEdge)aOffset = ScrollGetBounceDragShift(aOffset);
                
                mScrollOffset[0] = (mScrollOffsetPanStart[0] + aOffset);
                mScrollOffset[1] = mScrollOffsetPanStart[1];
                
                mScrollAnimationPercent = (aOffset / mWidth);
            }
            else
            {
                if(mScrollOffsetPanShift[1] > 0.0f)
                {
                    if(mScrollCurrentPageV <= 0)aEdge = true;
                }
                else
                {
                    if(mScrollCurrentPageV >= (mScrollPageCountV - 1))aEdge = true;
                }
                
                float aOffset = mScrollOffsetPanShift[1];
                if(aEdge)aOffset = ScrollGetBounceDragShift(aOffset);
                
                mScrollOffset[0] = mScrollOffsetPanStart[0];
                mScrollOffset[1] = (mScrollOffsetPanStart[1] + aOffset);
                mScrollAnimationPercent = (aOffset / mHeight);
            }
        }
    } else {
        //PanBegin(pX, pY);
    }
}

void FScrollCanvasPaged::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY) {
    if(pSpeedX > 80)pSpeedX = 80.0f;
    if(pSpeedX < -80)pSpeedX = -80.0f;
    if(pSpeedY > 80)pSpeedY = 80.0f;
    if(pSpeedY < -80)pSpeedY = -80.0f;
    
    if (mScrollPanning) {
        mScrollPanning = false;
        
        float aVelocity = pSpeedY;
        if(mScrollHorizontal)aVelocity = pSpeedX;
        
        float aMinimumScrollPercent = 0.25f;
        
        mAnimationDirection = -1;
        mFinishAnimation = false;
        
        if(fabsf(aVelocity) >= mSpeedThresholdFlingTo)
        {
            if(aVelocity >= 0)
            {
                mAnimationDirection = 1;
                if(mScrollAnimationPercent < 0)mScrollAnimationPercentTarget = 0.0f;
                else mScrollAnimationPercentTarget = 1.0f;
            }
            else
            {
                mAnimationDirection = -1;
                if(mScrollAnimationPercent > 0)mScrollAnimationPercentTarget = 0.0f;
                else mScrollAnimationPercentTarget = -1.0f;
            }
        }
        else
        {
            if(mScrollAnimationPercent >= 0)
            {
                if(mScrollAnimationPercent > aMinimumScrollPercent)
                {
                    mAnimationDirection = 1;
                    mScrollAnimationPercentTarget = 1.0f;
                }
                else
                {
                    mScrollAnimationPercentTarget = 0.0f;
                }
            }
            else
            {
                if(mScrollAnimationPercent < (-aMinimumScrollPercent))
                {
                    mAnimationDirection = -1;
                    mScrollAnimationPercentTarget = -1.0f;
                }
                else
                {
                    mAnimationDirection = 1;
                    mScrollAnimationPercentTarget = 0.0f;
                }
            }
        }
        
        if(mAnimationDirection < 0)
        {
            if(mScrollHorizontal)
            {
                //if(CanScrollRight() == false)
                if(mScrollCurrentPageH >= (mScrollPageCountH - 1))
                {
                    if(mScrollAnimationPercent <= 0)
                    {
                        mAnimationDirection = 1;
                        mScrollAnimationPercentTarget = 0.0f;
                    }
                }
            }
            else
            {
                //if(CanScrollDown() == false)
                if(mScrollCurrentPageV >= (mScrollPageCountV - 1))
                {
                    if(mScrollAnimationPercent <= 0)
                    {
                        mAnimationDirection = 1;
                        mScrollAnimationPercentTarget = 0.0f;
                    }
                }
            }
        }
        else
        {
            if(mScrollHorizontal)
            {
                //if(CanScrollLeft() == false)
                if(mScrollCurrentPageH <= 0)
                {
                    if(mScrollAnimationPercent >= 0)
                    {
                        mAnimationDirection = -1;
                        mScrollAnimationPercentTarget = 0.0f;
                    }
                }
            }
            else
            {
                if(mScrollCurrentPageV <= 0)
                {
                    if(mScrollAnimationPercent >= 0)
                    {
                        mAnimationDirection = -1;
                        mScrollAnimationPercentTarget = 0.0f;
                    }
                }
            }
        }
        
        mScrollAnimating = true;
    }
}

void FScrollCanvasPaged::ScrollFinished() {
    
}

void FScrollCanvasPaged::ScrollFinishedHorizontal(int pStartRow, int pEndRow)
{
    
}

void FScrollCanvasPaged::ScrollFinishedVertical(int pStartCol, int pEndCol) {
    
}

float FScrollCanvasPaged::ScrollGetBounceDragShift(float pAmount) {
    float aResult = pAmount;
    
    float aScale = mTransformAbsolute.mScale * (mTransformAbsolute.mScaleX + mTransformAbsolute.mScaleY) * 0.5f;
    
    float aMaxShift = ((gDeviceWidth * 0.25f)) / aScale;
    float aMaxDrag = ((gDeviceWidth * 0.75f)) / aScale;
    
    bool aNegative = (pAmount < 0.0f);
    
    if (aNegative)pAmount = (-pAmount);
    if (pAmount >= aMaxDrag) {
        aResult = aMaxShift;
    } else {
        float aPercent = (pAmount / aMaxDrag);
        float aRads = (PI / 2.0f) * aPercent;
        aResult = sin(aRads) * aMaxShift;
    }
    if (aNegative) aResult = (-aResult);
    return aResult;
}
