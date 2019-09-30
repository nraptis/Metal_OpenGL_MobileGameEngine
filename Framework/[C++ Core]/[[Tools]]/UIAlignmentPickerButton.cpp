//
//  UIAlignmentPickerButton.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIAlignmentPickerButton.hpp"

UIAlignmentPickerButton::UIAlignmentPickerButton() {
    mName = "UIAlignmentPickerButton";
    mSelected = false;
    SetSelected(mSelected);
    mBackgroundVerticalPadding = 0.0f;
    mButtonBackground.mCornerRadius = 2.0f;
    mButtonBackgroundDown.mCornerRadius = 2.0f;
    mButtonOutline.mCornerRadius = 2.0f;
    mButtonOutlineDown.mCornerRadius = 2.0f;
}

UIAlignmentPickerButton::~UIAlignmentPickerButton() {

}

void UIAlignmentPickerButton::Layout() {
    UIButton::Layout();
    
}

void UIAlignmentPickerButton::SetSelected(bool pState) {
    mSelected = pState;
    if (mSelected) {
        mButtonBackground.SetColorTop(1.0f, 0.49412f, 0.0f);
        mButtonBackground.SetColorBottom(0.965f, 0.4825f, 0.025f);
        mButtonBackgroundDown.SetColorTop(1.0f * 0.85f, 0.49412f * 0.85f, 0.0f);
        mButtonBackgroundDown.SetColorBottom(0.965f * 0.85f, 0.4825f * 0.85f, 0.025f * 0.85f);
        mButtonOutline.SetColorTop(1.0f, 1.0f, 1.0f);
        mButtonOutline.SetColorBottom(1.0f, 1.0f, 1.0f);
        mButtonOutlineDown.SetColorTop(0.85f, 0.85f, 0.85f);
        mButtonOutlineDown.SetColorBottom(0.85f, 0.85f, 0.85f);

    } else {
        mButtonBackground.SetColorTop(0.167f, 0.167f, 0.167f);
        mButtonBackground.SetColorBottom(0.175f, 0.175f, 0.175f);
        mButtonBackgroundDown.SetColorTop(0.127f, 0.127f, 0.127f);
        mButtonBackgroundDown.SetColorBottom(0.0988f, 0.1f, 0.1f);
        mButtonOutline.SetColorTop(0.375, 0.375, 0.373);
        mButtonOutline.SetColorBottom(0.366f, 0.366f, 0.366f);
        mButtonOutlineDown.SetColorTop(0.345, 0.345, 0.343);
        mButtonOutlineDown.SetColorBottom(0.32f, 0.32f, 0.32f);
    }
    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}

