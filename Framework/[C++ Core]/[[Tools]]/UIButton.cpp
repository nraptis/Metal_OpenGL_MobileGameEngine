//
//  UIButton.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIButton.hpp"
#include "ToolMenuSectionRow.hpp"
#include "FApp.hpp"

UIButton::UIButton() {
    mName = "UIButton";
    
    mConsumesTouches = true;
    
    mBackgroundVerticalPadding = 0.0f;
    
    mDrawCloseX = false;
    mDrawMinimize = false;
    mDrawMaximize = false;

    mFontScale = 0.75f;
    mFontBold = true;
    mFontPadding = 6.0f;
    
    mButtonBackground.SetColorTop(0.125f, 0.125f, 0.125f);
    mButtonBackground.SetColorBottom(0.165f, 0.165f, 0.165f);
    mButtonBackground.mCornerRadius = 4.0f;

    mButtonOutline.SetColorTop(0.265f, 0.265f, 0.265f);
    mButtonOutline.SetColorBottom(0.225f, 0.225f, 0.225f);
    mButtonOutline.mCornerRadius = 4.0f;
    
    mButtonBackgroundDown.SetColorTop(0.165f, 0.165f, 0.165f);
    mButtonBackgroundDown.SetColorBottom(0.1825f, 0.1825f, 0.1825f);
    mButtonBackgroundDown.mCornerRadius = 4.0f;

    mButtonOutlineDown.SetColorTop(0.855f, 0.825f, 0.125f);
    mButtonOutlineDown.SetColorBottom(0.865f, 0.865f, 0.125f);
    mButtonOutlineDown.mCornerRadius = 4.0f;

    SetHeight(ToolMenuSectionRow::RowHeight());
}

UIButton::~UIButton() {
    
}

void UIButton::Layout() {
    mButtonBackground.SetRect(2.0f, mBackgroundVerticalPadding + 2.0f, mWidth - 4.0f, mHeight - (4.0f + mBackgroundVerticalPadding * 2.0f));
    mButtonBackgroundDown.SetRect(2.0f, mBackgroundVerticalPadding + 2.0f, mWidth - 4.0f, mHeight - (4.0f + mBackgroundVerticalPadding * 2.0f));
    mButtonOutline.SetRect(0.0f, mBackgroundVerticalPadding, mWidth, mHeight - mBackgroundVerticalPadding * 2.0f);
    mButtonOutlineDown.SetRect(0.0f, mBackgroundVerticalPadding, mWidth, mHeight - mBackgroundVerticalPadding * 2.0f);

    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;

}

void UIButton::Update() {

}

void UIButton::Draw() {
    
    Graphics::SetColor();

    if (mTouchDown) {
        mButtonOutlineDown.Draw();
        mButtonBackgroundDown.Draw();
    } else {
        mButtonOutline.Draw();
        mButtonBackground.Draw();
    }

    
    float aLineThickness = (int)(mHeight * 0.06f) + 1;
    if (mTouchDown) { Graphics::SetColor(0.88f, 0.88f, 0.88f); }
    else { Graphics::SetColor(); }

    
    if (mDrawCloseX) {
        Graphics::PipelineStateSetShape2DAlphaBlending();
        float aGraphicInset = mWidth * 0.26f;
        Graphics::DrawLine(aGraphicInset, aGraphicInset, mWidth - aGraphicInset, mHeight - aGraphicInset, aLineThickness);
        Graphics::DrawLine(aGraphicInset, mHeight - aGraphicInset, mWidth - aGraphicInset, aGraphicInset, aLineThickness);
    }
    if (mDrawMinimize) {
        Graphics::PipelineStateSetShape2DAlphaBlending();
        float aGraphicInset = mWidth * 0.26f;
        Graphics::DrawLine(aGraphicInset, mHeight2, mWidth - aGraphicInset, mHeight2, aLineThickness);
    }

    if (mDrawMaximize) {
        if (mHeight < mWidth) {
            Graphics::PipelineStateSetShape2DAlphaBlending();
            float aGraphicInset = mHeight * 0.26f;
            float aRectHeight = mHeight - (aGraphicInset * 2.0f);
            float aShift = aRectHeight / 2.0f;
            Graphics::OutlineRect(mWidth2 - aShift, mHeight2 - aShift, aRectHeight, aRectHeight, aLineThickness);
        } else {
            Graphics::PipelineStateSetShape2DAlphaBlending();
            float aGraphicInset = mWidth * 0.26f;
            float aRectWidth = mWidth - (aGraphicInset * 2.0f);
            float aShift = aRectWidth / 2.0f;
            Graphics::OutlineRect(mWidth2 - aShift, mHeight2 - aShift, aRectWidth, aRectWidth, aLineThickness);
        }
    }

    if (mText.mLength > 0) {
        Graphics::PipelineStateSetSpritePremultipliedBlending();
        if (mTouchDown) { Graphics::SetColor(0.88f, 0.88f, 0.88f); }
        else { Graphics::SetColor(); }

        FFont *aFont = &(gAppBase->mSysFont);
        if (mFontBold) aFont = &(gAppBase->mSysFontBold);
        
        float aScale = gAppBase->mSysFont.ScaleForWidth(mText, mWidth, mFontPadding);
        if (aScale > mFontScale) { aScale = mFontScale; }
        gAppBase->mSysFont.Center(mText, mWidth2, mHeight2, aScale);
    }
    Graphics::SetColor();
}

float UIButton::GetIdealSize() {
    if (mText.mLength > 0) {
        FFont *aFont = &(gAppBase->mSysFont);
        if (mFontBold) aFont = &(gAppBase->mSysFontBold);
        float aWidth = aFont->Width(mText.c(), mFontScale);
        return aWidth;
    }
    return mWidth;
}

void UIButton::SetTransparentBackground() {
    mButtonBackground.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mButtonOutline.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mButtonBackgroundDown.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mButtonOutlineDown.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);

    mButtonBackground.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}


