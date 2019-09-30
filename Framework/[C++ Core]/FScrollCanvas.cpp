//
//  FScrollCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "FScrollCanvas.hpp"
#include "core_includes.h"

FScrollCanvas::FScrollCanvas() {
    mClipEnabled = true;
    mScrollUpdateFlingDecayMultiply = 0.96f;
    mScrollUpdateFlingDecaySubtract = 0.08f;
    mScrollMaxDistance = 240.0f;
    mScrollHorizontalEnabled = true;
    mScrollVerticalEnabled = true;
    mScrollHorizontalDisabledIfTooSmall = true;
    mScrollVerticalDisabledIfTooSmall = true;
    for (int i=0;i<2;i++) {
        mScrollOffset[i] = 0.0f;
        mScrollStartOffset[i] = 0.0f;
        mScrollTargetOffset[0] = 0.0f;
        mScrollFlingSpeed = 0.0f;
        mScrollFlingDir[i] = 0.0f;
        mScrollFlingDir[i] = 0.0f;
        mScrollContentSizeWidth = 0.0f;
        mScrollContentSizeHeight = 0.0f;
        mScrollMinOffset[i] = 0.0f;
        mScrollBounceBackStartOffset[i] = 0.0f;
        mScrollBounceBackFinishOffset[i] = 0.0f;
        mScrollBounceBackStartSpeed[i] = 0.0f;
        mScrollBounceBackFinishSpeed[i] = 0.0f;
        mScrollBounceBackTimeTotal[i] = 0;
        mScrollBounceBackTime[i] = 0;
        mScrollBounceBackAdjustmentPre[i] = 0.0f;
        mScrollBounceBackAdjustmentPost[i] = 0.0f;
    }
}

FScrollCanvas::~FScrollCanvas() { }

void FScrollCanvas::BaseLayout() {
    FGestureCanvas::BaseLayout();
    if (mScrollContentSizeWidth > 0.25f && mScrollContentSizeHeight > 0.25f) {
        SetContentSize(mScrollContentSizeWidth, mScrollContentSizeHeight);
    }
}

void FScrollCanvas::BaseUpdate() {
    FGestureCanvas::BaseUpdate();
    bool aAnimatingBefore = ScrollIsAnimating();
    for (int i=0;i<2;i++) {
        if (mScrollBounceBackTimeTotal[i] > 0) {
            mScrollBounceBackTime[i]++;
            if (mScrollBounceBackTime[i] >= mScrollBounceBackTimeTotal[i]) {
                mScrollBounceBackTimeTotal[i] = 0.0f;
                mScrollOffset[i] = (mScrollBounceBackFinishOffset[i] + mScrollBounceBackAdjustmentPost[i]);
                float aMoveX = mScrollFlingDir[0] * mScrollFlingSpeed;
                float aMoveY = mScrollFlingDir[1] * mScrollFlingSpeed;
                if (i == 0) {
                    aMoveX = mScrollBounceBackFinishSpeed[i];
                } else {
                    aMoveY = mScrollBounceBackFinishSpeed[i];
                }
                
                float aLength = aMoveX * aMoveX + aMoveY * aMoveY;

                if (aLength > 0.25f) {
                    aLength = sqrtf(aLength);
                    aMoveX /= aLength;
                    aMoveY /= aLength;
                    mScrollFlingDir[0] = aMoveX;
                    mScrollFlingDir[1] = aMoveY;
                    mScrollFlingSpeed = aLength;
                } else {
                    mScrollFlingDir[i] = 0.0f;
                }
            } else {
                float aPercent = ((float)mScrollBounceBackTime[i]) / ((float)mScrollBounceBackTimeTotal[i]);
                float aPercentInv = 1.0f - aPercent;
                int aMagicTickNumber = 10;
                float aAdjustmentPercentPre = ((float)mScrollBounceBackTime[i]) / ((float)aMagicTickNumber);
                float aAdjustmentPercentPost = ((float)(mScrollBounceBackTimeTotal[i] - mScrollBounceBackTime[i])) / ((float)aMagicTickNumber);
                if ((aAdjustmentPercentPost >= 0) && (aAdjustmentPercentPost <= 1.0f)) {
                    mScrollBounceBackAdjustmentPost[i] += aAdjustmentPercentPost * mScrollBounceBackFinishSpeed[i];
                }
                aAdjustmentPercentPre = (1 - aAdjustmentPercentPre);
                if (aAdjustmentPercentPre >= 0.0f) {
                    mScrollBounceBackAdjustmentPre[i] += mScrollBounceBackStartSpeed[i] * aAdjustmentPercentPre;
                }
                float aOffset = mScrollBounceBackStartOffset[i] + (mScrollBounceBackFinishOffset[i] - mScrollBounceBackStartOffset[i]) * aPercent;
                aOffset += mScrollBounceBackAdjustmentPre[i] * aPercentInv;
                aOffset += mScrollBounceBackAdjustmentPost[i] * aPercent;
                mScrollOffset[i] = aOffset;
            }
        } else if(mScrollFlingSpeed > 0) {
            float aMove = mScrollFlingDir[i] * mScrollFlingSpeed;
            mScrollOffset[i] += aMove;
            mScrollTargetOffset[i] = mScrollOffset[i];
            if (PositionIsOutOfBoundsOver(mScrollOffset[i], i)) {
                ScrollBounce(i);
            } else if(PositionIsOutOfBoundsUnder(mScrollOffset[i], i)) {
                ScrollBounce(i);
            }
        }
    }

    if (mScrollFlingSpeed > 0) {
        mScrollFlingSpeed *= mScrollUpdateFlingDecayMultiply;
        mScrollFlingSpeed -= mScrollUpdateFlingDecaySubtract;
        if (mScrollFlingSpeed < 0.0f) { mScrollFlingSpeed = 0.0f; }
    }

    bool aAnimatingAfter = ScrollIsAnimating();
    if ((aAnimatingBefore == true) && (aAnimatingAfter == false)) {
        ScrollFinished();
        this->ScrollFinished();
    }

    float aTranslateX = mScrollOffset[0];
    float aTranslateY = mScrollOffset[1];

    if(mScrollHorizontalEnabled == false)aTranslateX = 0.0f;
    if(mScrollVerticalEnabled == false)aTranslateY = 0.0f;

    EnumList(FCanvas, aCanvas, mChildren) {
        aCanvas->SetTransformTranslate(aTranslateX, aTranslateY);
    }
}

