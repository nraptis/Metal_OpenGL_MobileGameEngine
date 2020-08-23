//
//  Util_SpritePoints.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nick Raptis on 2/28/20.
//  Copyright © 2020 Froggy Studios. All rights reserved.
//

#ifndef Util_SpritePoints_hpp
#define Util_SpritePoints_hpp

#include "FCanvas.hpp"
#include "FPointList.hpp"

class Util_SpritePoints : public FCanvas {
public:
    Util_SpritePoints();
    virtual ~Util_SpritePoints();
    
    virtual void                            Layout() override;
    
    virtual void                            Update() override;
    virtual void                            Draw() override;
    
    virtual void                            TouchDown(float pX, float pY, void *pData) override;
    virtual void                            TouchMove(float pX, float pY, void *pData) override;
    virtual void                            TouchUp(float pX, float pY, void *pData) override;
    
    void                                    SetSprite(FSprite *pSprite);
    void                                    AddSprite(FSprite *pSprite);
    void                                    ClearPoints();
    void                                    Print();
    
    FPointList                              mPointList;
    FList                                   mSpriteList;
    FSprite                                 *mSprite;
    int                                     mSpriteIndex;
    
    void                                    *mSelectedTouch;
    float                                   mSelectedStartX;
    float                                   mSelectedStartY;
    float                                   mSelectedTouchStartX;
    float                                   mSelectedTouchStartY;
    int                                     mSelectedTouchIndex;
    
    
    
    float                                   mScale;
    
    int                                     mMode;
    int                                     mSelectedPoint;
    
    float                                   mCenterX;
    float                                   mCenterY;
    
    
    
};

#endif /* Util_SpritePoints_hpp */
