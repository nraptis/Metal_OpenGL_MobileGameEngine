//
//  FScrollCanvasGenericGeneric.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 11/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "FScrollCanvasGeneric.hpp"

FScrollCanvasGeneric::FScrollCanvasGeneric() {
    
    mTouchCount = 0;
    mTouch.mData = NULL;
    
    mDecayMultiply = 0.925f;
    mDecaySubtract = 0.1125 * gSpriteDrawScale;
    
    mDecayMultiplyHandedOff = 0.90f;
    mDecaySubtractHandedOff = 0.15 * gSpriteDrawScale;
    
    
    mMaxFlingSpeed = 42.0f * gSpriteDrawScale;
    
    mOvershootCorrectionSpeed = 1.0f * gSpriteDrawScale;
    mOvershootAntiDirectionMultiply = 0.85f;
    
    mReleaseFlingThreshold = 5.0f * gSpriteDrawScale;
    
    mContentOffsetX = 0.0f;
    mContentOffsetY = 0.0f;
    mPanStartContentOffsetX = 0.0f;
    mPanStartContentOffsetY = 0.0f;
    mContentWidth = 0.0f;
    mContentHeight = 0.0f;
    mPanStartX = 0.0f;
    mPanStartY = 0.0f;
    mPanX = 0.0f;
    mPanY = 0.0f;
    mPanDiffX = 0.0f;
    mPanDiffY = 0.0f;
    
    mOutOfBoundsRangeBaseDampened = 180.0f;
    mOutOfBoundsRangeBaseActual = 320.0f;
    
    mAnimatingX = false;
    mAnimatingY = false;
    
    mAnimationTypeX = SCROLL_CANVAS_ANIMATION_TYPE_NONE;
    mAnimationTypeY = SCROLL_CANVAS_ANIMATION_TYPE_NONE;
    
    mAnimationSnapTargetX = 0.0f;
    mAnimationSnapTargetY = 0.0f;
    
    mAnimationDecayVelocityX = 0.0f;
    mAnimationDecayHandedOffX = false;
    mAnimationDecayVelocityY = 0.0f;
    mAnimationDecayHandedOffY = false;
    mAnimationDecayVelocityDampeningFactor = 0.625f;
    
    
    //mAnimationDecayHandedOffX
    //mAnimationDecayHandedOffY;
    
    
    
    mAnimationDecelerateTickX = 0;
    mAnimationDecelerateTimeX = 100;
    mAnimationDecelerateHandoffTypeX = SCROLL_CANVAS_HAND_OFF_TYPE_STOP;
    mAnimationDeceleratePositionStartX = 0.0f;
    mAnimationDeceleratePositionEndX = 0.0f;
    mAnimationDecelerateVelocityStartX = 0.0f;
    mAnimationDecelerateVelocityEndX = 0.0f;
    mAnimationDecelerateVelocityCoef1X = 0.0f;
    mAnimationDecelerateVelocityCoef2X = 0.0f;
    mAnimationDecelerateVelocityCoef3X = 0.0f;
    mAnimationDecelerateTickY = 0;
    mAnimationDecelerateTimeY = 100;
    mAnimationDecelerateHandoffTypeY = SCROLL_CANVAS_HAND_OFF_TYPE_STOP;
    mAnimationDeceleratePositionStartY = 0.0f;
    mAnimationDeceleratePositionEndY = 0.0f;
    mAnimationDecelerateVelocityStartY = 0.0f;
    mAnimationDecelerateVelocityEndY = 0.0f;
    mAnimationDecelerateVelocityCoef1Y = 0.0f;
    mAnimationDecelerateVelocityCoef2Y = 0.0f;
    mAnimationDecelerateVelocityCoef3Y = 0.0f;
    
    mAnimationRestTickX = 0;
    mAnimationRestTargetX = 0.0f;
    mAnimationRestVelocityX = 0.0f;
    mAnimationRestMultiplyVelocityX = 0.0f;
    mAnimationRestWillOvershootX = false;
    mAnimationRestDidOvershootX = false;
    mAnimationRestDirectionX = -1;
    mAnimationRestTickY = 0;
    mAnimationRestTargetY = 0.0f;
    mAnimationRestVelocityY = 0.0f;
    mAnimationRestMultiplyVelocityY = 0.0f;
    mAnimationRestWillOvershootY = false;
    mAnimationRestDidOvershootY = false;
    mAnimationRestDirectionY = -1;
}

FScrollCanvasGeneric::~FScrollCanvasGeneric() {
    
}

