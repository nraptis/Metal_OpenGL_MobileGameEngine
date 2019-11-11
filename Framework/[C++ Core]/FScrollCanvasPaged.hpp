//
//  FScrollCanvasPagedPaged.hpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 11/8/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FScrollCanvasPagedPaged_hpp
#define FScrollCanvasPagedPaged_hpp

#include "FScrollCanvasGeneric.hpp"

class FScrollCanvasPaged : public FScrollCanvasGeneric {
public:
    FScrollCanvasPaged();
    virtual ~FScrollCanvasPaged();
    
    virtual void                                    BaseLayout() override;
    virtual void                                    BaseUpdate() override;
    
    virtual void                                    BaseTouchFlush() override;
    
    virtual void                                    PanBegin(float pX, float pY) override;
    virtual void                                    PanMove(float pX, float pY) override;
    virtual void                                    PanRelease(float pX, float pY, float pSpeedX, float pSpeedY) override;
    
    virtual void                                    AnimationComplete() override;
    virtual void                                    CancelAnimation() override;
    
    void                                            SetPageCount(int pCount);
    void                                            SetPage(int pPage);
    
    virtual void                                    DidLandOnPage(int pPage);
    
    void                                            JumpToPage(int pPage);
    
    
    
    bool                                            mVertical;
    
    int                                             mPageCount;
    int                                             mPage;
    
    
    
private:
    void                                            AdjustSizeToFitPageCount();
    void                                            SnapToCurrentPage();
    int                                             GetPageForPosition(float pPosition);
    float                                           GetPositionForPage(int pPage);
    
    int                                             mAnimationCompletePage;
    
    
    
};

#endif
