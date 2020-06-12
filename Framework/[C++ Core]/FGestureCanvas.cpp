//
//  FGestureCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "FGestureCanvas.hpp"
#include "core_includes.h"

FTrackedTouch::FTrackedTouch() {
    Reset(0.0f, 0.0f, 0);
    mHistoryMoveCount = 0;
}

FTrackedTouch::~FTrackedTouch() {
    
}

void FTrackedTouch::Reset(float pX, float pY, void *pData) {
    mX = pX;
    mY = pY;
    mStartX = pX;
    mStartY = pY;
    mMaxDistMoved = 0.0f;
    mTimer = 0;
    mData = pData;
    mHistoryMoveX[0] = pX;
    mHistoryMoveY[0] = pY;
    mHistoryMoveTime[0] = mTimer;
    mHistoryMoveCount = 1;
}

void FTrackedTouch::Move(float pX, float pY) {
    mX = pX;
    mY = pY;
    float aDiffX = (pX - mStartX);
    float aDiffY = (pY - mStartY);
    if(aDiffX < 0)aDiffX = (-aDiffX);
    if(aDiffY < 0)aDiffY = (-aDiffY);
    if(aDiffX > mMaxDistMoved)mMaxDistMoved = aDiffX;
    if(aDiffY > mMaxDistMoved)mMaxDistMoved = aDiffY;
    if (mHistoryMoveCount == GESTURE_TOUCH_COUNT) {
        for(int i=1;i<GESTURE_TOUCH_COUNT;i++)mHistoryMoveX[i - 1] = mHistoryMoveX[i];
        for(int i=1;i<GESTURE_TOUCH_COUNT;i++)mHistoryMoveY[i - 1] = mHistoryMoveY[i];
        for(int i=1;i<GESTURE_TOUCH_COUNT;i++)mHistoryMoveTime[i - 1] = mHistoryMoveTime[i];
        mHistoryMoveX[GESTURE_TOUCH_COUNT - 1] = pX;
        mHistoryMoveY[GESTURE_TOUCH_COUNT - 1] = pY;
        mHistoryMoveTime[GESTURE_TOUCH_COUNT - 1] = mTimer;
    } else {
        mHistoryMoveX[mHistoryMoveCount] = pX;
        mHistoryMoveY[mHistoryMoveCount] = pY;
        mHistoryMoveTime[mHistoryMoveCount] = mTimer;
        mHistoryMoveCount++;
    }
}

FGestureCanvas::FGestureCanvas() {
    mTouchCount = 0;

    mIsPanning = false;
    mIsPinching = false;
    mIsRotating = false;

    mGesturePanTerminatedFromFingerRelease = false;

    mGesturePanRequiredTouches = 1;

    mGesturePanStartX = 0.0f;
    mGesturePanStartY = 0.0f;

    mGesturePanStartCenterX = 0.0f;
    mGesturePanStartCenterY = 0.0f;

    mGestureTouchCenterX = 0;
    mGestureTouchCenterY = 0;

    mGesturePanDistX = 0.0f;
    mGesturePanDistY = 0.0f;

    mGesturePanPreviousCenterX = 0.0f;
    mGesturePanPreviousCenterY = 0.0f;

    mGestureTapLastTapTimer = 0;
    mGestureTapLastTapCount = 0;
    mGestureTapQueued = false;

    mGestureTranslateX = 0.0f;
    mGestureTranslateY = 0.0f;

    mGesturePinchX1 = 0.0f;
    mGesturePinchY1 = 0.0f;
    mGesturePinchX2 = 0.0f;
    mGesturePinchY2 = 0.0f;

    mGesturePinchStartDist = 0.0f;
    mGesturePinchScale = 1.0f;

    mGestureRotateStartAngle = 0.0f;

    for (int i=0;i<MAX_GESTURE_TOUCHES;i++) {
        mTouch[i] = new FTrackedTouch();
    }
}

FGestureCanvas::~FGestureCanvas() {
    for (int i=0;i<MAX_GESTURE_TOUCHES;i++) {
        delete mTouch[i];
        mTouch[i] = 0;
    }
}

