//
//  ToolMenuPanelHeader.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuPanelHeader.hpp"
#include "ToolMenu.hpp"
#include "ToolMenuPanel.hpp"

ToolMenuPanelHeader::ToolMenuPanelHeader() {
    mPanel = 0;
    mName = "ToolMenuPanelHeader";
    mConsumesTouches = false;
    mLabelTitle.mAlignment = 0;
    mLabelTitle.mBold = false;
    mLabelTitle.mShrink = true;
    mLabelTitle.mScale = 0.75f;
    mLabelTitle.SetTransparentBackground();
    AddChild(mLabelTitle);
    mMenuBackground.ResetColor(0.35f, 0.36f, 0.28f);
    mMenuBackground.mCornerRadius = 4.0f;
    mMenuBackground.mRoundBottom = false;


    mButtonMinimize.SetTransparentBackground();
    mButtonMinimize.mName = "Minimize Button";
    mButtonMinimize.mDrawMinimize = true;
    AddChild(mButtonMinimize);

    gNotify.Register(this, &mButtonMinimize, "button_click");
}

ToolMenuPanelHeader::~ToolMenuPanelHeader() {

}

void ToolMenuPanelHeader::Layout() {
    float aButtonPadding = 4.0f;
    float aButtonSize = mHeight - aButtonPadding * 2.0f;
    mButtonMinimize.SetFrame(mWidth - (aButtonPadding + aButtonSize), aButtonPadding, aButtonSize, aButtonSize);
    float aLabelLeft = 4.0f;
    float aLabelRight = mButtonMinimize.GetLeft() - 2.0f;
    mLabelTitle.SetFrame(aLabelLeft, 2.0f, aLabelRight - aLabelLeft, mHeight - 4.0f);
    mMenuBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mMenuBackground.mRefresh = true;
}

void ToolMenuPanelHeader::Update() {

}

void ToolMenuPanelHeader::Draw() {
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor();
    
    mMenuBackground.Draw();
}

void ToolMenuPanelHeader::Notify(void *pSender, const char *pNotification) {
    if (FString(pNotification) == "button_click") {
        if (pSender == &mButtonMinimize) {
            if (mPanel) {
                if (mPanel->mExpanded) {
                    mPanel->Collapse();
                } else {
                    mPanel->Expand();
                }
            }
        }
    }
}

void ToolMenuPanelHeader::SetSectionDepth(int pSectionDepth) {
    if (pSectionDepth == 0) {
        mMenuBackground.ResetColor(0.191f, 0.19f, 0.23f);
    }
    if (pSectionDepth == 1) {
        mMenuBackground.ResetColor(0.14f, 0.13f, 0.14f);

    }
    if (pSectionDepth == 2) {
        mMenuBackground.ResetColor(0.24f, 0.24f, 0.25f);
    }
    if (pSectionDepth == 3) {
        mMenuBackground.ResetColor(0.16f, 0.15f, 0.16f);
    }
    Layout();
}


void ToolMenuPanelHeader::SetExpandedLayout() {
    mButtonMinimize.mDrawMaximize = false;
    mButtonMinimize.mDrawMinimize = true;
}

void ToolMenuPanelHeader::SetCollapsedLayout() {
    mButtonMinimize.mDrawMaximize = true;
    mButtonMinimize.mDrawMinimize = false;
}



