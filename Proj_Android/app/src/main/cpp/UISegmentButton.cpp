//
//  UISegmentButton.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UISegmentButton.hpp"
#include "FApp.hpp"

UISegmentButton::UISegmentButton() {
    mName = "UISegmentButton";

    mSelected = false;
    SetSelected(mSelected);
    
    mBackgroundVerticalPadding = 4.0f;

    mButtonBackground.mCornerRadius = 8.0f;
    mButtonBackgroundDown.mCornerRadius = 8.0f;
    mButtonOutline.mCornerRadius = 8.0f;
    mButtonOutlineDown.mCornerRadius = 8.0f;
}

UISegmentButton::~UISegmentButton() {

}

void UISegmentButton::Layout() {
    UIButton::Layout();
}

void UISegmentButton::StyleSetLeft() {
    mButtonBackground.mRoundLeft = true;
    mButtonBackground.mRoundRight = false;

    mButtonBackgroundDown.mRoundLeft = true;
    mButtonBackgroundDown.mRoundRight = false;

    mButtonOutline.mRoundLeft = true;
    mButtonOutline.mRoundRight = false;

    mButtonOutlineDown.mRoundLeft = true;
    mButtonOutlineDown.mRoundRight = false;

    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}

void UISegmentButton::StyleSetMiddle() {
    mButtonBackground.mRoundLeft = false;
    mButtonBackground.mRoundRight = false;

    mButtonBackgroundDown.mRoundLeft = false;
    mButtonBackgroundDown.mRoundRight = false;

    mButtonOutline.mRoundLeft = false;
    mButtonOutline.mRoundRight = false;

    mButtonOutlineDown.mRoundLeft = false;
    mButtonOutlineDown.mRoundRight = false;

    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}

void UISegmentButton::StyleSetRight() {
    mButtonBackground.mRoundLeft = false;
    mButtonBackground.mRoundRight = true;

    mButtonBackgroundDown.mRoundLeft = false;
    mButtonBackgroundDown.mRoundRight = true;

    mButtonOutline.mRoundLeft = false;
    mButtonOutline.mRoundRight = true;

    mButtonOutlineDown.mRoundLeft = false;
    mButtonOutlineDown.mRoundRight = true;

    mButtonBackground.mRefresh = true;
    mButtonBackgroundDown.mRefresh = true;
    mButtonOutline.mRefresh = true;
    mButtonOutlineDown.mRefresh = true;
}

void UISegmentButton::SetSelected(bool pState) {
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


        //let styleColorBlue = UIColor(red: 0.2156863, green: 0.352941, blue: 0.7647059, alpha: 1.0)
        //let styleColorBlueLight = UIColor(red: 0.2156863 * 1.2, green: 0.352941 * 1.2, blue: 0.7647059 * 1.2, alpha: 1.0)
        //let styleColorBlueDark = UIColor(red: 0.2156863 * 0.8, green: 0.352941 * 0.8, blue: 0.7647059 * 0.8, alpha: 1.0)

        //let styleColorOrange = UIColor(red: 1.0, green: 0.49412, blue: 0.0, alpha: 1.0)
        //let styleColorOrangeLight = UIColor(red: 1.0, green: 0.57, blue: 0.1125, alpha: 1.0)
        //let styleColorOrangeDark = UIColor(red: 1.0 * 0.8, green: 0.49412 * 0.8, blue: 0.0 * 0.8, alpha: 1.0)

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