void FGestureCanvas::BaseUpdate() {
    FCanvas::BaseUpdate();
    
    int aKillTouchIndex = -1;
    
    for (int i=0;i<mTouchCount;i++) {
        mTouch[i]->mTimer++;
        if (mTouch[i]->mHistoryMoveCount > 0) {
            if ((mTouch[i]->mTimer - mTouch[i]->mHistoryMoveTime[i]) > 500) {
                Log("Touch Expire [%p] (%d - %d) [%d]\n", mTouch[i]->mData, mTouch[i]->mTimer, mTouch[i]->mHistoryMoveTime[i], mTouch[i]->mTimer - mTouch[i]->mHistoryMoveTime[i]);
                aKillTouchIndex = i;
            }
        } else {
            if (mTouch[i]->mTimer > 500) {
                aKillTouchIndex = i;
            }
        }
    }
    
    if (aKillTouchIndex != -1) {
        Log("Kill Touch: %p\n", mTouch[aKillTouchIndex]->mData);
        FTrackedTouch *aReleasedTouch = mTouch[aKillTouchIndex];
        for (int i=aKillTouchIndex+1;i<mTouchCount;i++) {
            mTouch[i-1] = mTouch[i];
        }
        mTouch[mTouchCount - 1] = aReleasedTouch;
        mTouchCount--;
    }
    
    if(mGestureTapQueued) {
        mGestureTapLastTapTimer++;
        if (mGestureTapLastTapTimer > 16) {
            mGestureTapQueued = false;
            mGestureTapLastTapTimer = 0;
            mGestureTapLastTapCount = 0;
        }
    }
}

FCanvas *FGestureCanvas::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed) {
    FCanvas *aChild = FCanvas::BaseTouchDown(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent, pConsumed);

    if (AllowGestures() == false) {
        if ((mIsPanning == true) || (mIsPanning == true) || (mIsRotating == true)) {
            ClearGestures(false);
        }
        BaseTouchFlush();
        return aChild;
    }
    
    bool aContainsPoint = mTransformAbsolute.ContainsPoint(pX, pY);
    bool aTrack = false;
    bool aIsChild = (aChild == this);

    if (!pOutsideParent) {
        if (aIsChild) { aTrack = true; }
    }
    if (aContainsPoint && mRecievesConsumedTouches) {
        if (aIsChild) {
            aTrack = true;
        }
    }
    if (aTrack) {
        FTrackedTouch *aTouch = 0;
        if (mTouchCount < MAX_GESTURE_TOUCHES) {
            for (int i = 0; i < mTouchCount; i++) {
                if (mTouch[i]->mData == pData) {
                    aTouch = mTouch[i];
                }
            }
            if (aTouch == 0) {
                aTouch = mTouch[mTouchCount];
                mTouchCount++;
            }
        } else {
            aTouch = mTouch[0];
            for (int i=1;i<MAX_GESTURE_TOUCHES;i++) {
                mTouch[i-1] = mTouch[i];
            }
            mTouch[MAX_GESTURE_TOUCHES - 1] = aTouch;
        }

        if (aTouch) {
            aTouch->Reset(mTouchX, mTouchY, pData);
            GestureComputeCenter();
            if (mIsPanning) {
                mGesturePanStartCenterX = mGestureTouchCenterX;
                mGesturePanStartCenterY = mGestureTouchCenterY;

                mGesturePanPreviousCenterX = mGestureTouchCenterX;
                mGesturePanPreviousCenterY = mGestureTouchCenterY;

                mGesturePanDistX = 0.0f;
                mGesturePanDistY = 0.0f;

                //A new finger came down, we have reset all our distance
                //info and this have started a new "pan"...
                PanBegin(0.0f, 0.0f);
            }
        }
    }
    return aChild;
}

