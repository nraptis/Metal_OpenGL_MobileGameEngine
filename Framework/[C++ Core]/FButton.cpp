//
//  FButton.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/23/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#include "FButton.hpp"
#include "core_includes.h"

FButton::FButton() {
    mName = "Button";

    mClickData = NULL;

    mDrawManual = false;

    mTriggerOnDown = false;
    mTriggerOnUp = true;
    
    mButtonLayer = new FButtonLayer();
    
    mDrawSetsSpriteAlphaPipelineState = true;
}

FButton::~FButton() {
    FreeList(FButtonLayer, mButtonLayersUnder);
    FreeList(FButtonLayer, mButtonLayersOver);
    delete mButtonLayer;
    mButtonLayer = NULL;
}

void FButton::AddOverlay(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown) {
    FButtonLayer *aLayer = new FButtonLayer();
    aLayer->SetUp(pSpriteUp, pSpriteOver, pSpriteDown);
    mButtonLayersOver.Add(aLayer);
    
    if(mWidth < aLayer->mWidth)SetWidth(aLayer->mWidth);
    if(mHeight < aLayer->mHeight)SetHeight(aLayer->mHeight);
}

void FButton::AddUnderlay(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown) {
    FButtonLayer *aLayer = new FButtonLayer();
    aLayer->SetUp(pSpriteUp, pSpriteOver, pSpriteDown);
    mButtonLayersUnder.Add(aLayer);
    
    if(mWidth < aLayer->mWidth)SetWidth(aLayer->mWidth);
    if(mHeight < aLayer->mHeight)SetHeight(aLayer->mHeight);
}

void FButton::SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown, float pX, float pY) {
    if (mButtonLayer == NULL) {
        mButtonLayer = new FButtonLayer();
    }
    mButtonLayer->SetUp(pSpriteUp, pSpriteOver, pSpriteDown);
    
    float aWidth = mWidth;
    float aHeight = mHeight;
    
    if(aWidth < mButtonLayer->mWidth)aWidth = mButtonLayer->mWidth;
    if(aHeight < mButtonLayer->mHeight)aHeight = mButtonLayer->mHeight;
    
    SetFrame(pX, pY, aWidth, aHeight);
}

void FButton::SetTopOverlayOffsetUp(float pX, float pY) {
    FButtonLayer *aLayer = (FButtonLayer *)(mButtonLayersOver.Last());
    if (aLayer != NULL) {
        aLayer->mOffsetUpX = pX;
        aLayer->mOffsetUpY = pY;
    }
}

void FButton::SetTopOverlayOffsetOver(float pX, float pY) {
    FButtonLayer *aLayer = (FButtonLayer *)(mButtonLayersOver.Last());
    if (aLayer != NULL) {
        aLayer->mOffsetOverX = pX;
        aLayer->mOffsetOverY = pY;
    }
}
void FButton::SetTopOverlayOffsetDown(float pX, float pY) {
    FButtonLayer *aLayer = (FButtonLayer *)(mButtonLayersOver.Last());
    if (aLayer != NULL) {
        aLayer->mOffsetDownX = pX;
        aLayer->mOffsetDownY = pY;
    }
}

void FButton::SetTopUnderlayOffsetUp(float pX, float pY) {
    FButtonLayer *aLayer = (FButtonLayer *)(mButtonLayersUnder.Last());
    if (aLayer != NULL) {
        aLayer->mOffsetUpX = pX;
        aLayer->mOffsetUpY = pY;
    }
}

void FButton::SetTopUnderlayOffsetOver(float pX, float pY) {
    FButtonLayer *aLayer = (FButtonLayer *)(mButtonLayersUnder.Last());
    if (aLayer != NULL) {
        aLayer->mOffsetOverX = pX;
        aLayer->mOffsetOverY = pY;
    }
}

void FButton::SetTopUnderlayOffsetDown(float pX, float pY) {
    FButtonLayer *aLayer = (FButtonLayer *)(mButtonLayersUnder.Last());
    if (aLayer != NULL) {
        aLayer->mOffsetDownX = pX;
        aLayer->mOffsetDownY = pY;
    }
}

void FButton::Draw() {
    if (mDrawSetsSpriteAlphaPipelineState == true && mColor.mAlpha != 0.0f) {
        Graphics::PipelineStateSetShape2DAlphaBlending();
        Graphics::SetColor(mColor);
        Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
        Graphics::SetColor();
    }
    
    bool aIsActive = true;
    bool aIsOver = mMouseOver;
    bool aIsDown = false;
    if ((mTouchDownInside == true) && (mClickData != NULL)) {
        aIsDown = true;
    }

    EnumList(FButtonLayer, aLayer, mButtonLayersUnder) {
        aLayer->Draw(this, aIsActive, aIsOver, aIsDown);
    }
    
    if (mButtonLayer) {
        mButtonLayer->Draw(this, aIsActive, aIsOver, aIsDown);
    }
    
    EnumList(FButtonLayer, aLayer, mButtonLayersOver) {
        aLayer->Draw(this, aIsActive, aIsOver, aIsDown);
    }
}

void FButton::TouchDown(float pX, float pY, void *pData) {
    if (mClickData == NULL) {
        mClickData = pData;
    }

    gNotify.Post(this, "button_down");
    
    if (mTriggerOnDown) {
        gNotify.Post(this, "button_click");
    }
}

