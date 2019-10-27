//
//  UIStepper.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/5/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIStepper.hpp"
#include "ToolMenu.hpp"

UIStepper::UIStepper() {
    mValue = 0;
    mTarget = NULL;
    
    mMax = 9999;
    mMin = -9999;
    
    mLabelTitle.mScale = 0.75f;
    mLabelTitle.mAlignment = 1;
    
    
    mLabelTitleWidth = 88.0f;
    mTextBoxWidth = 60.0f;
    
    
    mTextBox.mScale = 0.75f;
    
    
    AddChild(mButtonAdd1);
    AddChild(mButtonAdd10);
    AddChild(mButtonAdd50);
    AddChild(mButtonSub1);
    AddChild(mButtonSub10);
    AddChild(mButtonSub50);
    AddChild(mLabelTitle);
    AddChild(mTextBox);
    AddChild(mButtonZero);
    
    mLabelTitle.SetTransparentBackground();
    mLabelTitle.SetText("Int:");
    
    gNotify.Register(this, &mButtonAdd1, "button_click");
    gNotify.Register(this, &mButtonAdd10, "button_click");
    gNotify.Register(this, &mButtonAdd50, "button_click");
    gNotify.Register(this, &mButtonSub1, "button_click");
    gNotify.Register(this, &mButtonSub10, "button_click");
    gNotify.Register(this, &mButtonSub50, "button_click");
    gNotify.Register(this, &mButtonZero, "button_click");
    gNotify.Register(this, &mTextBox, "text_box_change");
    gNotify.Register(this, &mTextBox, "text_box_submit");
    
    
    mButtonAdd1.SetText("A");
    mButtonAdd10.SetText("A");
    mButtonAdd50.SetText("A");
    
    mButtonSub1.SetText("D");
    mButtonSub10.SetText("D");
    mButtonSub50.SetText("D");
    
    mButtonZero.SetText("R0");
    
    
    SetValue(0);
}

UIStepper::~UIStepper()
{

}

void UIStepper::Layout() {

    ToolMenuSectionRow::Layout();
    
    
    mLabelTitle.SetFrame(2.0f, 2.0f, mLabelTitleWidth, mHeight - 4.0f);
    
    float aLeft = 2.0f + mLabelTitleWidth + 2.0f;
    float aRight = mWidth - 2.0f;
    
    float aAvailableSpace = aRight - aLeft;
    
    bool aShowZero = false;
    bool aShow1 = false;
    bool aShow10 = false;
    bool aShow50 = false;
    
    if (aAvailableSpace >= mTextBoxWidth) {
        aAvailableSpace -= mTextBoxWidth;
        if (aAvailableSpace >= 44.0f) {
            aShowZero = true;
            mButtonZero.SetFrame(aLeft, 2.0f, 44.0f, mHeight - 4.0f);
            
            aLeft += 44.0f;
            aLeft += 2.0f;
            aAvailableSpace -= (44.0f + 2.0f);
                   
        }
    }
    
    if (aAvailableSpace >= 150.0f) {
        aShow1 = true;
        aShow10 = true;
        aShow50 = true;
    } else if (aAvailableSpace >= 100.0f) {
        aShow1 = true;
        aShow10 = true;
    } else if (aAvailableSpace >= 50.0f) {
        aShow1 = true;
    }
    
    
    if (aShow1 == false && aShow10 == false && aShow50 == false) {
        
        if ((mWidth - aLeft) >= mTextBoxWidth) {
            mTextBox.SetFrame(aLeft, 2.0f, aRight - aLeft, mHeight - 4.0f);
        } else {
            mTextBox.SetFrame(aLeft, 2.0f, mTextBoxWidth, mHeight - 4.0f);
        }
    } else {
        
        float aCenterX = aLeft + (aAvailableSpace + mTextBoxWidth) / 2.0f;
        float aTextBoxLeft = round(aCenterX - mTextBoxWidth / 2.0f);
        float aTextBoxRight = round(aCenterX + mTextBoxWidth / 2.0f);
        
        mTextBox.SetFrame(aTextBoxLeft, 2.0f, mTextBoxWidth, mHeight - 4.0f);
        
        aTextBoxLeft -= 2.0f;
        aTextBoxRight += 2.0f;
        
        float aSpaceLeft = (aTextBoxLeft - aLeft);
        float aSpaceRight = (aRight - aTextBoxRight);
        
        int aCount = 1;
        if (aShow10) aCount = 2;
        if (aShow50) aCount = 3;
        float aButtonWidthLeft = aSpaceLeft;
        float aButtonWidthRight = aSpaceRight;
        if (aCount > 1) {
            aButtonWidthLeft = (aButtonWidthLeft -  2.0f * ((float)(aCount - 1))) / ((float)aCount);
            aButtonWidthRight = (aButtonWidthRight -  2.0f * ((float)(aCount - 1))) / ((float)aCount);
        }
        
        if (aShow50) {
            mButtonSub50.SetFrame(aLeft, 2.0f, aButtonWidthLeft, mHeight - 4.0f);
            aLeft += aButtonWidthLeft + 2.0f;
        }
        if (aShow10) {
            mButtonSub10.SetFrame(aLeft, 2.0f, aButtonWidthLeft, mHeight - 4.0f);
            aLeft += aButtonWidthLeft + 2.0f;
        }
        mButtonSub1.SetFrame(aLeft, 2.0f, aButtonWidthLeft, mHeight - 4.0f);

        mButtonAdd1.SetFrame(aTextBoxRight, 2.0f, aButtonWidthRight, mHeight - 4.0f);
        if (aShow10) {
            aTextBoxRight += aButtonWidthRight + 2.0f;
            mButtonAdd10.SetFrame(aTextBoxRight, 2.0f, aButtonWidthRight, mHeight - 4.0f);
        }
        if (aShow50) {
            aTextBoxRight += aButtonWidthRight + 2.0f;
            mButtonAdd50.SetFrame(aTextBoxRight, 2.0f, aButtonWidthRight, mHeight - 4.0f);
        }
    }
    if (aShow1) {
        mButtonAdd1.Activate();
        mButtonSub1.Activate();
    } else {
        mButtonAdd1.Deactivate();
        mButtonSub1.Deactivate();
    }
    if (aShow10) {
        mButtonAdd10.Activate();
        mButtonSub10.Activate();
    } else {
        mButtonAdd10.Deactivate();
        mButtonSub10.Deactivate();
    }
    if (aShow50) {
        mButtonAdd50.Activate();
        mButtonSub50.Activate();
    } else {
        mButtonAdd50.Deactivate();
        mButtonSub50.Deactivate();
    }
    if (aShowZero) {
        mButtonZero.Activate();
    } else {
        mButtonZero.Deactivate();
    }
}

