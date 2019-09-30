//
//  FButton.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/23/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_BUTTON_H
#define FRAMEWORK_BUTTON_H

#include "FCanvas.hpp"
#include "FSprite.hpp"
#include "FColor.hpp"

class FButtonLayer;

class FButton : public FCanvas {
public:

    FButton();
    virtual ~FButton();
    
    void                                    SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown, float pX, float pY);
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown, FVec2 pPos) { SetUp(pSpriteUp, pSpriteOver, pSpriteDown, pPos.mX, pPos.mY); }
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown) { SetUp(pSpriteUp, pSpriteOver, pSpriteDown, mX, mY); }
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteDown, float pX, float pY) { SetUp(pSpriteUp, 0, pSpriteDown, pX, pY); }
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteDown, FVec2 pPos) { SetUp(pSpriteUp, 0, pSpriteDown, pPos.mX, pPos.mY); }
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteDown) { SetUp(pSpriteUp, 0, pSpriteDown, mX, mY); }
    
    inline void                             SetUp(FSprite *pSpriteUp, float pX, float pY){SetUp(pSpriteUp, 0, 0, pX, pY);}
    inline void                             SetUp(FSprite *pSpriteUp, FVec2 pPos){SetUp(pSpriteUp, 0, 0, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite *pSpriteUp){SetUp(pSpriteUp, 0, 0, mX, mY);}
    
    
    
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown, float pX, float pY){SetUp(&pSpriteUp, &pSpriteOver, &pSpriteDown, pX, pY);}
    
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown, FVec2 pPos){SetUp(&pSpriteUp, &pSpriteOver, &pSpriteDown, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown){SetUp(&pSpriteUp, &pSpriteOver, &pSpriteDown, mX, mY);}
    
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteDown, float pX, float pY){SetUp(&pSpriteUp, 0, &pSpriteDown, pX, pY);}
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteDown, FVec2 pPos){SetUp(&pSpriteUp, 0, &pSpriteDown, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteDown){SetUp(&pSpriteUp, 0, &pSpriteDown, mX, mY);}
    
    inline void                             SetUp(FSprite &pSpriteUp, float pX, float pY){SetUp(&pSpriteUp, 0, 0, pX, pY);}
    inline void                             SetUp(FSprite &pSpriteUp, FVec2 pPos){SetUp(&pSpriteUp, 0, 0, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite &pSpriteUp){SetUp(&pSpriteUp, 0, 0, mX, mY);}

    void                                    AddOverlay(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown);
    inline void                             AddOverlay(FSprite *pSpriteUp, FSprite *pSpriteDown){AddOverlay(pSpriteUp, 0, pSpriteDown);}
    inline void                             AddOverlay(FSprite *pSpriteUp){AddOverlay(pSpriteUp, 0, 0);}
    inline void                             AddOverlay(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown){AddOverlay(&pSpriteUp, &pSpriteOver, &pSpriteDown);}
    inline void                             AddOverlay(FSprite &pSpriteUp, FSprite &pSpriteDown){AddOverlay(&pSpriteUp, 0, &pSpriteDown);}
    inline void                             AddOverlay(FSprite &pSpriteUp){AddOverlay(&pSpriteUp, 0, 0);}

    void                                    AddUnderlay(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown);
    inline void                             AddUnderlay(FSprite *pSpriteUp, FSprite *pSpriteDown){AddUnderlay(pSpriteUp, 0, pSpriteDown);}
    inline void                             AddUnderlay(FSprite *pSpriteUp){AddUnderlay(pSpriteUp, 0, 0);}
    inline void                             AddUnderlay(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown){AddUnderlay(&pSpriteUp, &pSpriteOver, &pSpriteDown);}
    inline void                             AddUnderlay(FSprite &pSpriteUp, FSprite &pSpriteDown){AddUnderlay(&pSpriteUp, 0, &pSpriteDown);}
    inline void                             AddUnderlay(FSprite &pSpriteUp){AddUnderlay(&pSpriteUp, 0, 0);}
    
    
    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);

    virtual void                            TouchFlush();

    FList                                   mButtonLayersUnder;
    FButtonLayer                            *mButtonLayer;
    FList                                   mButtonLayersOver;

    void                                    *mClickData;

    bool                                    mTriggerOnDown;
    bool                                    mTriggerOnUp;
    
    //Note: If we use a canvas color, then we must have this flag enabled.
    //If not, then the sprites will not draw properly...
    bool                                    mDrawSetsSpriteAlphaPipelineState;
    
    
};

class FButtonLayer
{
public:
    FButtonLayer();
    virtual ~FButtonLayer();
    
    void                                    SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown);
    void                                    SetUp(FSprite *pSpriteUp, FSprite *pSpriteDown){SetUp(pSpriteUp, 0, pSpriteDown);}
    void                                    SetUp(FSprite *pSpriteUp){SetUp(pSpriteUp, 0, 0);}
    
    
    void                                    Draw(FButton *pButton, bool pActive, bool pIsOver, bool pIsDown);
    
    float                                   mWidth;
    float                                   mHeight;
    
    float                                   mOffsetX;
    float                                   mOffsetY;
    
    float                                   mRotation;
    
    float                                   mScale;
    
    FSprite                                 *mSpriteUp;
    FSprite                                 *mSpriteOver;
    FSprite                                 *mSpriteDown;
    
    FColor                                  mColorUp;
    FColor                                  mColorOver;
    FColor                                  mColorDown;
    
    bool                                    mActive;
    
};

#endif
