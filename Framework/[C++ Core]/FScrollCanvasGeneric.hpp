//
//  FScrollCanvasGenericGeneric.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 11/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FScrollCanvasGenericGeneric_hpp
#define FScrollCanvasGenericGeneric_hpp

#include "FGestureCanvas.hpp"

#define SCROLL_CANVAS_ANIMATION_TYPE_NONE 0
#define SCROLL_CANVAS_ANIMATION_TYPE_SNAP 1
#define SCROLL_CANVAS_ANIMATION_TYPE_DECAY 2
#define SCROLL_CANVAS_ANIMATION_TYPE_DECELERATE 3
#define SCROLL_CANVAS_ANIMATION_TYPE_REST 4


#define SCROLL_CANVAS_HAND_OFF_TYPE_STOP 0
#define SCROLL_CANVAS_HAND_OFF_TYPE_DECAY 2




class FScrollCanvasGeneric : public FCanvas {
    
    friend class FScrollCanvas;
    friend class FScrollCanvasPaged;
    
public:
    FScrollCanvasGeneric();
    virtual ~FScrollCanvasGeneric();
    
    virtual void                                    BaseUpdate();
    
    virtual FCanvas                                 *BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed);
    virtual void                                    BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    virtual void                                    BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    virtual void                                    BaseTouchFlush();
    
    virtual void                                    AnimationComplete();
    virtual void                                    CancelAnimation();
    
    virtual bool                                    AllowInteraction() { return true; }
    
    void                                            SetContentSize(float pWidth, float pHeight);
    
    bool                                            IsAnimating() { return ((mAnimatingX == true) || (mAnimatingY == true)); }
    
    float                                           mContentWidth;
    float                                           mContentHeight;
    
    float                                           mContentOffsetX;
    float                                           mContentOffsetY;
    
    float                                           mReleaseFlingThreshold;
    
    float                                           mDecayMultiply;
    float                                           mDecaySubtract;
    
    float                                           mDecayMultiplyHandedOff;
    float                                           mDecaySubtractHandedOff;
    
    
    
    float                                           mMaxFlingSpeed;
    
    float                                           mOvershootCorrectionSpeed;
    float                                           mOvershootAntiDirectionMultiply;
    
private:
    
    virtual void                                    PanBegin(float pX, float pY);
    virtual void                                    PanMove(float pX, float pY);
    virtual void                                    PanRelease(float pX, float pY, float pSpeedX, float pSpeedY);
    
    FTrackedTouch                                   mTouch;
    
    bool                                            IsOutOfBoundsX(float pScrollX);
    bool                                            IsOutOfBoundsY(float pScrollY);
    
    
    
    void                                            OutOfBoundsSnapToEdgeX();
    void                                            OutOfBoundsSnapToEdgeY();
    
    
    //Assumption: The values passed in are already out of bounds...
    float                                           GetDampenedX(float pScrollX);
    float                                           GetDampenedY(float pScrollY);
    
    
    
    
    
    bool                                            mAnimatingX;
    bool                                            mAnimatingY;
    
    int                                             mAnimationTypeX;
    int                                             mAnimationTypeY;
    
    
    float                                           GetDecayStopPosition(float pStart, float pVelocity);
    float                                           GetDecayStopPosition(float pStart, float pVelocity, float pAccel, float pSubtract);
    
    void                                            SnapAnimationX(float pTargetX);
    void                                            SnapAnimationY(float pTargetY);
    
    void                                            DecayAnimationX(float pVelocity, bool pHandedOff);
    void                                            DecayAnimationY(float pVelocity, bool pHandedOff);
    
    void                                            DecelerateAnimationX(float pTargetPos, float pStartVelocity, float pTargetVelocity, int pTicks, int pHandOffType);
    void                                            DecelerateAnimationY(float pTargetPos, float pStartVelocity, float pTargetVelocity, int pTicks, int pHandOffType);
    
    void                                            RestAnimationX(float pTargetPos, float pVelocity);
    void                                            RestAnimationY(float pTargetPos, float pVelocity);
    
    
    void                                            UpdateSnapAnimationX();
    void                                            UpdateSnapAnimationY();
    
    void                                            UpdateDecayAnimationX();
    void                                            UpdateDecayAnimationY();
    
    void                                            UpdateDecelerateAnimationX();
    void                                            UpdateDecelerateAnimationY();
    
    void                                            UpdateRestAnimationX();
    void                                            UpdateRestAnimationY();
    
    
    float                                           mAnimationSnapTargetX;
    float                                           mAnimationSnapTargetY;
    
    float                                           mAnimationDecayVelocityX;
    bool                                            mAnimationDecayHandedOffX;
    float                                           mAnimationDecayVelocityY;
    bool                                            mAnimationDecayHandedOffY;
    float                                           mAnimationDecayVelocityDampeningFactor;
    
    
    
    int                                             mAnimationDecelerateTickX;
    int                                             mAnimationDecelerateTimeX;
    int                                             mAnimationDecelerateHandoffTypeX;
    float                                           mAnimationDeceleratePositionStartX;
    float                                           mAnimationDeceleratePositionEndX;
    float                                           mAnimationDecelerateVelocityStartX;
    float                                           mAnimationDecelerateVelocityEndX;
    float                                           mAnimationDecelerateVelocityCoef1X;
    float                                           mAnimationDecelerateVelocityCoef2X;
    float                                           mAnimationDecelerateVelocityCoef3X;
    int                                             mAnimationDecelerateTickY;
    int                                             mAnimationDecelerateTimeY;
    int                                             mAnimationDecelerateHandoffTypeY;
    float                                           mAnimationDeceleratePositionStartY;
    float                                           mAnimationDeceleratePositionEndY;
    float                                           mAnimationDecelerateVelocityStartY;
    float                                           mAnimationDecelerateVelocityEndY;
    float                                           mAnimationDecelerateVelocityCoef1Y;
    float                                           mAnimationDecelerateVelocityCoef2Y;
    float                                           mAnimationDecelerateVelocityCoef3Y;
    
    float                                           mAnimationRestTargetX;
    float                                           mAnimationRestVelocityX;
    float                                           mAnimationRestMultiplyVelocityX;
    bool                                            mAnimationRestWillOvershootX;
    bool                                            mAnimationRestDidOvershootX;
    int                                             mAnimationRestTickX;
    int                                             mAnimationRestDirectionX;
    float                                           mAnimationRestTargetY;
    float                                           mAnimationRestVelocityY;
    float                                           mAnimationRestMultiplyVelocityY;
    bool                                            mAnimationRestWillOvershootY;
    bool                                            mAnimationRestDidOvershootY;
    int                                             mAnimationRestTickY;
    int                                             mAnimationRestDirectionY;
    
    
    //SCROLL_CANVAS_ANIMATION_TYPE_SNAP
    
    
    //Based on thought experiment, releasing should work in the following way...
    //We have a fixed deceleration animation.
    //The deceleration animation hands off to a "snap-back" animation at the screen's edge...
    
    //This can be encapsulated in a "rubber-band" animation, which the
    
    float                                           GetOutOfBoundsDampenedDrag(float pAmount);
    float                                           mOutOfBoundsRangeBaseDampened;
    float                                           mOutOfBoundsRangeBaseActual;
    
    
    
    float                                           mPanStartX;
    float                                           mPanStartY;
    float                                           mPanStartContentOffsetX;
    float                                           mPanStartContentOffsetY;
    
    float                                           mPanX;
    float                                           mPanY;
    
    float                                           mPanDiffX;
    float                                           mPanDiffY;
    
    
};

#endif /* FScrollCanvasGenericGeneric_hpp */
