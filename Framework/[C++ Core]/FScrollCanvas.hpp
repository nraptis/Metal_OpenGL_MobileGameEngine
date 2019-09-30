//
//  FScrollCanvas.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FScrollCanvas_hpp
#define FScrollCanvas_hpp

#include "FGestureCanvas.hpp"

class FScrollCanvas : public FGestureCanvas {
public:
    
    FScrollCanvas();
    virtual ~FScrollCanvas();
    
    virtual void                            BaseUpdate();
    virtual void                            BaseLayout();


    virtual FCanvas                         *BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed);


    virtual void                            ScrollFinished();

    virtual void                            PanBegin(float pX, float pY);
    virtual void                            Pan(float pX, float pY);
    virtual void                            PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);

    void                                    SetContentSize(float pWidth, float pHeight);
    
    bool                                    PositionIsOutOfBoundsOver(float pValue, int pIndex);
    bool                                    PositionIsOutOfBoundsUnder(float pValue, int pIndex);

    float                                   mScrollUpdateFlingDecayMultiply;
    float                                   mScrollUpdateFlingDecaySubtract;

    float                                   mScrollOffset[2];
    float                                   mScrollStartOffset[2];

    float                                   mScrollTargetOffset[2];

    float                                   mScrollFlingSpeed;
    float                                   mScrollFlingDir[2];

    float                                   mScrollContentSizeWidth;
    float                                   mScrollContentSizeHeight;

    float                                   mScrollMinOffset[2];

    float                                   mScrollBounceBackStartOffset[2];
    float                                   mScrollBounceBackFinishOffset[2];
    float                                   mScrollBounceBackStartSpeed[2];
    float                                   mScrollBounceBackFinishSpeed[2];
    float                                   mScrollBounceBackAdjustmentPre[2];
    float                                   mScrollBounceBackAdjustmentPost[2];
    int                                     mScrollBounceBackTimeTotal[2];
    int                                     mScrollBounceBackTime[2];

    float                                   mScrollMaxDistance;
    
    float                                   ScrollGetBounceDragShift(float pAmount);

    void                                    ScrollBounce(int pIndex);

    bool                                    ScrollIsAnimating();

    bool                                    mScrollHorizontalDisabledIfTooSmall;
    bool                                    mScrollVerticalDisabledIfTooSmall;

    bool                                    mScrollHorizontalEnabled;
    bool                                    mScrollVerticalEnabled;
};

#endif /* FScrollCanvas_hpp */
