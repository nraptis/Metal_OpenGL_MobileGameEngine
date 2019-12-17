//
//  FScrollCanvasPagedPaged.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 11/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "FScrollCanvasPaged.hpp"

FScrollCanvasPaged::FScrollCanvasPaged() {
    
    mPageCount = 0;
    mPage = 0;
    
    mAnimationCompletePage = 0;
    
    mVertical = false;
}

FScrollCanvasPaged::~FScrollCanvasPaged() {
    
}

void FScrollCanvasPaged::BaseLayout() {
    FScrollCanvasGeneric::BaseLayout();
    
    AdjustSizeToFitPageCount();
}


void FScrollCanvasPaged::BaseUpdate() {
    FScrollCanvasGeneric::BaseUpdate();
}

void FScrollCanvasPaged::BaseTouchFlush() {
    FScrollCanvasGeneric::BaseTouchFlush();
    SnapToCurrentPage();
}

void FScrollCanvasPaged::PanBegin(float pX, float pY) {
    
}

void FScrollCanvasPaged::PanMove(float pX, float pY) {
    
    if (mVertical == true) {
        mContentOffsetY = mPanStartContentOffsetY + mPanDiffY;
        if (IsOutOfBoundsY(mContentOffsetY)) {
            mContentOffsetY = GetDampenedY(mContentOffsetY);
        }
    } else {
        mContentOffsetX = mPanStartContentOffsetX + mPanDiffX;
        if (IsOutOfBoundsX(mContentOffsetX)) {
            mContentOffsetX = GetDampenedX(mContentOffsetX);
        }
    }
}

void FScrollCanvasPaged::PanRelease(float pX, float pY, float pSpeedX, float pSpeedY) {
    //printf("FScrollCanvasPaged::PanRelease(%f( (%.2f, %.2f) Vel(%.2f, %.2f)\n", mContentOffsetX, pX, pY, pSpeedX, pSpeedY);
    
    if (pSpeedX > mMaxFlingSpeed) { pSpeedX = mMaxFlingSpeed; }
    if (pSpeedX < -mMaxFlingSpeed) { pSpeedX = -mMaxFlingSpeed; }
    
    if (pSpeedY > mMaxFlingSpeed) { pSpeedY = mMaxFlingSpeed; }
    if (pSpeedY < -mMaxFlingSpeed) { pSpeedY = -mMaxFlingSpeed; }
    
    float aMagnitude = 0.0f;
    
    if (mVertical == true) {
        
        aMagnitude = fabsf(pSpeedY);
        
        
            
        if (aMagnitude >= mReleaseFlingThreshold) {
            
            float aStopPosition = GetDecayStopPosition(mContentOffsetY, pSpeedY);
            if (pSpeedY > 0) {
                aStopPosition += mHeight2 * 0.5f;
            } else {
                aStopPosition -= mHeight2 * 0.5f;
            }
            
            mAnimationCompletePage = GetPageForPosition(aStopPosition);
            if (mAnimationCompletePage < mPage) { mAnimationCompletePage = mPage - 1; }
            if (mAnimationCompletePage > mPage) { mAnimationCompletePage = mPage + 1; }
            if (pSpeedY > 0.0f && mPage > 0) {
                if (mContentOffsetY < GetPositionForPage(mPage)) {
                    if (mAnimationCompletePage < mPage) {
                        mAnimationCompletePage = mPage;
                    }
                }
            } else {
                if (mContentOffsetY > GetPositionForPage(mPage)) {
                    if (mAnimationCompletePage > mPage) {
                        mAnimationCompletePage = mPage;
                    }
                }
            }
            
            if (mAnimationCompletePage >= mPageCount) { mAnimationCompletePage = (mPageCount - 1); }
            if (mAnimationCompletePage < 0) { mAnimationCompletePage = 0; }
            
            if (IsOutOfBoundsY(mContentOffsetY)) {
                SnapAnimationY(GetPositionForPage(mAnimationCompletePage));
            } else {
                float aRestingPosition = GetPositionForPage(mAnimationCompletePage);
                RestAnimationY(aRestingPosition, pSpeedY);
            }
        } else {
            SnapToCurrentPage();
        }
        
    } else {

        aMagnitude = fabsf(pSpeedX);
        if (aMagnitude >= mReleaseFlingThreshold) {
            
            float aStopPosition = GetDecayStopPosition(mContentOffsetX, pSpeedX);
            if (pSpeedX > 0) {
                aStopPosition += mWidth2 * 0.5f;
            } else {
                aStopPosition -= mWidth2 * 0.5f;
            }
            
            mAnimationCompletePage = GetPageForPosition(aStopPosition);
            if (mAnimationCompletePage < mPage) { mAnimationCompletePage = mPage - 1; }
            if (mAnimationCompletePage > mPage) { mAnimationCompletePage = mPage + 1; }
            
            if (pSpeedX > 0.0f && mPage > 0) {
                if (mContentOffsetX < GetPositionForPage(mPage)) {
                    if (mAnimationCompletePage < mPage) {
                        mAnimationCompletePage = mPage;
                    }
                }
            } else {
                if (mContentOffsetX > GetPositionForPage(mPage)) {
                    if (mAnimationCompletePage > mPage) {
                        mAnimationCompletePage = mPage;
                    }
                }
            }
            
            if (mAnimationCompletePage >= mPageCount) { mAnimationCompletePage = (mPageCount - 1); }
            if (mAnimationCompletePage < 0) { mAnimationCompletePage = 0; }
            
            if (IsOutOfBoundsX(mContentOffsetX)) {
                SnapAnimationX(GetPositionForPage(mAnimationCompletePage));
            } else {
                float aRestingPosition = GetPositionForPage(mAnimationCompletePage);
                RestAnimationX(aRestingPosition, pSpeedX);
            }
        } else {
            SnapToCurrentPage();
        }
    }
}