void FScrollCanvasGeneric::BaseUpdate() {
    
    FCanvas::BaseUpdate();
    
    if (mTouch.mData != NULL) {
        mTouch.mTimer++;
        if (mTouch.mHistoryMoveCount > 0) {
            if ((mTouch.mTimer - mTouch.mHistoryMoveTime[0]) > 999) {
                BaseTouchFlush();
            }
        } else {
            if (mTouch.mTimer > 999) {
                BaseTouchFlush();
            }
        }
    }
    
    if (mAnimatingX == true) {
        if (mAnimationTypeX == SCROLL_CANVAS_ANIMATION_TYPE_SNAP) { UpdateSnapAnimationX(); }
        else if (mAnimationTypeX == SCROLL_CANVAS_ANIMATION_TYPE_DECAY) { UpdateDecayAnimationX(); }
        else if (mAnimationTypeX == SCROLL_CANVAS_ANIMATION_TYPE_DECELERATE) { UpdateDecelerateAnimationX(); }
        else if (mAnimationTypeX == SCROLL_CANVAS_ANIMATION_TYPE_REST) { UpdateRestAnimationX(); }
    }
    
    if (mAnimatingY == true) {
        if (mAnimationTypeY == SCROLL_CANVAS_ANIMATION_TYPE_SNAP) { UpdateSnapAnimationY(); }
        else if (mAnimationTypeY == SCROLL_CANVAS_ANIMATION_TYPE_DECAY) { UpdateDecayAnimationY(); }
        else if (mAnimationTypeY == SCROLL_CANVAS_ANIMATION_TYPE_DECELERATE) { UpdateDecelerateAnimationY(); }
        else if (mAnimationTypeY == SCROLL_CANVAS_ANIMATION_TYPE_REST) { UpdateRestAnimationY(); }
    }
    
    EnumList(FCanvas, aCanvas, mChildren) {
        aCanvas->SetTransformTranslate(mContentOffsetX, mContentOffsetY);
    }
}

FCanvas *FScrollCanvasGeneric::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed) {
    FCanvas *aChild = FCanvas::BaseTouchDown(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent, pConsumed);
    if (AllowInteraction() == false) {
        BaseTouchFlush();
        return aChild;
    }
    bool aContainsPoint = mTransformAbsolute.ContainsPoint(pX, pY);
    bool aTrack = false;
    bool aIsChild = (aChild == this);
    if (!pOutsideParent) {
        if (aIsChild == true) { aTrack = true; }
    }
    if (aContainsPoint && mRecievesConsumedTouches) {
        if (aIsChild == true) { aTrack = true; }
    }
    if ((aTrack == true) && (mTouch.mData == NULL)) {
        if ((mAnimatingX == true) || (mAnimatingY == true)) { CancelAnimation(); }
        mPanStartX = pX;
        mPanStartY = pY;
        mPanX = pX;
        mPanY = pY;
        mPanStartContentOffsetX = mContentOffsetX;
        mPanStartContentOffsetY = mContentOffsetY;
        mTouch.Reset(pX, pY, pData);
        PanBegin(pX, pY);
    }
    return aChild;
}

void FScrollCanvasGeneric::BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {
    FCanvas::BaseTouchMove(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);
    if (AllowInteraction() == false) {
        BaseTouchFlush();
        return;
    }
    if (pData != mTouch.mData) { return; }
    mPanX = pX;
    mPanY = pY;
    mPanDiffX = mPanX - mPanStartX;
    mPanDiffY = mPanY - mPanStartY;
    mTouch.Move(pX, pY);
    PanMove(pX, pY);
}

void FScrollCanvasGeneric::BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {
    FCanvas::BaseTouchUp(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);
    if (AllowInteraction() == false) {
        BaseTouchFlush();
        return;
    }
    if (mTouch.mData != pData) { return; }
    mTouch.mData = NULL;
    float aReleaseSpeedX = 0.0f;
    float aReleaseSpeedY = 0.0f;
    int aReleaseTime = (mTouch.mTimer - 6);
    int aReleaseConsiderCount = 0;
    for (int i=(mTouch.mHistoryMoveCount - 2);i >= 0;i--) {
        if (mTouch.mHistoryMoveTime[i + 1] >= aReleaseTime) {
            int aTimeDiff = (mTouch.mHistoryMoveTime[i + 1] - mTouch.mHistoryMoveTime[i]);
            float aXDiff = (mTouch.mHistoryMoveX[i + 1] - mTouch.mHistoryMoveX[i]);
            float aYDiff = (mTouch.mHistoryMoveY[i + 1] - mTouch.mHistoryMoveY[i]);
            aReleaseSpeedX += ((float)aTimeDiff) * aXDiff;
            aReleaseSpeedY += ((float)aTimeDiff) * aYDiff;
            aReleaseConsiderCount += 1;
        }
    }
    
    if (aReleaseConsiderCount > 0) {
        aReleaseConsiderCount++;
        aReleaseSpeedX /= ((float)aReleaseConsiderCount);
        aReleaseSpeedY /= ((float)aReleaseConsiderCount);
    }
    
    PanRelease(pX, pY, aReleaseSpeedX, aReleaseSpeedY);
}