void UIStepper::Update() {
    if (mTarget) {
        if (*mTarget != mValue) {
            SetValue(*mTarget);
        }
    }
}

void UIStepper::Draw() {
    
}

void UIStepper::SetValue(int pValue) {
    
    if (pValue > mMax) pValue = mMax;
    if (pValue < mMin) pValue = mMin;
    
    bool aNotify = (mValue != pValue);
    mValue = pValue;
    if (mTarget) {
        *mTarget = pValue;
    }
    
    int aTextNum = mTextBox.mText.ToInt();
    if (aTextNum != pValue) {
        mTextBox.mText = FString(pValue);
    }
    
    if (aNotify) {
        gNotify.Post(this, "stepper");
        if (mMenu) {
            mMenu->Notify(this, "stepper");
        }
    }
}

void UIStepper::SetTarget(int *pTarget) {
    mTarget = pTarget;
    if (mTarget) {
        int aValue = (*pTarget);
        SetValue(aValue);
    }
}

void UIStepper::Notify(void *pSender, const char *pNotification) {
    if (FString("text_box_change") == pNotification) {
        if (pSender == &mTextBox) {
            int aValue = mTextBox.mText.ToInt();
            if (aValue != mValue && aValue >= mMin && aValue <= mMax) {
                SetValue(aValue);
            }
        }
    }
    
    
    if (FString("button_click") == pNotification) {
        
        if (pSender == &mButtonZero) { SetValue(0); }
        
        if (pSender == &mButtonAdd1) { SetValue(mValue + 1); }
        if (pSender == &mButtonAdd10) { SetValue(mValue + 10); }
        if (pSender == &mButtonAdd50) { SetValue(mValue + 50); }
        
        if (pSender == &mButtonSub1) { SetValue(mValue - 1); }
        if (pSender == &mButtonSub10) { SetValue(mValue - 10); }
        if (pSender == &mButtonSub50) { SetValue(mValue - 50); }
    }
}

void UIStepper::SetText(const char *pText) {
    mLabelTitle.SetText(pText);
}
