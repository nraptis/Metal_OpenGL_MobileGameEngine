//
//  ToolMenuSection.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuSection.hpp"
#include "FApp.hpp"
#include "ToolMenu.hpp"

ToolMenuSection::ToolMenuSection() {
    mName = "ToolMenuSection";
    mConsumesTouches = false;

    mSectionDepth = 0;
    
    mSectionBackground.SetColorTop(0.45f, 0.44f, 0.485f);
    mSectionBackground.SetColorBottom(0.52f, 0.54f, 0.575f);
    mSectionBackground.mCornerRadius = 3.0f;

    mSectionBackgroundOutline.SetColorTop(0.65f, 0.65f, 0.685f);
    mSectionBackgroundOutline.SetColorBottom(0.59f, 0.59f, 0.62f);
    mSectionBackgroundOutline.mCornerRadius = 4.0f;

    mMenu = 0;

    mLayoutBubbleUpDepth = 2;
}

ToolMenuSection::~ToolMenuSection() {

}

void ToolMenuSection::Layout() {
    mSectionBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mSectionBackground.mRefresh = true;
    mSectionBackgroundOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mSectionBackgroundOutline.mRefresh = true;
}

void ToolMenuSection::Update() {

}

void ToolMenuSection::Draw() {
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor();
    
    
    mSectionBackgroundOutline.Draw();
    mSectionBackground.Draw();
}

void ToolMenuSection::TouchDown(float pX, float pY, void *pData) {
    if (mMenu != NULL) {
        if (mMenu->mParent != NULL) {
            mMenu->mParent->BringChildToFront(mMenu);
        }
    }
}

void ToolMenuSection::TouchMove(float pX, float pY, void *pData) {
    
}

void ToolMenuSection::TouchUp(float pX, float pY, void *pData) {
    
}

void ToolMenuSection::TouchFlush() {
    
}

void ToolMenuSection::Notify(void *pSender, const char *pNotification) {
    if (mMenu) {
        mMenu->Notify(pSender, pNotification);
    }
}

void ToolMenuSection::SetTransparentBackground() {
    mSectionBackground.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackgroundOutline.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackground.mRefresh = true;
    mSectionBackgroundOutline.mRefresh = true;
}

void ToolMenuSection::StyleSetPicker() {
    
    
    mSectionBackground.SetColorTop(0.48f, 0.48f, 0.51f);
    mSectionBackground.SetColorBottom(0.45f, 0.45f, 0.48f);
    mSectionBackground.mRefresh = true;
    
    mSectionBackgroundOutline.SetColorTop(0.68f, 0.68f, 0.68f);
    mSectionBackgroundOutline.SetColorBottom(0.65f, 0.65f, 0.65f);
    mSectionBackgroundOutline.mRefresh = true;
    
    
    
    
}
