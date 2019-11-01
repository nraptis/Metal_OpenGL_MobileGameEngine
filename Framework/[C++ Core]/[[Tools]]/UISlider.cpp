//
//  UISlider.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UISlider.hpp"
#include "ToolMenu.hpp"

UISlider::UISlider() {
    mPreviousDrawMin = -1;
    mPreviousDrawMax = -1;

    mValue = 0.0f;
    mTargetValue = 0;

    mBarHeight = 10.0f;

    mLabelTitle.mScale = 0.6f;
    mLabelTitle.mAlignment = 1;

    mLabelValue.mScale = 0.6f;
    mLabelValue.mAlignment = -1;

    mDefaultValue = 0.0f;
    mDefaultValueAssigned = false;
    
    //mSliderContainer.mColor = FColor(0.0f, 1.0f, 0.0f, 0.5f);
    //mButtonsContainer.mColor = FColor(0.0f, 0.0f, 1.0f, 0.5f);
    
    AddChild(mSliderContainer);
    AddChild(mButtonsContainer);
    
    
    mButtonResetDefault = new UIButton();
    mButtonResetDefault->SetText("R-D");
    mButtonsContainer.AddButton(mButtonResetDefault);
    gNotify.Register(this, mButtonResetDefault, "button_click");
    
    mButtonResetZero = new UIButton();
    mButtonResetZero->SetText("R-0");
    mButtonsContainer.AddButton(mButtonResetZero);
    gNotify.Register(this, mButtonResetZero, "button_click");
    
    mButtonResetOne = new UIButton();
    mButtonResetOne->SetText("R-1");
    mButtonsContainer.AddButton(mButtonResetOne);
    gNotify.Register(this, mButtonResetOne, "button_click");

    
    
    
    
    mSliderContainer.SetTransparentBackground();
    
    
    mLabelTitleWidth = 80.0f;
    mLabelValueWidth = 60.0f;

    mLabelTitle.SetTransparentBackground();
    mLabelValue.SetTransparentBackground();

    
    mSliderContainer.AddChild(mLabelTitle);
    
    mSliderContainer.AddChild(mLabelValue);
    

    mLabelTitle.SetText("Value:");
    
    mBaseSlider.SetFrame(0.0f, 0.0f, mWidth, mHeight);
    mBaseSlider.SetThumb(0.0f, 0.0f, 40.0f, mHeight);
    mBaseSlider.mDrawManual = true;
    mSliderContainer.AddChild(mBaseSlider);

    gNotify.Register(this, &mBaseSlider, "slider_update");

    FRect aRectBar = FRect(6.0f, mHeight / 2.0f - mBarHeight / 2.0f, mWidth - 12, mBarHeight);
    FRect aRectThumb = FRect(0.0f, 0.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight);

    mRectBarLeft.mCornerRadius = 5.0f;
    mRectBarLeft.mRoundRight = false;
    mRectBarLeft.SetColorTop(0.231f, 0.373f, 0.7847059f);
    mRectBarLeft.SetColorBottom(0.2157f, 0.353f, 0.7647059f);
    mRectBarLeft.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);
    
    mRectBarRight.mCornerRadius = 5.0f;
    mRectBarRight.mRoundLeft = false;
    mRectBarRight.SetColorTop(0.16f, 0.16f, 0.16f);
    mRectBarRight.SetColorBottom(0.18f, 0.18f, 0.18f);
    mRectBarRight.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);
    
    mRectBarOutline.mCornerRadius = 5.0f;
    mRectBarOutline.mCornerPointCount = 6;
    mRectBarOutline.SetColorTop(0.46f, 0.46f, 0.46f);
    mRectBarOutline.SetColorBottom(0.50f, 0.50f, 0.50f);
    mRectBarOutline.SetRect(aRectBar.mX, aRectBar.mY, aRectBar.mWidth, aRectBar.mHeight);
    
    mRectThumb.mCornerRadius = 8.0f;
    mRectThumb.mCornerPointCount = 10;
    mRectThumb.SetColorTop(0.76f, 0.76f, 0.79f);
    mRectThumb.SetColorBottom(0.73f, 0.73f, 0.74f);
    mRectThumb.SetRect(0.0f, 0.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight);
    
    mRectThumbOutline.mCornerRadius = 8.0f;
    mRectThumbOutline.mCornerPointCount = 10;
    mRectThumbOutline.SetColorTop(0.96f, 0.96f, 0.96f, 1.0f);
    mRectThumbOutline.SetColorBottom(0.94f, 0.94f, 0.94f, 1.0f);
    mRectThumbOutline.SetRect(-1.0f, -1.0f, mBaseSlider.mThumbWidth + 2.0f, mBaseSlider.mThumbHeight + 2.0f);
}

