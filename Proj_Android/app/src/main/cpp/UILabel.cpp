//
//  UILabel.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UILabel.hpp"
#include "ToolMenuSectionRow.hpp"
#include "FApp.hpp"

UILabel::UILabel() {
    mConsumesTouches = false;
    mName = "UILabel";
    mText = "Label";
    mAlignment = 0;
    mBold = false;
    mShrink = true;
    mPadding = 3.0f;
    mScale = 1.0f;
    mMinWidth = 60.0f;
    mSectionBackground.SetColorTop(0.125f, 0.125f, 0.145f);
    mSectionBackground.SetColorBottom(0.095f, 0.135f, 0.115f);
    mSectionBackground.mCornerRadius = 4.0f;
    mSectionBackgroundOutline.SetColorTop(0.4125, 0.4225, 0.3925, 1.0f);
    mSectionBackgroundOutline.SetColorBottom(0.44f, 0.475f, 0.46f, 1.0f);
    mSectionBackgroundOutline.mCornerRadius = 5.0f;

    SetHeight(ToolMenuSectionRow::RowHeight());
}

UILabel::~UILabel() { }

void UILabel::Layout() {
    mSectionBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mSectionBackground.mRefresh = true;
    mSectionBackgroundOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mSectionBackgroundOutline.mRefresh = true;
}

void UILabel::Draw() {
    mSectionBackgroundOutline.Draw();
    mSectionBackground.Draw();
    FFont *aFont = &(gAppBase->mSysFont);
    if (mBold) aFont = &(gAppBase->mSysFontBold);
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::SetColor(mColor);
    float aScale = mScale;
    if (mShrink) {
        aScale = aFont->ScaleForWidth(mText, mWidth - mPadding * 2.0f);
        if (aScale > mScale) { aScale = mScale; }
    }
    if (mAlignment < 0) {
        aFont->LeftCenter(mText, mPadding, mHeight2, aScale);
    } else if (mAlignment == 0) {
        aFont->Center(mText, mWidth2, mHeight2, aScale);
    } else {
        aFont->RightCenter(mText, mWidth - mPadding, mHeight2, aScale);
    }
    Graphics::SetColor();
}

void UILabel::SetText(const char *pText) {
    mText = pText;
}

float UILabel::GetIdealSize() {
    FFont *aFont = &(gAppBase->mSysFont);
    if (mBold) aFont = &(gAppBase->mSysFontBold);
    float aTextWidth = aFont->Width(mText.c(), mScale);
    if (aTextWidth < 20) { aTextWidth = 20.0f; }
    return aTextWidth + mPadding * 2.0f;
}


void UILabel::SetTransparentBackground() {
    mSectionBackground.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackgroundOutline.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackground.mRefresh = true;
    mSectionBackgroundOutline.mRefresh = true;
}