void FGestureCanvas::BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {

    FCanvas::BaseTouchMove(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);

    if (AllowGestures() == false) {
        if ((mIsPanning == true) || (mIsPanning == true) || (mIsRotating == true)) {
            ClearGestures(false);
        }
        BaseTouchFlush();
        return;
    }
    
    int aTouchIndex = -1;
    for (int i=0;i<mTouchCount;i++) {
        if (mTouch[i]->mData == pData) {
            aTouchIndex = i;
            break;
        }
    }

    if(aTouchIndex >= 0)
    {
        FTrackedTouch *aMovedTouch = mTouch[aTouchIndex];
        aMovedTouch->Move(mTouchX, mTouchY);

        GestureComputeCenter();

        float aTriggerPanDistance = 4.0f;
        //if ((gDeviceWidth > 600.0f) || (gDeviceHeight > 600.0f)) { aTriggerPanDistance = 6.0f; }
        

        float aTriggerPinchDistance = 1.0f;
        //if((gDeviceWidth > 600.0f) || (gDeviceHeight > 600.0f))aTriggerPinchDistance = 10.0f;

        float aPinchSize = 24.0f;


        if (mIsPanning == false) {
            if (mTouchCount >= mGesturePanRequiredTouches) {
                if (aMovedTouch->mMaxDistMoved > aTriggerPanDistance && mGesturePanTerminatedFromFingerRelease == false) {
                    mIsPanning = true;

                    mGesturePanStartCenterX = mGestureTouchCenterX;
                    mGesturePanStartCenterY = mGestureTouchCenterY;

                    mGesturePanPreviousCenterX = mGestureTouchCenterX;
                    mGesturePanPreviousCenterY = mGestureTouchCenterY;

                    mGesturePanDistX = (mGestureTouchCenterX - mGesturePanStartCenterX);
                    mGesturePanDistY = (mGestureTouchCenterY - mGesturePanStartCenterY);

                    //PanBegin(mGesturePanStartCenterX + mGesturePanDistX, mGesturePanStartCenterY + mGesturePanDistY);
                    PanBegin(0.0f, 0.0f);

                    Pan(mGesturePanDistX, mGesturePanDistY);
                }
            }
        } else {
            mGesturePanDistX = (mGestureTouchCenterX - mGesturePanStartCenterX);
            mGesturePanDistY = (mGestureTouchCenterY - mGesturePanStartCenterY);

            Pan(mGesturePanDistX, mGesturePanDistY);
        }

        if (mIsPinching == false) {
            if (mTouchCount >= 2) {
                if (true)//aMovedTouch->mMaxDistMoved > aPinchSize)
                {
                    mGesturePinchStartDist = Distance(mTouch[0]->mStartX, mTouch[0]->mStartY, mTouch[1]->mStartX, mTouch[1]->mStartY);
                    mGesturePinchScale = 1.0f;
                    if (mGesturePinchStartDist > aPinchSize) {


                        mIsPinching = true;
                        float aDist = Distance(mTouch[0]->mX, mTouch[0]->mY, mTouch[1]->mX, mTouch[1]->mY);

                        mGesturePinchStartDist = aDist;

                        //mGesturePinchScale = (aDist / mGesturePinchStartDist);
                        mGesturePinchScale = 1.0f;

                        PinchBegin(1.0f);
                        Pinch(mGesturePinchScale);
                    }
                }
            }
        } else {
            if (mTouchCount >= 2) {
                if (mGesturePinchStartDist > aPinchSize) {
                    float aDist = Distance(mTouch[0]->mX, mTouch[0]->mY, mTouch[1]->mX, mTouch[1]->mY);
                    mGesturePinchScale = (aDist / mGesturePinchStartDist);
                    Pinch(mGesturePinchScale);
                }
            }
            else
            {
                PinchEnd(mGesturePinchScale);
                mIsPinching = false;
            }
        }
        
        if (mIsRotating == false) {
            if (mTouchCount >= 2) {
                if(aMovedTouch->mMaxDistMoved > aTriggerPinchDistance) {
                    float aDist = Distance(mTouch[0]->mStartX, mTouch[0]->mStartY, mTouch[1]->mStartX, mTouch[1]->mStartY);
                    if (aDist > 36.0f) {
                        mIsRotating = true;
                        mGestureRotateStartAngle = FaceTarget(mTouch[0]->mStartX, mTouch[0]->mStartY, mTouch[1]->mStartX, mTouch[1]->mStartY);
                        float aAngle = FaceTarget(mTouch[0]->mX, mTouch[0]->mY, mTouch[1]->mX, mTouch[1]->mY);
                        mGestureRotateDegrees = DistanceBetweenAngles(mGestureRotateStartAngle, aAngle);
                        RotateStart(0.0f);
                        Rotate(mGestureRotateDegrees);
                    }
                }
            }
        } else {
            if (mTouchCount >= 2) {
                if (mGesturePinchStartDist > 36.0f) {
                    float aAngle = FaceTarget(mTouch[0]->mX, mTouch[0]->mY, mTouch[1]->mX, mTouch[1]->mY);
                    mGestureRotateDegrees = DistanceBetweenAngles(mGestureRotateStartAngle, aAngle);
                    Rotate(mGestureRotateDegrees);
                }
            } else {
                RotateEnd(mGestureRotateDegrees);
                mIsRotating = false;
            }
        }
    }
}