FCanvas *FScrollCanvas::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed) {
    mScrollFlingSpeed = 0.0f;
    mScrollBounceBackTimeTotal[0] = 0;
    mScrollBounceBackTime[0] = 0;
    mScrollBounceBackTimeTotal[1] = 0;
    mScrollBounceBackTime[1] = 0;
    return FGestureCanvas::BaseTouchDown(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent, pConsumed);
}

void FScrollCanvas::PanBegin(float pX, float pY) {
    mScrollTargetOffset[0] = mScrollOffset[0];
    mScrollTargetOffset[1] = mScrollOffset[1];
    mScrollStartOffset[0] = mScrollOffset[0];
    mScrollStartOffset[1] = mScrollOffset[1];
}

void FScrollCanvas::Pan(float pX, float pY) {
    mScrollFlingSpeed = 0;

    if (mScrollHorizontalEnabled) {
        mScrollTargetOffset[0] = mScrollStartOffset[0] + mGesturePanDistX;
    }
    if (mScrollVerticalEnabled) {
        mScrollTargetOffset[1] = mScrollStartOffset[1] + mGesturePanDistY;
    }

    for (int i=0;i<2;i++) {
        mScrollOffset[i] = mScrollTargetOffset[i];
        if (mScrollTargetOffset[i] < mScrollMinOffset[i]) {
            float aShift = (mScrollMinOffset[i] - mScrollTargetOffset[i]);
            mScrollOffset[i] = (mScrollMinOffset[i] - ScrollGetBounceDragShift(aShift));
        }
        if (mScrollTargetOffset[i] > 0.0f) {
            float aShift = mScrollTargetOffset[i];
            mScrollOffset[i] = ScrollGetBounceDragShift(aShift);
        }
    }
}

void FScrollCanvas::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY) {
    
    pSpeedX *= 0.5f;
    pSpeedY *= 0.5f;
    
    if (mScrollHorizontalEnabled == false) { pSpeedX = 0.0f; }
    if (mScrollVerticalEnabled == false) { pSpeedY = 0.0f; }
    float aSpeed = pSpeedX * pSpeedX + pSpeedY * pSpeedY;
    if (aSpeed > 0.1f) {
        aSpeed = sqrtf(aSpeed);
        pSpeedX /= aSpeed;
        pSpeedY /= aSpeed;
    }
    mScrollFlingDir[0] = (pSpeedX);
    mScrollFlingDir[1] = (pSpeedY);
    mScrollFlingSpeed = aSpeed;
    //Log("mScrollFlingSpeed: %f\n", mScrollFlingSpeed);
    
    if (mScrollFlingSpeed > 40.0f) {
        mScrollFlingSpeed = 40.0f;
    }
    float aDestination[2];
    aDestination[0] = mScrollOffset[0];
    aDestination[1] = mScrollOffset[1];
    float aFlingSpeed = mScrollFlingSpeed;
    int aLoops = 0;
    while (aFlingSpeed > 0.0f) {
        aLoops++;
        float aMoveX = mScrollFlingDir[0] * aFlingSpeed;
        float aMoveY = mScrollFlingDir[1] * aFlingSpeed;
        aDestination[0] += aMoveX;
        aDestination[1] += aMoveY;
        aFlingSpeed *= mScrollUpdateFlingDecayMultiply;
        aFlingSpeed -= mScrollUpdateFlingDecaySubtract;
    }
    for (int i=0;i<2;i++) {
        bool aBounce = false;
        if (PositionIsOutOfBoundsOver(mScrollOffset[i], i)) {
            if (PositionIsOutOfBoundsOver(aDestination[i], i)) {
                aBounce = true;
            }
        }
        if (PositionIsOutOfBoundsUnder(mScrollOffset[i], i)) {
            if (PositionIsOutOfBoundsUnder(aDestination[i], i)) {
                aBounce = true;
            }
        }
        if (aBounce) {
            ScrollBounce(i);
        }
    }
}