void FScrollCanvasGeneric::BaseTouchFlush() {
    FCanvas::BaseTouchFlush();
    mTouch.Reset(0.0f, 0.0f, NULL);
}

void FScrollCanvasGeneric::PanBegin(float pX, float pY) {
    
}

void FScrollCanvasGeneric::PanMove(float pX, float pY) {
    
}

void FScrollCanvasGeneric::PanRelease(float pX, float pY, float pSpeedX, float pSpeedY) {
    
}

void FScrollCanvasGeneric::SetContentSize(float pWidth, float pHeight) {
    mContentWidth = pWidth;
    mContentHeight = pHeight;
    if (mContentWidth < mWidth) { mContentWidth = mWidth; }
    if (mContentHeight < mHeight) { mContentHeight = mHeight; }
}

bool FScrollCanvasGeneric::IsOutOfBoundsX(float pScrollX) {
    if (pScrollX > 0.0f) { return true; }
    float aMinX = (mWidth - mContentWidth);
    if (pScrollX < aMinX) { return true; }
    return false;
}

bool FScrollCanvasGeneric::IsOutOfBoundsY(float pScrollY) {
    if (pScrollY > 0.0f) { return true; }
    float aMinY = (mHeight - mContentHeight);
    if (pScrollY < aMinY) { return true; }
    return false;
}

void FScrollCanvasGeneric::OutOfBoundsSnapToEdgeX() {
    if (mContentOffsetX > 0.0f) {
        SnapAnimationX(0.0f);
    } else {
        float aTargetX = (mWidth - mContentWidth);
        if (aTargetX > 0.0f) { aTargetX = 0.0f; }
        SnapAnimationX(aTargetX);
    }
}

void FScrollCanvasGeneric::OutOfBoundsSnapToEdgeY() {
    if (mContentOffsetY > 0.0f) {
        SnapAnimationY(0.0f);
    } else {
        float aTargetY = (mHeight - mContentHeight);
        if (aTargetY > 0.0f) { aTargetY = 0.0f; }
        SnapAnimationY(aTargetY);
    }
}

float FScrollCanvasGeneric::GetDampenedX(float pScrollX) {
    if (pScrollX > 0.0f) {
        return GetOutOfBoundsDampenedDrag(pScrollX);
    } else {
        float aMinX = (mWidth - mContentWidth);
        float aOvershoot = (pScrollX - aMinX);
        return aMinX + GetOutOfBoundsDampenedDrag(aOvershoot);
    }
}

float FScrollCanvasGeneric::GetDampenedY(float pScrollY) {
    if (pScrollY > 0.0f) {
        return GetOutOfBoundsDampenedDrag(pScrollY);
    } else {
        float aMinY = (mHeight - mContentHeight);
        float aOvershoot = (pScrollY - aMinY);
        return aMinY + GetOutOfBoundsDampenedDrag(aOvershoot);
    }
}

float FScrollCanvasGeneric::GetOutOfBoundsDampenedDrag(float pAmount) {
    float aActualMax = mOutOfBoundsRangeBaseActual * gSpriteDrawScale;
    float aDampenedMax = mOutOfBoundsRangeBaseDampened * gSpriteDrawScale;
    float aResult = 0.0f;
    bool aNegative = (pAmount < 0.0f);
    if (aNegative == true) {
        pAmount = (-pAmount);
    }
    if (pAmount >= aActualMax) {
        aResult = aDampenedMax;
    } else {
        float aPercent = (pAmount / aActualMax);
        float aRads = (PI_2) * aPercent;
        aResult = sinf(aRads) * aDampenedMax;
    }
    if (aNegative == true) {
        aResult = (-aResult);
    }
    return aResult;
}

bool FScrollCanvasGeneric::IsDragging() {
    if (mTouch.mData != NULL) { return true; }
    return false;
}

bool FScrollCanvasGeneric::IsScrolling() {
    if (mAnimatingX == true) { return true; }
    if (mAnimatingY == true) { return true; }
    if (mTouch.mData != NULL) { return true; }
    return false;
}

void FScrollCanvasGeneric::AnimationComplete() {
    
}

void FScrollCanvasGeneric::CancelAnimation() {
    mAnimatingX = false;
    mAnimatingY = false;
}

float FScrollCanvasGeneric::GetDecayStopPosition(float pStart, float pVelocity) {
    return GetDecayStopPosition(pStart, pVelocity, mDecayMultiply, mDecaySubtract);
}

