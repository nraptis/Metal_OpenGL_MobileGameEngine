//
//  ProgressBar.hpp
//
//  Created by Nick Raptis on 10/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef ProgressBar_hpp
#define ProgressBar_hpp

#include "FCanvas.hpp"
#include "FPointList.hpp"

class ProgressBar : public FCanvas {
public:
    ProgressBar();
    virtual ~ProgressBar();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Draw() override;
    
    FPointList                                  mShapeList;
    
    float                                       mPercent;
    
    FTextureTriangle                            mTextureTriangle;
    
    void                                        DrawTextureLoop(FSprite *pSprite, float pX1, float pY1, float pX2, float pY2, float pX3, float pY3);
    void                                        DrawTextureLoop(FSprite *pSprite, int pIndex1, int pIndex2, int pIndex3);
    void                                        DrawTextureLoop(FSprite *pSprite);
    
    float                                       mTextureTop;
    float                                       mTextureBottom;
    
    float                                       mBubbleOffsetU;
    float                                       mStripeOffsetU;
    
    float                                       mTextureOffsetU;
};

#endif
