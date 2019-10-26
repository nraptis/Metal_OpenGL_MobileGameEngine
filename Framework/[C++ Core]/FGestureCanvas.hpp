//
//  FGestureCanvas.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FGestureCanvas_hpp
#define FGestureCanvas_hpp

#define MAX_GESTURE_TOUCHES 10
#define GESTURE_TOUCH_COUNT 8

#include "FCanvas.hpp"
#include "FObject.hpp"

class FTrackedTouch : public FObject {
public:

    FTrackedTouch();
    ~FTrackedTouch();

    void                        Reset(float pX, float pY, void *pData);
    void                        Move(float pX, float pY);

    float                       mHistoryMoveX[GESTURE_TOUCH_COUNT];
    float                       mHistoryMoveY[GESTURE_TOUCH_COUNT];
    int                         mHistoryMoveTime[GESTURE_TOUCH_COUNT];
    int                         mHistoryMoveCount;

    float                       mX;
    float                       mY;

    float                       mStartX;
    float                       mStartY;

    float                       mMaxDistMoved;

    //Basically, if it is "resting" for too long, flush it out of the system.
    int                         mTimer;

    void                        *mData;

};

class FGestureCanvas : public FCanvas {
public:
    FGestureCanvas();
    virtual ~FGestureCanvas();

    virtual void                                    PanBegin(float pX, float pY);
    virtual void                                    Pan(float pX, float pY);
    virtual void                                    PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);

    virtual void                                    PinchBegin(float pScale);
    virtual void                                    Pinch(float pScale);
    virtual void                                    PinchEnd(float pScale);

    virtual void                                    TapSingle(float pX, float pY);
    virtual void                                    TapDouble(float pX, float pY);

    virtual void                                    RotateStart(float pRotation);
    virtual void                                    Rotate(float pRotation);
    virtual void                                    RotateEnd(float pRotation);

    virtual void                                    BaseUpdate();
    
    // Basically, this can be used to prevent new gestures from coming in and cancel existing gestures...
    virtual bool                                    AllowGestures() { return true; }
    

    FTrackedTouch                                   *mTouch[MAX_GESTURE_TOUCHES];
    int                                             mTouchCount;

    virtual FCanvas                                 *BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed);
    virtual void                                    BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    virtual void                                    BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    virtual void                                    BaseTouchFlush();

    void                                            GestureComputeCenter();

    bool                                            mIsPanning;
    int                                             mGesturePanRequiredTouches;

    bool                                            mGesturePanTerminatedFromFingerRelease;

    float                                           mGestureTouchCenterX;
    float                                           mGestureTouchCenterY;

    float                                           mGesturePanStartCenterX;
    float                                           mGesturePanStartCenterY;

    float                                           mGesturePanPreviousCenterX;
    float                                           mGesturePanPreviousCenterY;

    float                                           mGesturePanStartX;
    float                                           mGesturePanStartY;

    float                                           mGesturePanDistX;
    float                                           mGesturePanDistY;

    float                                           mGestureTranslateX;
    float                                           mGestureTranslateY;

    bool                                            mGestureTapQueued;
    int                                             mGestureTapLastTapTimer;
    int                                             mGestureTapLastTapCount;

    bool                                            mIsPinching;
    bool                                            mIsRotating;

    float                                           mGesturePinchX1;
    float                                           mGesturePinchY1;
    float                                           mGesturePinchX2;
    float                                           mGesturePinchY2;

    float                                           mGesturePinchStartDist;
    float                                           mGesturePinchScale;

    float                                           mGestureRotateStartAngle;
    float                                           mGestureRotateDegrees;

    void                                            ClearGestures(bool pEndActive);
};

#endif


