//
//  ToolMenuPanelPanelPanel.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuPanel.hpp"
#include "FApp.hpp"

ToolMenuPanel::ToolMenuPanel() {
    mName = "ToolMenuPanel";
    mExpanded = true;
    mContent.mConsumesTouches = false;
    AddChild(mContent);
    mHeader.mPanel = this;
    AddChild(mHeader);
}

ToolMenuPanel::~ToolMenuPanel() {

}

void ToolMenuPanel::Layout() {
    
    mHeader.SetSectionDepth(mSectionDepth);
    if (mSectionDepth == 0) {
        mSectionBackground.ResetColor(0.28f, 0.28f, 0.28f);
        mSectionBackgroundOutline.ResetColor(0.36f, 0.36f, 0.36f);
    }
    if (mSectionDepth == 1) {
        mSectionBackground.ResetColor(0.34f, 0.35f, 0.36f);
        mSectionBackgroundOutline.ResetColor(0.386f, 0.40f, 0.40f);
    }
    if (mSectionDepth == 2) {
        mSectionBackground.ResetColor(0.15f, 0.14f, 0.15f);
        mSectionBackgroundOutline.ResetColor(0.24f, 0.26f, 0.24f);
    }
    if (mSectionDepth == 3) {
        mSectionBackground.ResetColor(0.24f, 0.24f, 0.24f);
        mSectionBackgroundOutline.ResetColor(0.28f, 0.28f, 0.28f);
    }
    
    ToolMenuSection::Layout();
    float aHeaderHeight = 44.0f;
    float aContentWidth = mWidth - 4.0f;
    float aContentHeight = 6.0f;
    EnumList(ToolMenuSection, aSection, mSectionList) {
        if (aSection->mHidden == false) {
            aSection->SetFrame(3.0f, aContentHeight, aContentWidth - 6.0f, aSection->mHeight);
            aContentHeight += aSection->mHeight + 6.0f;
        }
    }
    if (aContentHeight < 44.0f) { aContentHeight = 44.0f; }
    mContent.SetFrame(2.0f, aHeaderHeight + 2.0f, aContentWidth, aContentHeight);
    mHeader.SetFrame(1.0f, 1.0f, mWidth - 2.0f, aHeaderHeight);

    if (mExpanded) {
        SetHeight(aContentHeight + 46.0f);
    } else {
        SetHeight(46.0f);
    }
}

void ToolMenuPanel::Notify(void *pSender, const char *pNotification) {
    ToolMenuSection::Notify(pSender, pNotification);

}

void ToolMenuPanel::SetTitle(const char *pText) {
    mHeader.mLabelTitle.mText = pText;
}

void ToolMenuPanel::AddSection(ToolMenuSection *pSection) {
    if (mMenu) { pSection->mMenu = mMenu; }
    mSectionList.Add(pSection);
    mContent.AddChild(pSection);
}


void ToolMenuPanel::Expand() {
    float aContentHeight = 0.0f;
    EnumList(ToolMenuSection, aSection, mSectionList) {
        aContentHeight += aSection->mHeight;
    }
    if (aContentHeight < 32.0f) { aContentHeight = 32.0f; }
    mExpanded = true;
    mContent.mEnabled = true;
    mContent.mHidden = false;
    mHeader.SetExpandedLayout();
    SetHeight(aContentHeight + 46.0f);
}

void ToolMenuPanel::Collapse() {
    mExpanded = false;
    mContent.mEnabled = false;
    mContent.mHidden = true;
    mHeader.SetCollapsedLayout();
    SetHeight(46.0f);
}