UISlider::~UISlider()
{

}

void UISlider::Layout() {
    ToolMenuSectionRow::Layout();
    
    bool aShowButtons = true;
    float aSliderContainerWidth = mWidth * 0.6f;
    float aButtonContainerWidth = (mWidth - (2.0f + aSliderContainerWidth));
    
    if (mWidth > 450.0f) {
        aShowButtons = true;
    } else {
        aShowButtons = false;
    }
    
    if (aShowButtons == false) {
        mButtonsContainer.mHidden = true;
        aSliderContainerWidth = mWidth;
        aButtonContainerWidth = 0.0f;
    } else {
        mButtonsContainer.mHidden = false;
    }
    
    mSliderContainer.SetFrame(0.0f, 0.0f, aSliderContainerWidth, mHeight);
    mButtonsContainer.SetFrame(aSliderContainerWidth + 2.0, 0.0f, aButtonContainerWidth, mHeight);
    
    mLabelTitle.SetFrame(2.0f, 2.0f, mLabelTitleWidth, mHeight - 4.0f);
    mLabelValue.SetFrame(aSliderContainerWidth - (mLabelValueWidth + 2.0f), 2.0f, mLabelValueWidth, mHeight - 4.0f);

    float aSliderLeft = mLabelTitle.GetRight() + 2.0f;
    float aSliderRight = mLabelValue.GetLeft() - 2.0f;
    float aSliderWidth = (aSliderRight - aSliderLeft);

    mBaseSlider.SetFrame(aSliderLeft, 0.0f, aSliderWidth, mHeight);
    mBaseSlider.mThumbHeight = mHeight;

    FRect aRectBar = FRect(aSliderLeft + 6.0f, mHeight / 2.0f - mBarHeight / 2.0f, aSliderWidth - 12, mBarHeight);
    FRect aRectThumb = FRect(aSliderLeft + 2.0f, 10.0f, mBaseSlider.mThumbWidth - 4.0f, mBaseSlider.mThumbHeight - 20.0f);

    mRectBarOutline.SetRect(aRectBar.mX - 1.0f, aRectBar.mY - 1.0f, aRectBar.mWidth + 2.0f, aRectBar.mHeight + 2.0f);
    mRectThumbOutline.SetRect(aSliderLeft - 1.0f + 1.0f, -1.0f + 5.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight + 2.0f - 10.0f);
    mRectThumb.SetRect(aSliderLeft + 1.0f, 0.0f + 5.0f, mBaseSlider.mThumbWidth - 2.0f, mBaseSlider.mThumbHeight - 10.0f);
    
    mRectThumb.mRefresh = true;
    mRectThumbOutline.mRefresh = true;
    mRectBarOutline.mRefresh = true;
    
    mBaseSlider.SetValue(mValue);

    SliderDidUpdate();
}

void UISlider::Update() {
    if (mTargetValue) {
        
        if (mDefaultValueAssigned == false) {
            mDefaultValueAssigned = true;
            mDefaultValue = *mTargetValue;
        }
        
        float aDiff = *mTargetValue - mValue;
        if (aDiff < 0.0) { aDiff = -aDiff; }
        if (aDiff > 0.001f) {
            mBaseSlider.ForceValue(*mTargetValue);
            mValue = mBaseSlider.GetValue();
            SliderDidUpdate();
        }
    }
}