void FScrollCanvas::ScrollFinished() {

}

bool FScrollCanvas::ScrollIsAnimating() {
    bool aResult = false;
    if (mScrollFlingSpeed > 0) { aResult = true; }
    for (int i=0;i<2;i++) {
        if(mScrollBounceBackTimeTotal[i] > 0) { aResult = true; }
    }
    return aResult;
}

void FScrollCanvas::ScrollBounce(int pIndex) {
    float aStickSpeedThreshold = 40.0f;
    mScrollBounceBackAdjustmentPre[pIndex] = 0.0f;
    mScrollBounceBackAdjustmentPost[pIndex] = 0.0f;
    mScrollBounceBackStartOffset[pIndex] = mScrollOffset[pIndex];
    mScrollBounceBackTime[pIndex] = 0;
    mScrollBounceBackTimeTotal[pIndex] = (8 + (mScrollFlingSpeed / 3.0f));
    bool aBouncesAway = false;
    float aSpeed = mScrollFlingSpeed * mScrollFlingDir[pIndex];
    mScrollBounceBackStartSpeed[pIndex] = aSpeed;
    if (fabsf(aSpeed) >= aStickSpeedThreshold) { aBouncesAway = true; }
    int aBounceDir = 0;
    if (mScrollOffset[pIndex] >= 0) {
        aBounceDir = -1;
        mScrollBounceBackFinishOffset[pIndex] = 0.0f;
        if (aSpeed < 0) {
            int aExtra = (int)(-(aSpeed / 4));
            if(aExtra > 30)aExtra = 30;
            mScrollBounceBackTimeTotal[pIndex] += aExtra;
        }
    } else {
        aBounceDir = 1;
        mScrollBounceBackFinishOffset[pIndex] = mScrollMinOffset[pIndex];
        if (aSpeed > 0) {
            int aExtra = (int)(aSpeed / 4);
            if(aExtra > 30)aExtra = 30;
            mScrollBounceBackTimeTotal[pIndex] += aExtra;
        }
    }
    mScrollBounceBackFinishSpeed[pIndex] = 0.0f;
    if (aBouncesAway) {
        float aBounceAwaySpeed = ((float)mScrollBounceBackTimeTotal[pIndex]) / 14.0f;
        if(aBounceDir == -1) { aBounceAwaySpeed = (-aBounceAwaySpeed); }
        mScrollBounceBackFinishSpeed[pIndex] = aBounceAwaySpeed;
    }
}

void FScrollCanvas::SetContentSize(float pWidth, float pHeight) {
    mScrollContentSizeWidth = pWidth;
    mScrollContentSizeHeight = pHeight;
    if (mScrollContentSizeWidth > mWidth) {
        mScrollMinOffset[0] = (mWidth - mScrollContentSizeWidth);
    } else {
        mScrollMinOffset[0] = 0.0f;
    }

    if (mScrollContentSizeHeight > mHeight) {
        mScrollMinOffset[1] = (mHeight - mScrollContentSizeHeight);
    } else {
        mScrollMinOffset[1] = 0.0f;
    }
}

float FScrollCanvas::ScrollGetBounceDragShift(float pAmount) {
    float aResult = pAmount;
    float aMaxShift = mScrollMaxDistance;
    float aMaxDrag = (gDeviceWidth * 0.75f);
    bool aNegative = (pAmount < 0.0f);
    if (aNegative) {
        pAmount = (-pAmount);
    }
    if (pAmount >= aMaxDrag) {
        aResult = aMaxShift;
    } else {
        float aPercent = (pAmount / aMaxDrag);
        float aRads = (3.1415926535897932384626433832795028841968f / 2.0f) * aPercent;
        aResult = sin(aRads) * aMaxShift;
    }
    if(aNegative)aResult = (-aResult);
    return aResult;
}

bool FScrollCanvas::PositionIsOutOfBoundsOver(float pValue, int pIndex) {
    return (pValue > 0.0f);
}

bool FScrollCanvas::PositionIsOutOfBoundsUnder(float pValue, int pIndex) {
    return (pValue < mScrollMinOffset[pIndex]);
}