float FScrollCanvasGeneric::GetDecayStopPosition(float pStart, float pVelocity, float pAccel, float pSubtract) {
    float aVelocity = pVelocity;
    if (aVelocity > mMaxFlingSpeed) { aVelocity = mMaxFlingSpeed; }
    if (aVelocity < -mMaxFlingSpeed) { aVelocity = -mMaxFlingSpeed; }
    float aResult = pStart;
    if (aVelocity > 0.0f) {
        while (true) {
            aResult += aVelocity;
            aVelocity -= pSubtract;
            if (aVelocity <= 0.0f) {
                break;
            } else {
                aVelocity *= pAccel;
            }
        }
    } else {
        while (true) {
            aResult += aVelocity;
            aVelocity += pSubtract;
            if (aVelocity >= 0.0f) {
                break;
            } else {
                aVelocity *= pAccel;
            }
        }
    }
    return aResult;
}

void FScrollCanvasGeneric::SnapAnimationX(float pTargetX) {
    mAnimatingX = true;
    mAnimationTypeX = SCROLL_CANVAS_ANIMATION_TYPE_SNAP;
    mAnimationSnapTargetX = pTargetX;
}

void FScrollCanvasGeneric::SnapAnimationY(float pTargetY) {
    mAnimatingY = true;
    mAnimationTypeY = SCROLL_CANVAS_ANIMATION_TYPE_SNAP;
    mAnimationSnapTargetY = pTargetY;
}

void FScrollCanvasGeneric::DecayAnimationX(float pVelocity, bool pHandedOff) {
    if (pVelocity > mMaxFlingSpeed) { pVelocity = mMaxFlingSpeed; }
    if (pVelocity < -mMaxFlingSpeed) { pVelocity = -mMaxFlingSpeed; }
    mAnimatingX = true;
    mAnimationTypeX = SCROLL_CANVAS_ANIMATION_TYPE_DECAY;
    mAnimationDecayVelocityX = pVelocity * mAnimationDecayVelocityDampeningFactor;
    mAnimationDecayHandedOffX = pHandedOff;
    if (mAnimationDecayVelocityX > mMaxFlingSpeed) { mAnimationDecayVelocityX = mMaxFlingSpeed; }
    if (mAnimationDecayVelocityX < -mMaxFlingSpeed) { mAnimationDecayVelocityX = -mMaxFlingSpeed; }
}

void FScrollCanvasGeneric::DecayAnimationY(float pVelocity, bool pHandedOff) {
    if (pVelocity > mMaxFlingSpeed) { pVelocity = mMaxFlingSpeed; }
    if (pVelocity < -mMaxFlingSpeed) { pVelocity = -mMaxFlingSpeed; }
    mAnimatingY = true;
    mAnimationTypeY = SCROLL_CANVAS_ANIMATION_TYPE_DECAY;
    mAnimationDecayVelocityY = pVelocity * mAnimationDecayVelocityDampeningFactor;
    mAnimationDecayHandedOffY = pHandedOff;
    if (mAnimationDecayVelocityY > mMaxFlingSpeed) { mAnimationDecayVelocityY = mMaxFlingSpeed; }
    if (mAnimationDecayVelocityY < -mMaxFlingSpeed) { mAnimationDecayVelocityY = -mMaxFlingSpeed; }
}

void FScrollCanvasGeneric::DecelerateAnimationX(float pTargetPos, float pStartVelocity, float pTargetVelocity, int pTicks, int pHandOffType) {
    if (pTicks < 6) { pTicks = 6; }
    if (pStartVelocity > mMaxFlingSpeed) { pStartVelocity = mMaxFlingSpeed; }
    if (pStartVelocity < -mMaxFlingSpeed) { pStartVelocity = -mMaxFlingSpeed; }
    if (pTargetVelocity > mMaxFlingSpeed) { pTargetVelocity = mMaxFlingSpeed; }
    if (pTargetVelocity < -mMaxFlingSpeed) { pTargetVelocity = -mMaxFlingSpeed; }
    mAnimatingX = true;
    mAnimationTypeX = SCROLL_CANVAS_ANIMATION_TYPE_DECELERATE;
    mAnimationDeceleratePositionStartX = mContentOffsetX;
    mAnimationDeceleratePositionEndX = pTargetPos;
    mAnimationDecelerateVelocityStartX = pStartVelocity;
    mAnimationDecelerateVelocityEndX = pTargetVelocity;
    pStartVelocity *= ((float)pTicks);
    pTargetVelocity *= ((float)pTicks);
    mAnimationDecelerateVelocityCoef1X = pStartVelocity;
    mAnimationDecelerateVelocityCoef2X = 3.0f * (pTargetPos - mContentOffsetX) - 2.0f * pStartVelocity - pTargetVelocity;
    mAnimationDecelerateVelocityCoef3X = 2.0f * (mContentOffsetX - pTargetPos) + pStartVelocity + pTargetVelocity;
    mAnimationDecelerateTickX = 0;
    mAnimationDecelerateTimeX = pTicks;
    mAnimationDecelerateHandoffTypeX = pHandOffType;
}