void UISlider::Draw() {
    
    mRectBarOutline.Draw();
    //mRectBar.Draw();
    mRectBarLeft.Draw();
    mRectBarRight.Draw();
    
    mRectThumbOutline.Draw(mBaseSlider.mThumbX, 0.0f);
    mRectThumb.Draw(mBaseSlider.mThumbX, 0.0f);

    bool aUpdateText = false;
    if (mBaseSlider.mMin != mPreviousDrawMin) {
        mPreviousDrawMin = mBaseSlider.mMin;
        aUpdateText = true;
    }

    if (mBaseSlider.mMax != mPreviousDrawMax) {
        mPreviousDrawMax = mBaseSlider.mMax;
        aUpdateText = true;
    }


    if(aUpdateText || true)
    {
        int aDecimals = 1;

        float aRange = mBaseSlider.mMax - mBaseSlider.mMin;

        if(aRange <= 2.0f)
        {
            aDecimals = 2;

            if(aRange < 0.5f)
            {
                aDecimals = 4;
            }

        }

        mLabelValue.mText = FString(mBaseSlider.mValue, 3.0f);
        Graphics::SetColor();
    }
}

void UISlider::SetTarget(float *pTargetValue) {
    mTargetValue = pTargetValue;
    
    mDefaultValueAssigned = false;
    
    if (mTargetValue) {
        mDefaultValue = *mTargetValue;
        mBaseSlider.ForceValue(*mTargetValue);
        mValue = mBaseSlider.GetValue();
    } else {
        mDefaultValue = 0.0f;
        if ((mValue < mBaseSlider.mMin) || (mValue > mBaseSlider.mMax)) {
            mValue = mBaseSlider.mMin;
            mBaseSlider.ForceValue(mValue);
        }
    }
}

float UISlider::GetValue() {
    return mBaseSlider.GetValue();
}


void UISlider::SliderDidUpdate() {
    float aSliderLeft = mLabelTitle.GetRight() + 2.0f;
    float aSliderRight = mLabelValue.GetLeft() - 2.0f;
    float aSliderWidth = (aSliderRight - aSliderLeft);
    
    FRect aRectBar = FRect(aSliderLeft + 6.0f, mHeight / 2.0f - mBarHeight / 2.0f, aSliderWidth - 12, mBarHeight);
    FRect aRectThumb = FRect(aSliderLeft, 10.0f, mBaseSlider.mThumbWidth, mBaseSlider.mThumbHeight - 20.0f);

    float aSliderSplit = aSliderLeft + mBaseSlider.mThumbX + mBaseSlider.mThumbWidth / 2.0f;

    FRect aRectBarLeft = FRect(aRectBar.mX, aRectBar.mY, aSliderSplit - aRectBar.mX, aRectBar.mHeight);
    FRect aRectBarRight = FRect(aRectBarLeft.Right(), aRectBar.mY, aRectBar.mWidth - aRectBarLeft.mWidth, aRectBar.mHeight);

    mRectBarLeft.SetRect(aRectBarLeft.mX, aRectBarLeft.mY, aRectBarLeft.mWidth, aRectBarLeft.mHeight);
    mRectBarRight.SetRect(aRectBarRight.mX, aRectBarRight.mY, aRectBarRight.mWidth, aRectBarRight.mHeight);

    mRectBarLeft.mRefresh = true;
    mRectBarRight.mRefresh = true;
}

void UISlider::Notify(void *pSender, const char *pNotification) {
    if (FString("slider_update") == pNotification) {
        if (pSender == &mBaseSlider) {
            mValue = mBaseSlider.mValue;
            if (mTargetValue) {
                *mTargetValue = mValue;
            }
            SliderDidUpdate();
            gNotify.Post(this, "slider_update");
            if (mMenu) {
                mMenu->Notify(this, "slider_update");
            }
        }
    }
    if (FString("button_click") == pNotification) {
        if (pSender == mButtonResetZero) {
            if (mTargetValue) {
                *mTargetValue = 0.0f;
            } else {
                mValue = 0.0f;
            }
            SliderDidUpdate();
        }
        if (pSender == mButtonResetOne) {
            if (mTargetValue) {
                *mTargetValue = 1.0f;
            } else {
                mValue = 1.0f;
            }
            SliderDidUpdate();
        }
        if (pSender == mButtonResetDefault) {
            if (mTargetValue) {
                *mTargetValue = mDefaultValue;
            } else {
                mValue = mDefaultValue;
            }
            SliderDidUpdate();
        }
    }
    
}

void UISlider::SetText(const char *pText) {
    mLabelTitle.SetText(pText);
    SliderDidUpdate();
}

void UISlider::SetRange(float pMin, float pMax) {
    mBaseSlider.SetMin(pMin);
    mBaseSlider.SetMax(pMax);
    SliderDidUpdate();
}