void FButton::TouchMove(float pX, float pY, void *pData) {
    if (pData == mClickData) {

    }
}

void FButton::TouchUp(float pX, float pY, void *pData) {
    if (mClickData == pData) {
        if ((pX >= 0) && (pY >= 0) && (pX <= mWidth) && (pY <= mHeight)) {
            if (mTriggerOnUp) {
                gNotify.Post(this, "button_click");
            }
            gNotify.Post(this, "button_up");
        }
        mClickData = NULL;
    }
}

void FButton::TouchFlush() {
    mClickData = NULL;
}

FButtonLayer::FButtonLayer() {
    
    mOffsetUpX = 0.0f;
    mOffsetUpY = 0.0f;
    
    mOffsetDownX = 0.0f;
    mOffsetDownY = 0.0f;
    
    mOffsetOverX = 0.0f;
    mOffsetOverY = 0.0f;
    
    mRotation = 0.0f;
    
    mScale = 1.0f;
    
    mSpriteUp = 0;
    mSpriteOver = 0;
    mSpriteDown = 0;
    
    mActive = true;
    
    mColorUp.mRed = 1.0f;
    mColorUp.mGreen = 1.0f;
    mColorUp.mBlue = 1.0f;
    mColorUp.mAlpha = 1.0f;
    
    mColorOver.mRed = 0.925f;
    mColorOver.mGreen = 0.925f;
    mColorOver.mBlue = 0.925f;
    mColorOver.mAlpha = 1.0f;
    
    mColorDown.mRed = 0.85f;
    mColorDown.mGreen = 0.85f;
    mColorDown.mBlue = 0.85f;
    mColorDown.mAlpha = 1.0f;
    
    mWidth = 0.0f;
    mHeight = 0.0f;
}

FButtonLayer::~FButtonLayer() {
    
}

void FButtonLayer::SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown) {
    mSpriteUp = pSpriteUp;
    mSpriteOver = pSpriteOver;
    mSpriteDown = pSpriteDown;
    mWidth = 0.0f;
    mHeight = 0.0f;
    if (pSpriteDown != 0) {
        mColorOver.mRed = 1.0f;
        mColorOver.mGreen = 1.0f;
        mColorOver.mBlue = 1.0f;
        mColorOver.mAlpha = 1.0f;
        mColorDown.mRed = 1.0f;
        mColorDown.mGreen = 1.0f;
        mColorDown.mBlue = 1.0f;
        mColorDown.mAlpha = 1.0f;
    }
    else if(mSpriteOver != 0)
    {
        mColorOver.mRed = 1.0f;
        mColorOver.mGreen = 1.0f;
        mColorOver.mBlue = 1.0f;
        mColorOver.mAlpha = 1.0f;
    }
    
    if(mSpriteUp != 0)
    {
        if(mSpriteUp->mWidth > mWidth)mWidth = mSpriteUp->mWidth;
        if(mSpriteUp->mHeight > mHeight)mHeight = mSpriteUp->mHeight;
    }
    
    if(mSpriteOver != 0)
    {
        if(mSpriteOver->mWidth > mWidth)mWidth = mSpriteOver->mWidth;
        if(mSpriteOver->mHeight > mHeight)mHeight = mSpriteOver->mHeight;
    }
    
    if(mSpriteDown != 0)
    {
        if(mSpriteDown->mWidth > mWidth)mWidth = mSpriteDown->mWidth;
        if(mSpriteDown->mHeight > mHeight)mHeight = mSpriteDown->mHeight;
    }
    
}

void FButtonLayer::Draw(FButton *pButton, bool pActive, bool pIsOver, bool pIsDown)
{
    FSprite *aSprite = 0;
    
    if ((pActive == true) && (pButton != NULL)) {
        
        float aX = pButton->mWidth2;
        float aY = pButton->mHeight2;
        
        float aOffsetX = mOffsetUpX;
        float aOffsetY = mOffsetUpY;
        
        if (pIsDown) {
            Graphics::SetColor(mColorDown.mRed, mColorDown.mGreen, mColorDown.mBlue, mColorDown.mAlpha);
            aSprite = mSpriteDown;
            aOffsetX = mOffsetDownX;
            aOffsetY = mOffsetDownY;
            
        } else if(pIsOver) {
            Graphics::SetColor(mColorOver.mRed, mColorOver.mGreen, mColorOver.mBlue, mColorOver.mAlpha);
            aSprite = mSpriteOver;
            aOffsetX = mOffsetOverX;
            aOffsetY = mOffsetOverY;
        } else {
            Graphics::SetColor(mColorUp.mRed, mColorUp.mGreen, mColorUp.mBlue, mColorUp.mAlpha);
        }
        
        if (aSprite == NULL) {
            aSprite = mSpriteUp;
        }
        
        //Graphics::SetColor(1.0f, 1.0f, 1.0f, 0.85f);
        if (aSprite != NULL) {
            if (pButton->mDrawSetsSpriteAlphaPipelineState == true) {
                Graphics::PipelineStateSetSpriteAlphaBlending();
            }
            aSprite->Draw(aX + aOffsetX, aY + aOffsetY, mScale, mRotation);
        }
        Graphics::SetColor();
    }
}