void FScrollCanvasGeneric::DecelerateAnimationY(float pTargetPos, float pStartVelocity, float pTargetVelocity, int pTicks, int pHandOffType) {
    if (pTicks < 6) { pTicks = 6; }
    if (pStartVelocity > mMaxFlingSpeed) { pStartVelocity = mMaxFlingSpeed; }
    if (pStartVelocity < -mMaxFlingSpeed) { pStartVelocity = -mMaxFlingSpeed; }
    if (pTargetVelocity > mMaxFlingSpeed) { pTargetVelocity = mMaxFlingSpeed; }
    if (pTargetVelocity < -mMaxFlingSpeed) { pTargetVelocity = -mMaxFlingSpeed; }
    mAnimatingY = true;
    mAnimationTypeY = SCROLL_CANVAS_ANIMATION_TYPE_DECELERATE;
    mAnimationDeceleratePositionStartY = mContentOffsetY;
    mAnimationDeceleratePositionEndY = pTargetPos;
    mAnimationDecelerateVelocityStartY = pStartVelocity;
    mAnimationDecelerateVelocityEndY = pTargetVelocity;
    pStartVelocity *= ((float)pTicks);
    pTargetVelocity *= ((float)pTicks);
    mAnimationDecelerateVelocityCoef1Y = pStartVelocity;
    mAnimationDecelerateVelocityCoef2Y = 3.0f * (pTargetPos - mContentOffsetY) - 2.0f * pStartVelocity - pTargetVelocity;
    mAnimationDecelerateVelocityCoef3Y = 2.0f * (mContentOffsetY - pTargetPos) + pStartVelocity + pTargetVelocity;
    mAnimationDecelerateTickY = 0;
    mAnimationDecelerateTimeY = pTicks;
    mAnimationDecelerateHandoffTypeY = pHandOffType;
}

void FScrollCanvasGeneric::RestAnimationX(float pTargetPos, float pVelocity) {
    
    if (pVelocity > mMaxFlingSpeed) { pVelocity = mMaxFlingSpeed; }
    if (pVelocity < -mMaxFlingSpeed) { pVelocity = -mMaxFlingSpeed; }
    
    mAnimatingX = true;
    mAnimationTypeX = SCROLL_CANVAS_ANIMATION_TYPE_REST;
    
    mAnimationRestTickX = 0;
    mAnimationRestTargetX = pTargetPos;
    mAnimationRestVelocityX = pVelocity;
    mAnimationRestMultiplyVelocityX = mDecayMultiply;
    
    float aStopPosition = GetDecayStopPosition(mContentOffsetX, pVelocity);
    mAnimationRestWillOvershootX = false;
    mAnimationRestDidOvershootX = false;
    mAnimationRestDirectionX = 0;
    
    if (pVelocity < 0.0f) {
        mAnimationRestDirectionX = 1;
        if (pTargetPos > aStopPosition) {
            mAnimationRestWillOvershootX = true;
        }
    }
    
    if (pVelocity > 0.0f) {
        mAnimationRestDirectionX = -1;
        if (pTargetPos < aStopPosition) {
            mAnimationRestWillOvershootX = true;
        }
    }
    
    if (mAnimationRestWillOvershootX == true) {
        float aStep = 0.001f;
        for (float aMult = (mDecayMultiply - aStep);aMult>=0.75f;aMult-=aStep) {
            aStopPosition = GetDecayStopPosition(mContentOffsetX, pVelocity, aMult, mDecaySubtract);
            if (mAnimationRestDirectionX == 1) {
                if (pTargetPos < aStopPosition) {
                    break;
                }
            } else {
                if (pTargetPos > aStopPosition) {
                    break;
                }
            }
            mAnimationRestMultiplyVelocityX = aMult;
        }
    }
}

void FScrollCanvasGeneric::RestAnimationY(float pTargetPos, float pVelocity) {
    
    if (pVelocity > mMaxFlingSpeed) { pVelocity = mMaxFlingSpeed; }
    if (pVelocity < -mMaxFlingSpeed) { pVelocity = -mMaxFlingSpeed; }
    
    mAnimatingY = true;
    mAnimationTypeY = SCROLL_CANVAS_ANIMATION_TYPE_REST;
    
    mAnimationRestTickY = 0;
    mAnimationRestTargetY = pTargetPos;
    mAnimationRestVelocityY = pVelocity;
    mAnimationRestMultiplyVelocityY = mDecayMultiply;
    
    float aStopPosition = GetDecayStopPosition(mContentOffsetY, pVelocity);
    mAnimationRestWillOvershootY = false;
    mAnimationRestDidOvershootY = false;
    mAnimationRestDirectionY = 0;
    
    if (pVelocity < 0.0f) {
        mAnimationRestDirectionY = 1;
        if (pTargetPos > aStopPosition) {
            mAnimationRestWillOvershootY = true;
        }
    }
    
    if (pVelocity > 0.0f) {
        mAnimationRestDirectionY = -1;
        if (pTargetPos < aStopPosition) {
            mAnimationRestWillOvershootY = true;
        }
    }
    
    if (mAnimationRestWillOvershootY == true) {
        float aStep = 0.001f;
        for (float aMult = (mDecayMultiply - aStep);aMult>=0.75f;aMult-=aStep) {
            aStopPosition = GetDecayStopPosition(mContentOffsetY, pVelocity, aMult, mDecaySubtract);
            if (mAnimationRestDirectionY == 1) {
                if (pTargetPos < aStopPosition) {
                    break;
                }
            } else {
                if (pTargetPos > aStopPosition) {
                    break;
                }
            }
            mAnimationRestMultiplyVelocityY = aMult;
        }
    }
}

