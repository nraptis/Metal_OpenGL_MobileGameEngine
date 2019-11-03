//
//  ProgressBar.cpp
//
//  Created by Nick Raptis on 10/21/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "ProgressBar.hpp"
#include "core_includes.h"
#include "GFXApp.hpp"

ProgressBar::ProgressBar() {
    mConsumesTouches = false;
    
    mTextureTop = 0.0f;
    mTextureBottom = 255.0f;
    
    mBubbleOffsetU = 0.0f;
    mStripeOffsetU = 0.0f;
}

ProgressBar::~ProgressBar() {
    
}

void ProgressBar::Layout() {
    float aTemplateWidth = gWadGameInterface.mProgressBarFull.mWidth;
    float aTemplateHeight = gWadGameInterface.mProgressBarFull.mHeight;
    float aLeftX = aTemplateWidth * 0.155f;
    float aRightX = mWidth - aTemplateWidth * 0.155f;
    float aCenterY = mHeight * 0.5f;
    
    int aEdgePointCount = 4;
    
    float aOutlineHeight = aTemplateHeight * 0.5f;
    float aOutlineHeight2 = aOutlineHeight * 0.5f;
    
    float aOutlineEdgeCompressionFactor = 0.30f;
    
    float aTopY = aCenterY - aOutlineHeight2;
    float aBottomY = aCenterY + aOutlineHeight2;
    
    float aX = 0.0f;
    float aY = 0.0f;
    
    mShapeList.RemoveAll();
    
    mShapeList.Add(aLeftX, aTopY);
    mShapeList.Add(aRightX, aTopY);
    for (int i=1;i<aEdgePointCount;i++) {
        float aPercent = ((float)i) / ((float)(aEdgePointCount));
        float aRotation = 180.0f * aPercent;
        float aDirX = Sin(aRotation);
        float aDirY = -Cos(aRotation);
        aX = aRightX + aDirX * aOutlineHeight2 * aOutlineEdgeCompressionFactor;
        aY = aCenterY + aDirY * aOutlineHeight2;
        mShapeList.Add(aX, aY);
    }
    
    mShapeList.Add(aRightX, aBottomY);
    mShapeList.Add(aLeftX, aBottomY);
    for (int i=1;i<aEdgePointCount;i++) {
        float aPercent = ((float)i) / ((float)(aEdgePointCount));
        float aRotation = 180.0f + 180.0f * aPercent;
        float aDirX = Sin(aRotation);
        float aDirY = -Cos(aRotation);
        aX = aLeftX + aDirX * aOutlineHeight2 * aOutlineEdgeCompressionFactor;
        aY = aCenterY + aDirY * aOutlineHeight2;
        mShapeList.Add(aX, aY);
    }
    
    mTextureTop = aTopY;
    mTextureBottom = aBottomY;
}

void ProgressBar::Update() {
    mStripeOffsetU -= 0.000545f;
    if (mStripeOffsetU < 0.0f) { mStripeOffsetU += 1.0f; }
    
    mBubbleOffsetU += 0.00032f;
    if (mBubbleOffsetU > 1.0f) { mBubbleOffsetU -= 1.0f; }
    
    
    mPercent += 0.001f;
    if (mPercent >= 1.0f) {
        mPercent -= 1.0f;
    }
}

void ProgressBar::Draw() {
    
    Graphics::SetColor();
    Graphics::PipelineStateSetSpriteAlphaBlending();
    
    float aTemplateWidth = gWadGameInterface.mProgressBarFull.mWidth;
    float aTemplateHeight = gWadGameInterface.mProgressBarFull.mHeight;
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    gWadGameInterface.mProgressBarEmpty.DrawTripletH(0.0f, mHeight2 - aTemplateHeight / 2.0f, aTemplateWidth * 0.25f, aTemplateWidth * 0.25f, mWidth);
    
    gWadGameInterface.mProgressBarFull.DrawTripletHProgress(0.0f, mHeight2 - aTemplateHeight / 2.0f, aTemplateWidth * 0.25f, aTemplateWidth * 0.25f, mWidth,
                                                            aTemplateWidth * 0.125f, aTemplateWidth * 0.125f, mPercent);
    
    Graphics::CullFacesSetBack();
    Graphics::TextureSetWrap();
    
    Graphics::PipelineStateSetSpriteAdditiveBlending();
    Graphics::SetColor(0.065f);
    mTextureOffsetU = mBubbleOffsetU;
    DrawTextureLoop(&(gWadGameInterface.mProgressLoopBubbles));
    
    Graphics::SetColor(0.095f);
    mTextureOffsetU = mStripeOffsetU;
    DrawTextureLoop(&(gWadGameInterface.mProgressLoopStripes));
    
    Graphics::TextureSetClamp();
    Graphics::CullFacesSetDisabled();
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor();
    gWadGameInterface.mProgressBarStroke.DrawTripletH(0.0f, mHeight2 - aTemplateHeight / 2.0f, aTemplateWidth * 0.25f, aTemplateWidth * 0.25f, mWidth);
    
    Graphics::PipelineStateSetSpriteAlphaBlending();
    Graphics::SetColor(0.25f);
    gWadGameInterface.mProgressBarShine.DrawTripletH(0.0f, mHeight2 - aTemplateHeight / 2.0f, aTemplateWidth * 0.25f, aTemplateWidth * 0.25f, mWidth);
}

