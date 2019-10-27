//
//  FScrollCanvasPaged.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/13/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FScrollCanvasPaged_hpp
#define FScrollCanvasPaged_hpp

#include "FGestureCanvas.hpp"

class FScrollCanvasPaged : public FGestureCanvas {
public:
    
    FScrollCanvasPaged();
    virtual ~FScrollCanvasPaged();
    
    virtual void                            BaseUpdate();
    
    void                                    SetPageCountHorizontal(int pCount);
    void                                    SetPageCountVertical(int pCount);
    void                                    SetPageCount(int pCountHorizontal, int pCountVertical){SetPageCountHorizontal(pCountHorizontal);SetPageCountVertical(pCountVertical);}
    
    void                                    SnapToPage(int pPageH, int pPageV);
    
    int                                     mScrollPageCountH;
    int                                     mScrollPageCountV;
    
    virtual void                            ScrollFinished();
    virtual void                            ScrollFinishedHorizontal(int pStartRow, int pEndRow);
    virtual void                            ScrollFinishedVertical(int pStartCol, int pEndCol);
    
    virtual void                            PanBegin(float pX, float pY);
    virtual void                            Pan(float pX, float pY);
    virtual void                            PanEnd(float pX, float pY, float pSpeedX, float pSpeedY);
    
    //virtual bool                            Allow();
    
    
    int                                     mScrollCurrentPageH;
    int                                     mScrollCurrentPageV;
    
    int                                     mScrollAnimationTimeTotal;
    int                                     mScrollAnimationTimer;
    
    bool                                    mScrollAnimating;
    
    float                                   mSpeedThresholdFlingTo;
    
    float                                   mScrollOffset[2];
    float                                   mScrollOffsetPanShift[2];
    float                                   mScrollOffsetPanStart[2];
    
    int                                     mAnimationDirection;
    int                                     mFinishAnimationDirection;
    
    bool                                    mFinishAnimation;
    
    float                                   mScrollAnimationPercent;
    float                                   mScrollAnimationPercentTarget;
    
    float                                   mScrollPanStartThreshold;
    float                                   mScrollPanSwitchDirectionThreshold;
    
    bool                                    mScrollPanning;
    bool                                    mScrollPanDirectionPicked;
    
    bool                                    mScrollHorizontal;
    
    bool                                    mScrollEnabledHorizontal;
    bool                                    mScrollEnabledVertical;
    
    float                                   ScrollGetBounceDragShift(float pAmount);
};

#endif