void FScrollCanvasGeneric::UpdateSnapAnimationX() {
    float aDiffX = mAnimationSnapTargetX - mContentOffsetX;
    float aLength = fabsf(aDiffX);
    if (aLength > SQRT_EPSILON) {
        aDiffX /= aLength;
        float aMoveAmount = (aLength / 18.0f) + 1.25f;
        if (aMoveAmount >= aLength) {
            mContentOffsetX = mAnimationSnapTargetX;
            mAnimatingX = false;
            if ((mAnimatingX == false) && (mAnimatingY == false)) {
                AnimationComplete();
            }
        } else {
            mContentOffsetX += aDiffX * aMoveAmount;
        }
    } else {
        mContentOffsetX = mAnimationSnapTargetX;
        mAnimatingX = false;
        if ((mAnimatingX == false) && (mAnimatingY == false)) {
            AnimationComplete();
        }
    }
}

void FScrollCanvasGeneric::UpdateSnapAnimationY() {
    float aDiffY = mAnimationSnapTargetY - mContentOffsetY;
    float aLength = fabsf(aDiffY);
    if (aLength > SQRT_EPSILON) {
        aDiffY /= aLength;
        float aMoveAmount = (aLength / 18.0f) + 1.25f;
        if (aMoveAmount >= aLength) {
            mContentOffsetY = mAnimationSnapTargetY;
            mAnimatingY = false;
            if ((mAnimatingX == false) && (mAnimatingY == false)) {
                AnimationComplete();
            }
        } else {
            mContentOffsetY += aDiffY * aMoveAmount;
        }
    } else {
        mContentOffsetY = mAnimationSnapTargetY;
        mAnimatingY = false;
        if ((mAnimatingX == false) && (mAnimatingY == false)) {
            AnimationComplete();
        }
    }
}

void FScrollCanvasGeneric::UpdateDecayAnimationX() {
    
    mContentOffsetX += mAnimationDecayVelocityX;
    bool aComplete = false;
    
    if (mAnimationDecayVelocityX > 0.0f) {
        
        if (mAnimationDecayHandedOffX == true) {
            mAnimationDecayVelocityX -= mDecaySubtractHandedOff;
        } else {
            mAnimationDecayVelocityX -= mDecaySubtract;
        }
        
        if (mAnimationDecayVelocityX <= 0.0f) {
            mAnimationDecayVelocityX = 0.0f;
            aComplete = true;
        }
    }
    
    if (mAnimationDecayVelocityX < 0.0f) {
        if (mAnimationDecayHandedOffX == true) {
            mAnimationDecayVelocityX += mDecaySubtractHandedOff;
        } else {
            mAnimationDecayVelocityX += mDecaySubtract;
        }
        
        if (mAnimationDecayVelocityX >= 0.0f) {
             mAnimationDecayVelocityX = 0.0f;
            aComplete = true;
        }
    }
    
    if (aComplete) {
        mAnimatingX = false;
        mAnimationDecayVelocityX = 0.0f;
        if ((mAnimatingX == false) && (mAnimatingY == false)) {
            AnimationComplete();
        }
    } else {
        if (mAnimationDecayHandedOffX == true) {
            mAnimationDecayVelocityX *= mDecayMultiplyHandedOff;
        } else {
            mAnimationDecayVelocityX *= mDecayMultiply;
        }
    }
}

void FScrollCanvasGeneric::UpdateDecayAnimationY() {
    
    mContentOffsetY += mAnimationDecayVelocityY;
    bool aComplete = false;
    
    if (mAnimationDecayVelocityY > 0.0f) {
        if (mAnimationDecayHandedOffY == true) {
            mAnimationDecayVelocityY -= mDecaySubtractHandedOff;
        } else {
            mAnimationDecayVelocityY -= mDecaySubtract;
        }
        
        if (mAnimationDecayVelocityY <= 0.0f) {
            mAnimationDecayVelocityY = 0.0f;
            aComplete = true;
        }
    }
    
    if (mAnimationDecayVelocityY < 0.0f) {
        if (mAnimationDecayHandedOffY == true) {
            mAnimationDecayVelocityY += mDecaySubtractHandedOff;
        } else {
            mAnimationDecayVelocityY += mDecaySubtract;
        }
        
        if (mAnimationDecayVelocityY >= 0.0f) {
             mAnimationDecayVelocityY = 0.0f;
            aComplete = true;
        }
    }
    
    if (aComplete) {
        mAnimatingY = false;
        mAnimationDecayVelocityY = 0.0f;
        if ((mAnimatingX == false) && (mAnimatingY == false)) {
            AnimationComplete();
        }
    } else {
        if (mAnimationDecayHandedOffY == true) {
            mAnimationDecayVelocityY *= mDecayMultiplyHandedOff;
        } else {
            mAnimationDecayVelocityY *= mDecayMultiply;
        }
    }
}