void ProgressBar::DrawTextureLoop(FSprite *pSprite, float pX1, float pY1, float pX2, float pY2, float pX3, float pY3) {
    if (pSprite == NULL) { return; }
    
    float aTextureWidth = pSprite->mWidth;
    float aTextureHeight = pSprite->mHeight;
    
    if ((aTextureWidth <= 2.0f) || (aTextureHeight <= 2.0f)) { return; }
    
    float aStartU = pSprite->GetStartU();
    float aStartV = pSprite->GetStartV();
    
    float aEndU = pSprite->GetEndU();
    float aEndV = pSprite->GetEndV();
    float aDeltaU = (aEndU - aStartU);
    float aDeltaV = (aEndV - aStartV);
    
    float aOffset = mTextureOffsetU * aDeltaU;
    
    float aU1 = pX1 / aTextureWidth;
    float aU2 = pX2 / aTextureWidth;
    float aU3 = pX3 / aTextureWidth;
    
    float aV1 = (pY1 - mTextureTop) / (aTextureHeight);
    float aV2 = (pY2 - mTextureTop) / (aTextureHeight);
    float aV3 = (pY3 - mTextureTop) / (aTextureHeight);
    
    aU1 = aStartU + (aDeltaU * aU1) + aOffset;
    aU2 = aStartU + (aDeltaU * aU2) + aOffset;
    aU3 = aStartU + (aDeltaU * aU3) + aOffset;
    
    aV1 = aStartV + (aDeltaV * aV1);
    aV2 = aStartV + (aDeltaV * aV2);
    aV3 = aStartV + (aDeltaV * aV3);
    
    mTextureTriangle.SetXYTriangle(pX1, pY1, pX2, pY2, pX3, pY3);
    mTextureTriangle.SetUVTriangle(aU1, aV1, aU2, aV2, aU3, aV3);
    
    Graphics::DrawSpriteTriangle(mTextureTriangle.mPositions, mTextureTriangle.mTextureCoords, pSprite->mTexture);
}

void ProgressBar::DrawTextureLoop(FSprite *pSprite, int pIndex1, int pIndex2, int pIndex3) {
    if ((pIndex1 >= 0) && (pIndex2 >= 0) && (pIndex3 >= 0) && (pIndex1 < mShapeList.mCount) && (pIndex2 < mShapeList.mCount) && (pIndex3 < mShapeList.mCount)) {
        
        float aX1 = mShapeList.mX[pIndex1];
        float aY1 = mShapeList.mY[pIndex1];
        
        float aX2 = mShapeList.mX[pIndex2];
        float aY2 = mShapeList.mY[pIndex2];
        
        float aX3 = mShapeList.mX[pIndex3];
        float aY3 = mShapeList.mY[pIndex3];
        
        DrawTextureLoop(pSprite, aX1, aY1, aX2, aY2, aX3, aY3);
    }
}

void ProgressBar::DrawTextureLoop(FSprite *pSprite) {
    
    //Main Box...
    DrawTextureLoop(pSprite, 0, 1, 6);
    DrawTextureLoop(pSprite, 1, 5, 6);
    
    //Left Side
    DrawTextureLoop(pSprite, 8, 6, 7);
    DrawTextureLoop(pSprite, 0, 8, 9);
    DrawTextureLoop(pSprite, 0, 6, 8);
    
    //Right Side
    DrawTextureLoop(pSprite, 3, 1, 2);
    DrawTextureLoop(pSprite, 5, 3, 4);
    DrawTextureLoop(pSprite, 5, 1, 3);

}

