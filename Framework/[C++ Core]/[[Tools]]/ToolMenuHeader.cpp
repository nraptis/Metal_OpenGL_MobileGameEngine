//
//  ToolMenuHeader.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuHeader.hpp"
#include "ToolMenu.hpp"
#include "ToolMenu.hpp"
#include "UIImagePicker.hpp"

ToolMenuHeader::ToolMenuHeader() {
    mMenu = 0;

    mName = "ToolMenuHeader";

    mConsumesTouches = false;

    mLabelTitle.mAlignment = 0;
    mLabelTitle.mBold = true;
    mLabelTitle.mShrink = true;
    mLabelTitle.mScale = 1.0f;
    mLabelTitle.SetTransparentBackground();
    AddChild(mLabelTitle);

    mMenuBackground.SetColorTop(0.125f, 0.125f, 0.125f);
    mMenuBackground.SetColorBottom(0.165f, 0.165f, 0.145f);
    mMenuBackground.mCornerRadius = 6.0f;
    mMenuBackground.mRoundBottom = false;

    mButtonClose.SetTransparentBackground();
    mButtonClose.mName = "Close Button";
    mButtonClose.mDrawCloseX = true;
    AddChild(mButtonClose);

    mButtonMinimize.SetTransparentBackground();
    mButtonMinimize.mName = "Minimize Button";
    mButtonMinimize.mDrawMinimize = true;
    AddChild(mButtonMinimize);
    
    gNotify.Register(this, &mButtonClose, "button_click");
    gNotify.Register(this, &mButtonMinimize, "button_click");
}

ToolMenuHeader::~ToolMenuHeader() {
    
}

void ToolMenuHeader::Layout() {
    float aButtonPadding = 4.0f;
    float aButtonSize = mHeight - aButtonPadding * 2.0f;
    mButtonClose.SetFrame(aButtonPadding, aButtonPadding, aButtonSize, aButtonSize);
    mButtonMinimize.SetFrame(mWidth - (aButtonPadding + aButtonSize), aButtonPadding, aButtonSize, aButtonSize);

    float aLabelLeft = mButtonClose.GetRight() + 2.0f;
    float aLabelRight = mButtonMinimize.GetLeft() - 2.0f;

    mLabelTitle.SetFrame(aLabelLeft, 2.0f, aLabelRight - aLabelLeft, mHeight - 4.0f);

    mMenuBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mMenuBackground.mRefresh = true;
}

void ToolMenuHeader::Update() {
    
}

void ToolMenuHeader::Draw() {
    Graphics::SetColor();
    Graphics::PipelineStateSetShape2DNoBlending();
    mMenuBackground.Draw();
}

void ToolMenuHeader::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        if (pSender == &mButtonClose) {
            if (mMenu) { mMenu->Kill(); }
        }
        if (pSender == &mButtonMinimize) {
            if (mMenu) {
                if (mMenu->mExpanded) {
                    mMenu->Collapse();
                } else {
                    mMenu->Expand();
                }
            }
        }
    }
}

void ToolMenuHeader::SetExpandedLayout() {
    mButtonMinimize.mDrawMaximize = false;
    mButtonMinimize.mDrawMinimize = true;
}

void ToolMenuHeader::SetCollapsedLayout() {
    mButtonMinimize.mDrawMaximize = true;
    mButtonMinimize.mDrawMinimize = false;
}