void FScrollCanvasGeneric::UpdateDecelerateAnimationX() {
    mAnimationDecelerateTickX++;
    if (mAnimationDecelerateTickX >= mAnimationDecelerateTimeX) {
        mContentOffsetX = mAnimationDeceleratePositionEndX;
        if (mAnimationDecelerateHandoffTypeX == SCROLL_CANVAS_HAND_OFF_TYPE_DECAY) {
            DecayAnimationX(mAnimationDecelerateVelocityEndX, true);
        } else {
            mAnimatingX = false;
            if ((mAnimatingX == false) && (mAnimatingY == false)) {
                AnimationComplete();
            }
        }
        return;
    }
    float aPercent = ((float)mAnimationDecelerateTickX) / ((float)mAnimationDecelerateTimeX);
    float aPercent2 = aPercent * aPercent;
    float aPercent3 = aPercent2 * aPercent;
    mContentOffsetX = mAnimationDeceleratePositionStartX + mAnimationDecelerateVelocityCoef1X * aPercent + mAnimationDecelerateVelocityCoef2X * aPercent2 + mAnimationDecelerateVelocityCoef3X * aPercent3;
}

void FScrollCanvasGeneric::UpdateDecelerateAnimationY() {
    mAnimationDecelerateTickY++;
    if (mAnimationDecelerateTickY >= mAnimationDecelerateTimeY) {
        mContentOffsetY = mAnimationDeceleratePositionEndY;
        if (mAnimationDecelerateHandoffTypeY == SCROLL_CANVAS_HAND_OFF_TYPE_DECAY) {
            DecayAnimationY(mAnimationDecelerateVelocityEndY, true);
        } else {
            mAnimatingY = false;
            if ((mAnimatingX == false) && (mAnimatingY == false)) {
                AnimationComplete();
            }
        }
        return;
    }
    float aPercent = ((float)mAnimationDecelerateTickY) / ((float)mAnimationDecelerateTimeY);
    float aPercent2 = aPercent * aPercent;
    float aPercent3 = aPercent2 * aPercent;
    mContentOffsetY = mAnimationDeceleratePositionStartY + mAnimationDecelerateVelocityCoef1Y * aPercent + mAnimationDecelerateVelocityCoef2Y * aPercent2 + mAnimationDecelerateVelocityCoef3Y * aPercent3;
}

void FScrollCanvasGeneric::UpdateRestAnimationX() {
    mAnimationRestTickX++;
    mContentOffsetX += mAnimationRestVelocityX;
    if (mAnimationRestDidOvershootX == false) {
        if (mAnimationRestVelocityX > 0.0f) {
            mAnimationRestVelocityX -= mDecaySubtract;
            if (mAnimationRestVelocityX <= 0.0f) {
                mAnimationRestVelocityX = 0.0f;
            }
        }
        if (mAnimationRestVelocityX < 0.0f) {
            mAnimationRestVelocityX += mDecaySubtract;
            if (mAnimationRestVelocityX >= 0.0f) {
                 mAnimationRestVelocityX = 0.0f;
            }
        }
        mAnimationRestVelocityX *= mAnimationRestMultiplyVelocityX;
    }
    
    if (mAnimationRestWillOvershootX == true) {
        if (mAnimationRestDidOvershootX == false) {
            if (mAnimationRestDirectionX == 1) {
                if (mAnimationRestTargetX > mContentOffsetX) {
                    mAnimationRestDidOvershootX = true;
                }
            } else {
                if (mAnimationRestTargetX < mContentOffsetX) {
                    mAnimationRestDidOvershootX = true;
                }
            }
        } else {
            if (mAnimationRestDirectionX == 1) {
                if (mAnimationRestVelocityX < 0.0f) {
                    mAnimationRestVelocityX *= mOvershootAntiDirectionMultiply;
                }
                mAnimationRestVelocityX += mOvershootCorrectionSpeed;
                if (mAnimationRestTargetX < mContentOffsetX) {
                    mContentOffsetX = mAnimationRestTargetX;
                    mAnimatingX = false;
                    if ((mAnimatingX == false) && (mAnimatingY == false)) {
                        AnimationComplete();
                    }
                }
            } else {
                if (mAnimationRestVelocityX > 0.0f) {
                    mAnimationRestVelocityX *= mOvershootAntiDirectionMultiply;
                }
                mAnimationRestVelocityX -= mOvershootCorrectionSpeed;
                if (mAnimationRestTargetX > mContentOffsetX) {
                    mContentOffsetX = mAnimationRestTargetX;
                    mAnimatingX = false;
                    if ((mAnimatingX == false) && (mAnimatingY == false)) {
                        AnimationComplete();
                    }
                }
            }
        }
    } else {
        float aDiffX = mAnimationRestTargetX - mContentOffsetX;
        float aLength = fabsf(aDiffX);
        if (aLength > SQRT_EPSILON) {
            aDiffX /= aLength;
            float aMoveAmount = (aLength / 18.0f) + 1.25f;
            float aRampUpTick = ((float)mAnimationRestTickX) / ((float)50);
            aMoveAmount *= aRampUpTick;
            if (aMoveAmount >= aLength) {
                mContentOffsetX = mAnimationRestTargetX;
                mAnimatingX = false;
                if ((mAnimatingX == false) && (mAnimatingY == false)) {
                    AnimationComplete();
                }
            } else {
                mContentOffsetX += aDiffX * aMoveAmount;
            }
        } else {
            mContentOffsetX = mAnimationRestTargetX;
            mAnimatingX = false;
            if ((mAnimatingX == false) && (mAnimatingY == false)) {
                AnimationComplete();
            }
        }
    }
}