void FScrollCanvasPaged::DidLandOnPage(int pPage) {
    
    printf("DidLandOnPage[%d]\n", pPage);
    
}

int FScrollCanvasPaged::GetPageForPosition(float pPosition) {
    int aResult = 0;
    if (mVertical) {
        aResult = (int)((((float)-pPosition) + mHeight2) / mHeight);
    } else {
        aResult = (int)((((float)-pPosition) + mWidth2) / mWidth);
    }
    if (aResult >= mPageCount) { aResult = mPageCount - 1; }
    if (aResult < 0) { aResult = 0; }
    return aResult;
}

float FScrollCanvasPaged::GetPositionForPage(int pPage) {
    float aResult = 0.0f;
    if (mVertical) {
        aResult = ((float)(pPage)) * (-mHeight);
    } else {
        aResult = ((float)(pPage)) * (-mWidth);
    }
    return aResult;
}


void FScrollCanvasPaged::CancelAnimation() {
    FScrollCanvasGeneric::CancelAnimation();
    //int aPrevPage = mPage;
    
    if (mVertical) {
        mPage = GetPageForPosition(mContentOffsetY);
    } else {
        mPage = GetPageForPosition(mContentOffsetX);
    }
    
    //if (aPrevPage != mPage) {
    //    DidLandOnPage(mPage);
    //}
    
}

void FScrollCanvasPaged::AnimationComplete() {
    FScrollCanvasGeneric::AnimationComplete();
    mPage = mAnimationCompletePage;
    DidLandOnPage(mPage);
}

void FScrollCanvasPaged::SetPageCount(int pCount) {
    mPageCount = pCount;
    AdjustSizeToFitPageCount();
}

void FScrollCanvasPaged::SetPage(int pPage) {
    
    CancelAnimation();
    
    mPage = pPage;
    if (mPage >= mPageCount) { mPage = (mPageCount - 1); }
    if (mPage < 0) { mPage = 0; }
    
    float aPosition = GetPositionForPage(mPage);
    if (mVertical) {
        mContentOffsetY = aPosition;
    } else {
        mContentOffsetX = aPosition;
    }
    DidLandOnPage(mPage);
}

void FScrollCanvasPaged::SnapToCurrentPage() {
    mAnimationCompletePage = 0;
    if (mVertical) {
        mAnimationCompletePage = GetPageForPosition(mContentOffsetY);
        SnapAnimationY(GetPositionForPage(mAnimationCompletePage));
    } else {
        mAnimationCompletePage = GetPageForPosition(mContentOffsetX);
        SnapAnimationX(GetPositionForPage(mAnimationCompletePage));
    }
}

void FScrollCanvasPaged::AdjustSizeToFitPageCount() {
    if (mVertical == true) {
        mContentWidth = mWidth;
        mContentHeight = ((float)mPageCount) * mHeight;
    } else {
        mContentWidth = ((float)mPageCount) * mWidth;
        mContentHeight = mHeight;
    }
}