void FGestureCanvas::BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {
    FCanvas::BaseTouchUp(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);

    if (AllowGestures() == false) {
        if ((mIsPanning == true) || (mIsPanning == true) || (mIsRotating == true)) {
            ClearGestures(false);
        }
        BaseTouchFlush();
        return;
    }
    
    int aTouchIndex = -1;

    for (int i=0;i<mTouchCount;i++) {
        if (mTouch[i]->mData == pData) {
            aTouchIndex = i;
            break;
        }
    }

    if (aTouchIndex >= 0) {
        FTrackedTouch *aReleasedTouch = mTouch[aTouchIndex];
        for(int i=aTouchIndex+1;i<mTouchCount;i++)mTouch[i-1] = mTouch[i];
        mTouch[mTouchCount - 1] = aReleasedTouch;
        mTouchCount--;
        GestureComputeCenter();
        if (mIsPinching) {
            PinchEnd(mGesturePinchScale);
            mIsPinching = false;
        }

        if (mIsRotating) {
            RotateEnd(mGestureRotateDegrees);
            mIsRotating = false;
        }

        if (mTouchCount > 0) {
            mGesturePanTerminatedFromFingerRelease = true;
        } else {
            mGesturePanTerminatedFromFingerRelease = false;
        }

        if (mIsPanning) {
            //if (mTouchCount == 0) {
                float aReleaseSpeedX = 0.0f;
                float aReleaseSpeedY = 0.0f;
                int aReleaseTime = (aReleasedTouch->mTimer - 6);
                int aReleaseConsiderCount = 0;
                for (int i=(aReleasedTouch->mHistoryMoveCount - 2);i >= 0;i--) {
                    if (aReleasedTouch->mHistoryMoveTime[i + 1] >= aReleaseTime) {
                        int aTimeDiff = (aReleasedTouch->mHistoryMoveTime[i + 1] - aReleasedTouch->mHistoryMoveTime[i]);
                        float aXDiff = (aReleasedTouch->mHistoryMoveX[i + 1] - aReleasedTouch->mHistoryMoveX[i]);
                        float aYDiff = (aReleasedTouch->mHistoryMoveY[i + 1] - aReleasedTouch->mHistoryMoveY[i]);
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
                PanEnd(aReleasedTouch->mX, aReleasedTouch->mY, aReleaseSpeedX, aReleaseSpeedY);
                mIsPanning = false;
            //} else {
            //    mGesturePanStartCenterX = mGestureTouchCenterX;
            //    mGesturePanStartCenterY = mGestureTouchCenterY;
            //    mGesturePanPreviousCenterX = mGestureTouchCenterX;
            //    mGesturePanPreviousCenterY = mGestureTouchCenterY;
            //    mGesturePanDistX = 0.0f;
            //    mGesturePanDistY = 0.0f;

                //One of several fingers has been released, we are
                //starting a new pan gesture through continuous flow.
            //    PanBegin(0.0f, 0.0f);
            //}
            
        } else {
            if (mTouchCount == 0) {
                
                //TODO: Apple seems to have sped up updates, need to fix. Higher number for now...
                //if (aReleasedTouch->mTimer <= 12) {
                
                if (aReleasedTouch->mTimer <= 60) {
                    mGestureTapLastTapCount++;
                    mGestureTapQueued = true;
                    if (mGestureTapLastTapCount == 1) {
                        mGestureTapLastTapTimer = 0;
                        TapSingle(aReleasedTouch->mX, aReleasedTouch->mY);
                    } else if(mGestureTapLastTapCount == 2) {
                        TapDouble(aReleasedTouch->mX, aReleasedTouch->mY);
                        mGestureTapLastTapCount = 0;
                    }
                } else {
                    mGestureTapLastTapTimer = 0;
                    mGestureTapLastTapCount = 0;
                    mGestureTapQueued = false;
                }
            } else {
                mGestureTapLastTapTimer = 0;
                mGestureTapLastTapCount = 0;
                mGestureTapQueued = false;
            }
        }
    }
}

void FGestureCanvas::BaseTouchFlush() {
    FCanvas::BaseTouchFlush();
    
    
    
}

void FGestureCanvas::GestureComputeCenter() {
    mGestureTouchCenterX = 0.0f;
    mGestureTouchCenterY = 0.0f;
    
    for (int i=0;i<mTouchCount;i++) {
        mGestureTouchCenterX += mTouch[i]->mX;
        mGestureTouchCenterY += mTouch[i]->mY;
    }

    mGestureTouchCenterX /= ((float)mTouchCount);
    mGestureTouchCenterY /= ((float)mTouchCount);
}

void FGestureCanvas::PanBegin(float pX, float pY) {
    
}

void FGestureCanvas::Pan(float pX, float pY) {
    
}

void FGestureCanvas::PanEnd(float pX, float pY, float pSpeedX, float pSpeedY) {

}


void FGestureCanvas::PinchBegin(float pScale) {

}

void FGestureCanvas::Pinch(float pScale) {

}

void FGestureCanvas::PinchEnd(float pScale) {

}

void FGestureCanvas::TapSingle(float pX, float pY) {
    
}

void FGestureCanvas::TapDouble(float pX, float pY) {
    
}

void FGestureCanvas::RotateStart(float pRotation) {
    
}

void FGestureCanvas::Rotate(float pRotation) {
    
}

void FGestureCanvas::RotateEnd(float pRotation) {
    
}

void FGestureCanvas::ClearGestures(bool pEndActive) {
    if (pEndActive == true) {
        if (mIsPanning == true) {
            mIsPanning = false;
            PanEnd(mGesturePanDistX, mGesturePanDistY, 0.0f, 0.0f);
        }
        if (mIsPinching == true) {
            mIsPinching = false;
            PinchEnd(mGesturePinchScale);
        }
    } else {
        mIsPanning = false;
        mIsPinching = false;
    }
}