void FScrollCanvasGeneric::UpdateRestAnimationY() {
    mAnimationRestTickY++;
    mContentOffsetY += mAnimationRestVelocityY;
    if (mAnimationRestDidOvershootY == false) {
        if (mAnimationRestVelocityY > 0.0f) {
            mAnimationRestVelocityY -= mDecaySubtract;
            if (mAnimationRestVelocityY <= 0.0f) {
                mAnimationRestVelocityY = 0.0f;
            }
        }
        if (mAnimationRestVelocityY < 0.0f) {
            mAnimationRestVelocityY += mDecaySubtract;
            if (mAnimationRestVelocityY >= 0.0f) {
                 mAnimationRestVelocityY = 0.0f;
            }
        }
        mAnimationRestVelocityY *= mAnimationRestMultiplyVelocityY;
    }
    
    if (mAnimationRestWillOvershootY == true) {
        if (mAnimationRestDidOvershootY == false) {
            if (mAnimationRestDirectionY == 1) {
                if (mAnimationRestTargetY > mContentOffsetY) {
                    mAnimationRestDidOvershootY = true;
                }
            } else {
                if (mAnimationRestTargetY < mContentOffsetY) {
                    mAnimationRestDidOvershootY = true;
                }
            }
        } else {
            if (mAnimationRestDirectionY == 1) {
                if (mAnimationRestVelocityY < 0.0f) {
                    mAnimationRestVelocityY *= mOvershootAntiDirectionMultiply;
                }
                mAnimationRestVelocityY += mOvershootCorrectionSpeed;
                if (mAnimationRestTargetY < mContentOffsetY) {
                    mContentOffsetY = mAnimationRestTargetY;
                    mAnimatingY = false;
                    if ((mAnimatingX == false) && (mAnimatingY == false)) {
                        AnimationComplete();
                    }
                }
            } else {
                if (mAnimationRestVelocityY > 0.0f) {
                    mAnimationRestVelocityY *= mOvershootAntiDirectionMultiply;
                }
                mAnimationRestVelocityY -= mOvershootCorrectionSpeed;
                if (mAnimationRestTargetY > mContentOffsetY) {
                    mContentOffsetY = mAnimationRestTargetY;
                    mAnimatingY = false;
                    if ((mAnimatingX == false) && (mAnimatingY == false)) {
                        AnimationComplete();
                    }
                }
            }
        }
    } else {
        float aDiffY = mAnimationRestTargetY - mContentOffsetY;
        float aLength = fabsf(aDiffY);
        if (aLength > SQRT_EPSILON) {
            aDiffY /= aLength;
            float aMoveAmount = (aLength / 18.0f) + 1.25f;
            float aRampUpTick = ((float)mAnimationRestTickY) / ((float)50);
            aMoveAmount *= aRampUpTick;
            if (aMoveAmount >= aLength) {
                mContentOffsetY = mAnimationRestTargetY;
                mAnimatingY = false;
                if ((mAnimatingX == false) && (mAnimatingY == false)) {
                    AnimationComplete();
                }
            } else {
                mContentOffsetY += aDiffY * aMoveAmount;
            }
        } else {
            mContentOffsetY = mAnimationRestTargetY;
            mAnimatingY = false;
            if ((mAnimatingX == false) && (mAnimatingY == false)) {
                AnimationComplete();
            }
        }
    }
}
