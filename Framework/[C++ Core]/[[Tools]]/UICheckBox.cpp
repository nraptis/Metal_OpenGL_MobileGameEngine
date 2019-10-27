//
//  UICheckBox.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/5/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UICheckBox.hpp"
#include "ToolMenuSectionRow.hpp"
#include "FApp.hpp"


UICheckBox::UICheckBox() {
    mName = "UICheckBox";

    mTarget = 0;
    mConsumesTouches = true;
    mFontScale = 0.6f;
    mTextCenterX = 20.0f;
    mIsChecked = false;

    mButtonBackground.mCornerRadius = 5.0f;
    mButtonOutline.mCornerRadius = 5.0f;
    mButtonBackgroundDown.mCornerRadius = 5.0f;
    mButtonOutlineDown.mCornerRadius = 5.0f;
    mCheckBackground.mCornerRadius = 5.0f;
    mCheckOutline.mCornerRadius = 5.0f;
    mCheckBackground.mCornerPointCount = 6;
    mCheckOutline.mCornerPointCount = 6;

    SetHeight(ToolMenuSectionRow::RowHeight());

    CheckedStateDidUpdate();
}

UICheckBox::~UICheckBox() {

}

void UICheckBox::Layout() {
    float aTextWidth = gAppBase->mSysFont.Width(mText.c(), mFontScale);
    if (aTextWidth < 20.0f) { aTextWidth = 20.0f; }

    float aTextRight = aTextWidth + 4.0f + 4.0f;


    float aCheckSize = 24.0f;
    //SetWidth(aTextRight + aCheckSize + 8.0f);

    mButtonBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mButtonBackgroundDown.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mButtonOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mButtonOutlineDown.SetRect(0.0f, 0.0f, mWidth, mHeight);

    float aCheckTop = mHeight2 - aCheckSize / 2.0f;
    float aExpectedWidth = aTextRight + aCheckSize + 8.0f;
    float aShift = 0.0f;

    if (mWidth > aExpectedWidth) {
        aShift += (mWidth - aExpectedWidth)  / 2.0f;
    }

    mTextCenterX = aTextWidth / 2.0f + 2.0f + aShift;
    
    mCheckBackground.SetRect(aTextRight + 2.0f + aShift, aCheckTop + 2.0f, aCheckSize - 4.0f, aCheckSize - 4.0f);
    mCheckOutline.SetRect(aTextRight + aShift, aCheckTop, aCheckSize, aCheckSize);

    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
    mCheckBackground.mRefresh = true;
    mCheckOutline.mRefresh = true;
}

void UICheckBox::Update() {
    if (mTarget) {
        if (*mTarget != mIsChecked) {
            SetChecked(*mTarget);
        }
    }
}

void UICheckBox::Draw() {
    
    Graphics::SetColor();
    
    if (mTouchDown) {
        mButtonOutlineDown.Draw();
        mButtonBackgroundDown.Draw();
    } else {
        mButtonOutline.Draw();
        mButtonBackground.Draw();
    }
    mCheckOutline.Draw();
    mCheckBackground.Draw();
    if (mText.mLength > 0) {
        Graphics::PipelineStateSetSpritePremultipliedBlending();
        if (mTouchDown) { Graphics::SetColor(0.88f, 0.88f, 0.88f); }
        else { Graphics::SetColor(1.0f, 1.0f, 1.0f); }
        gAppBase->mSysFont.Center(mText, mTextCenterX, mHeight2, mFontScale);
    }
    Graphics::SetColor();
}

void UICheckBox::TouchUp(float pX, float pY, void *pData) {
    if (mClickData == pData) {
        if (pX >= 0 && pY >= 0 && pX <= mWidth && pY <= mHeight) {
            mIsChecked = !mIsChecked;
            if (mTarget) {
                *mTarget = mIsChecked;
            }
            CheckedStateDidUpdate();

            gNotify.Post(this, "checkbox");
        }
        mClickData = 0;
    }
}

float UICheckBox::GetIdealSize() {
    float aTextWidth = gAppBase->mSysFont.Width(mText.c(), mFontScale);
    if (aTextWidth < 20.0f) { aTextWidth = 20.0f; }
    float aTextRight = aTextWidth + 4.0f + 4.0f;
    float aCheckSize = 24.0f;
    return aTextRight + aCheckSize + 8.0f;
}

void UICheckBox::SetTarget(bool *pTarget) {
    mTarget = pTarget;
    if (mTarget) {
        mIsChecked = (*pTarget);
        CheckedStateDidUpdate();
    }
}

void UICheckBox::SetChecked(bool pChecked) {
    mIsChecked = pChecked;
    CheckedStateDidUpdate();
}

void UICheckBox::CheckedStateDidUpdate() {
    mButtonBackground.SetColorTop(0.125f, 0.125f, 0.125f);
    mButtonBackground.SetColorBottom(0.165f, 0.165f, 0.165f);
    mButtonBackgroundDown.SetColorTop(0.165f, 0.165f, 0.165f);
    mButtonBackgroundDown.SetColorBottom(0.1825f, 0.1825f, 0.1825f);
    if (mIsChecked) {
        mCheckBackground.SetColorTop(0.165f, 0.95f, 0.165f);
        mCheckBackground.SetColorBottom(0.168f, 0.98f, 0.168f);
        mButtonOutline.SetColorTop(0.82f, 0.82f, 0.82f);
        mButtonOutline.SetColorBottom(0.85f, 0.85f, 0.85f);
        mButtonOutlineDown.SetColorTop(0.925f, 0.925f, 0.142f);
        mButtonOutlineDown.SetColorBottom(0.935f, 0.935f, 0.145f);
    } else {
        mCheckBackground.SetColorTop(0.125f, 0.125f, 0.125f);
        mCheckBackground.SetColorBottom(0.10f, 0.10f, 0.10f);
        mButtonOutline.SetColorTop(0.265f, 0.265f, 0.265f);
        mButtonOutline.SetColorBottom(0.225f, 0.225f, 0.225f);
        mButtonOutlineDown.SetColorTop(0.855f, 0.825f, 0.125f);
        mButtonOutlineDown.SetColorBottom(0.865f, 0.865f, 0.125f);
    }
    mCheckOutline.SetColorTop(0.56f, 0.56f, 0.56f);
    mCheckOutline.SetColorBottom(0.52f, 0.52f, 0.52f);
    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
    mCheckBackground.mRefresh = true;
    mCheckOutline.mRefresh = true;
}

