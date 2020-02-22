//
//  ToolMenu.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenu.hpp"
#include "FApp.hpp"





ToolMenu::ToolMenu() {
    mName = "ToolMenu";
    mClipEnabled = false;
    mClipDisabled = true;
    mRecievesConsumedTouches = false;
    
    mScrollMode = true;
    mExpanded = true;
    mExpandedHeight = 340.0f;
    mManualSectionLayout = false;

    mMenuBackground.SetColorTop(0.125f, 0.125f, 0.125f);
    mMenuBackground.SetColorBottom(0.165f, 0.135f, 0.085f);
    mMenuBackground.mCornerRadius = 8.0f;

    mMenuBackgroundOutline.SetColorTop(0.925f, 0.925f, 0.925f);
    mMenuBackgroundOutline.SetColorBottom(0.965f, 0.965f, 0.965f);
    mMenuBackgroundOutline.mCornerRadius = 8.0f;

    mMenuBackgroundShadow.SetColorTop(0.021f, 0.021f, 0.021f, 0.25f);
    mMenuBackgroundShadow.SetColorBottom(0.025f, 0.025f, 0.025f, 0.25f);
    mMenuBackgroundShadow.mCornerRadius = 8.0f;

    mScrollContent.mEnabledX = false;
    mScrollContent.mRecievesConsumedTouches = false;
    mScrollContent.mClipEnabled = true;
    mScrollContent.mMenu = this;
    
    AddChild(mScrollContent);

    mContent.mMenu = this;
    mContent.mClipEnabled = true;
    AddChild(mContent);

    mHeader.mMenu = this;
    AddChild(mHeader);
}

ToolMenu::~ToolMenu() {
    
}

void ToolMenu::Layout() {
    float aHeaderHeight = 56.0f;
    float aContentWidth = mWidth - 4.0f;
    float aContentHeight = 0.0f;
    EnumList(ToolMenuSection, aSection, mSectionList) {
        SetSectionDepths(aSection, 0);
        if (aSection->mHidden == false) {
            SetMenu(aSection);
            if (mManualSectionLayout == false) {
                aSection->SetFrame(2.0f, aContentHeight, aContentWidth - 4.0f, aSection->mHeight);
            }
            aContentHeight += aSection->mHeight;
        }
    }
    mContent.SetFrame(2.0f, aHeaderHeight + 2.0f, aContentWidth, mHeight - (aHeaderHeight + 4.0f));
    mScrollContent.SetFrame(2.0f, aHeaderHeight + 2.0f, aContentWidth, mHeight - (aHeaderHeight + 4.0f));
    mScrollContent.SetContentSize(aContentWidth, aContentHeight);
    mHeader.SetFrame(1.0f, 1.0f, mWidth - 2.0f, aHeaderHeight);
    mMenuBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mMenuBackgroundOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mMenuBackgroundShadow.SetRect(-2.0f, -2.0f, mWidth + 4.0f, mHeight + 4.0f);
    mMenuBackground.mRefresh = true;
    mMenuBackgroundOutline.mRefresh = true;
    mMenuBackgroundShadow.mRefresh = true;
}

void ToolMenu::Update() {
    
}

void ToolMenu::Draw() {
    Graphics::SetColor();
    mMenuBackgroundShadow.Draw();
    mMenuBackgroundOutline.Draw();
    mMenuBackground.Draw();
}

void ToolMenu::TouchDown(float pX, float pY, void *pData) {
    if (mParent) {
        mParent->BringChildToFront(this);
    }
}

void ToolMenu::TouchMove(float pX, float pY, void *pData) {

}

void ToolMenu::TouchUp(float pX, float pY, void *pData) {

}

void ToolMenu::TouchFlush() {

}

void ToolMenu::Notify(void *pSender, const char *pNotification) {
    Kill();
}

void ToolMenu::DeactivateCloseButton() {
    mHeader.mButtonClose.Deactivate();

}

void ToolMenu::SetScrollMode(bool pScroll) {
    mScrollMode = pScroll;
    if (pScroll) {
        BringChildToFront(mScrollContent);
        mScrollContent.mEnabled = true;
        mScrollContent.mHidden = false;
        mContent.mEnabled = false;
        mContent.mHidden = true;
    } else {
        BringChildToFront(mContent);
        mScrollContent.mEnabled = false;
        mScrollContent.mHidden = true;
        mContent.mEnabled = true;
        mContent.mHidden = false;
    }
    BringChildToFront(mHeader);
}

void ToolMenu::SetTitle(const char *pText) {
    mHeader.mLabelTitle.mText = pText;
}

void ToolMenu::AddSection(ToolMenuSection *pSection) {
    if (pSection) {

    mSectionList.Add(pSection);
    if (mScrollMode) {
        mScrollContent.AddChild(pSection);
    } else {
        mContent.AddChild(pSection);
    }
    SetSectionDepths(pSection, 0);
        SetMenu(pSection);
    }
}

void ToolMenu::SetSectionDepths(ToolMenuSection *pSection, int pDepth) {
    if (pSection) {
        if (pSection->mSectionDepth != pDepth) {
            pSection->mSectionDepth = pDepth;
            pSection->FrameDidUpdate();
        }

        EnumList(ToolMenuSection, aSubsection, pSection->mSectionList) {
            SetSectionDepths(aSubsection, pDepth + 1);
        }
    }
}

void ToolMenu::SetMenu(ToolMenuSection *pSection) {
    if (pSection) {
        pSection->mMenu = this;
        EnumList(ToolMenuSection, aSubsection, pSection->mSectionList) {
            SetMenu(aSubsection);
        }
    }
}

void ToolMenu::Expand() {
    mExpanded = true;
    mResizeDragAllowed = true;
    SetScrollMode(mScrollMode);
    SetHeight(mExpandedHeight);
    mHeader.SetExpandedLayout();
}

void ToolMenu::Collapse() {
    mExpandedHeight = mHeight;
    mExpanded = false;
    mResizeDragAllowed = false;
    mScrollContent.mEnabled = false;
    mScrollContent.mHidden = true;
    mContent.mEnabled = false;
    mContent.mHidden = true;
    SetHeight(58.0f);
    mHeader.SetCollapsedLayout();
}



ToolMenuScrollCanvas::ToolMenuScrollCanvas() {
    mMenu = NULL;
}

ToolMenuScrollCanvas::~ToolMenuScrollCanvas() {
    
}

void ToolMenuScrollCanvas::TouchDown(float pX, float pY, void *pData) {
    if (mMenu != NULL) {
        if (mMenu->mParent != NULL) {
            mMenu->mParent->BringChildToFront(mMenu);
        }
    }
}



ToolMenuCanvas::ToolMenuCanvas() {
    mMenu = NULL;
}

ToolMenuCanvas::~ToolMenuCanvas() {
    
}

void ToolMenuCanvas::TouchDown(float pX, float pY, void *pData) {
    if (mMenu != NULL) {
        if (mMenu->mParent != NULL) {
            mMenu->mParent->BringChildToFront(mMenu);
        }
    }
}
