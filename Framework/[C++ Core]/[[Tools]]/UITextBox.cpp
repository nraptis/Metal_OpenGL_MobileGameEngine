//
//  UITextBox.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "UITextBox.hpp"
#include "ToolMenuSectionRow.hpp"
#include "FApp.hpp"

UITextBox::UITextBox() {
    mConsumesTouches = true;
    mExclusiveKeyDownCaptureWhenSelected = true;
    mExclusiveKeyUpCaptureWhenSelected = false;
    
    mName = "UITextBox";
    mBold = false;
    mShrink = true;
    mPadding = 3.0f;
    mScale = 1.0f;
    mMinWidth = 60.0f;
    mSectionBackground.SetColorTop(0.165f, 0.145f, 0.215f);
    mSectionBackground.SetColorBottom(0.135f, 0.130f, 0.186f);
    mSectionBackground.mCornerRadius = 4.0f;
    
    mSectionBackgroundOutline.SetColorTop(0.4125, 0.4225, 0.3925, 1.0f);
    mSectionBackgroundOutline.SetColorBottom(0.44f, 0.475f, 0.46f, 1.0f);
    mSectionBackgroundOutline.mCornerRadius = 5.0f;
    
    
    mSectionBackgroundOutlineSelected.SetColorTop(0.7125, 0.7225, 0.7225, 1.0f);
    mSectionBackgroundOutlineSelected.SetColorBottom(0.74f, 0.775f, 0.67f, 1.0f);
    mSectionBackgroundOutlineSelected.mCornerRadius = 5.0f;
    
    
    mCursorBlinkTimer = 0;
    mCursor = 0;
    
    SetHeight(ToolMenuSectionRow::RowHeight());
    
    
}

UITextBox::~UITextBox() {
    
}

void UITextBox::Update() {
    if (gAppBase->mSelectedCanvas == this) {
        mCursorBlinkTimer += 1;
        if (mCursorBlinkTimer > 80) {
            mCursorBlinkTimer = 0;
        }
    } else {
        mCursorBlinkTimer = 0;
    }
}


void UITextBox::Layout() {
    mSectionBackground.SetRect(2.0f, 2.0f, mWidth - 4.0f, mHeight - 4.0f);
    mSectionBackground.mRefresh = true;
    mSectionBackgroundOutline.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mSectionBackgroundOutline.mRefresh = true;
    
    mSectionBackgroundOutlineSelected.SetRect(0.0f, 0.0f, mWidth, mHeight);
    mSectionBackgroundOutlineSelected.mRefresh = true;
}

void UITextBox::Draw() {
    
    if (gAppBase->mSelectedCanvas == this) {
        mSectionBackgroundOutlineSelected.Draw();
    } else {
        mSectionBackgroundOutline.Draw();
    }
    mSectionBackground.Draw();
    FFont *aFont = &(gAppBase->mSysFont);
    if (mBold) aFont = &(gAppBase->mSysFontBold);
    Graphics::PipelineStateSetSpritePremultipliedBlending();
    Graphics::SetColor(mColor);
    float aScale = mScale;
    if (mShrink) {
        aScale = aFont->ScaleForWidth(mText, mWidth - mPadding * 2.0f);
        if (aScale > mScale) { aScale = mScale; }
    }
    
    aFont->LeftCenter(mText, mPadding, mHeight2, aScale);
    
    float aCursorPos = aFont->LocationOfCursor(mCursor, mText.c(), mPadding, 0.0f, aScale);
    
    if (gAppBase->mSelectedCanvas == this) {
        
        if (mCursorBlinkTimer < 50) {
            Graphics::PipelineStateSetShape2DAlphaBlending();
            Graphics::SetColor();
            Graphics::DrawRect(aCursorPos -1.0f, 6.0f, 3.0f, mHeight - 12.0f);
        }
    }
    
    Graphics::SetColor();
}

void UITextBox::SetText(const char *pText) {
    mText = pText;
}

float UITextBox::GetIdealSize() {
    FFont *aFont = &(gAppBase->mSysFont);
    if (mBold) aFont = &(gAppBase->mSysFontBold);
    float aTextWidth = aFont->Width(mText.c(), mScale);
    if (aTextWidth < 20) { aTextWidth = 20.0f; }
    return aTextWidth + mPadding * 2.0f;
}


void UITextBox::SetTransparentBackground() {
    mSectionBackground.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackgroundOutline.ResetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mSectionBackground.mRefresh = true;
    mSectionBackgroundOutline.mRefresh = true;
}

void UITextBox::TouchDown(float pX, float pY, void *pData) {
    FFont *aFont = &(gAppBase->mSysFont);
    if (mBold) aFont = &(gAppBase->mSysFontBold);
    float aScale = mScale;
    if (mShrink) {
        aScale = aFont->ScaleForWidth(mText, mWidth - mPadding * 2.0f);
        if (aScale > mScale) { aScale = mScale; }
    }
    mCursor = aFont->GetCursor(pX, pY, mText.c(), mPadding, 0.0f, aScale);
}

void UITextBox::TouchMove(float pX, float pY, void *pData)  {
    
}

void UITextBox::TouchUp(float pX, float pY, void *pData)  {
    
}

void UITextBox::TouchFlush()  {
    
}

void UITextBox::KeyDown(int pKey)  {
    
    if (gAppBase->mSelectedCanvas != this) {
        return;
    }
    
    if (pKey == __KEY__ESCAPE) {
        SetText("");
        gNotify.Post(this, "text_box_change");
    }
    
    if (pKey == __KEY__ENTER) {
        gNotify.Post(this, "text_box_submit");
    }
    
    if (pKey == __KEY__DELETE) {
        
        FString aString = mText;
        if (mCursor <= 0) {
            return;
        } else if (mCursor >= mText.mLength) {
            aString = aString.GetSubString(0, aString.mLength - 1);
        } else {
            FString aHalf1 = aString.GetSubString(0, mCursor - 1);
            FString aHalf2 = aString.GetSubString(mCursor, aString.mLength);
            aString = aHalf1 + aHalf2;
        }
        mCursor -= 1;
        if (mCursor < 0) {
            mCursor = 0;
        }
        SetText(aString.c());
        gNotify.Post(this, "text_box_change");
        return;
    }
    
    if (pKey == __KEY__RIGHT) {
        mCursor += 1;
        if (mCursor > mText.mLength) {
            mCursor = mText.mLength;
        }
        return;
    }
    if (pKey == __KEY__LEFT) {
        mCursor -= 1;
        if (mCursor < 0) {
            mCursor = 0;
        }
        return;
    }
    
    char aChar = CharForKey(pKey);
    if (aChar != 0) {
        FString aString = mText;
        aString.Insert(aChar, mCursor);
        SetText(aString.c());
        ++mCursor;
        gNotify.Post(this, "text_box_change");
        return;
    }
}

void UITextBox::KeyUp(int pKey)  {
    
}

char UITextBox::CharForKey(int pKey) {
    
    bool aShift = gKeyDownShift;
    bool aCtrl = gKeyDownCtrl;
    bool aAlt = gKeyDownAlt;
    
    if (aShift == false && aCtrl == false && aAlt == false) {
        if (pKey == __KEY__0) { return '0'; }
        if (pKey == __KEY__1) { return '1'; }
        if (pKey == __KEY__2) { return '2'; }
        if (pKey == __KEY__3) { return '3'; }
        if (pKey == __KEY__4) { return '4'; }
        if (pKey == __KEY__5) { return '5'; }
        if (pKey == __KEY__6) { return '6'; }
        if (pKey == __KEY__7) { return '7'; }
        if (pKey == __KEY__8) { return '8'; }
        if (pKey == __KEY__9) { return '9'; }
        
        if (pKey == __KEY__MINUS) { return '-'; }
        if (pKey == __KEY__EQUALS) { return '='; }
        if (pKey == __KEY__SEMICOLON) { return ';'; }
        
        if (pKey == __KEY__APOSTROPHE) { return '\''; }
        
        if (pKey == __KEY__GRAVE) { return '`'; }
        
        if (pKey == __KEY__BACKSLASH) { return '\\'; }
        if (pKey == __KEY__SLASH) { return '/'; }
        
        if (pKey == __KEY__LBRACKET) { return '['; }
        if (pKey == __KEY__RBRACKET) { return ']'; }
        
        if (pKey == __KEY__SPACE) { return ' '; }
        if (pKey == __KEY__PERIOD) { return '.'; }
        if (pKey == __KEY__COMMA) { return ','; }
        
        if (pKey == __KEY__A) { return 'a'; }
        if (pKey == __KEY__B) { return 'b'; }
        if (pKey == __KEY__C) { return 'c'; }
        if (pKey == __KEY__D) { return 'd'; }
        if (pKey == __KEY__E) { return 'e'; }
        if (pKey == __KEY__F) { return 'f'; }
        if (pKey == __KEY__G) { return 'g'; }
        if (pKey == __KEY__H) { return 'h'; }
        if (pKey == __KEY__I) { return 'i'; }
        if (pKey == __KEY__J) { return 'j'; }
        if (pKey == __KEY__K) { return 'k'; }
        if (pKey == __KEY__L) { return 'l'; }
        if (pKey == __KEY__M) { return 'm'; }
        if (pKey == __KEY__N) { return 'n'; }
        if (pKey == __KEY__O) { return 'o'; }
        if (pKey == __KEY__P) { return 'p'; }
        if (pKey == __KEY__Q) { return 'q'; }
        if (pKey == __KEY__R) { return 'r'; }
        if (pKey == __KEY__S) { return 's'; }
        if (pKey == __KEY__T) { return 't'; }
        if (pKey == __KEY__U) { return 'u'; }
        if (pKey == __KEY__V) { return 'v'; }
        if (pKey == __KEY__W) { return 'w'; }
        if (pKey == __KEY__X) { return 'x'; }
        if (pKey == __KEY__Y) { return 'y'; }
        if (pKey == __KEY__Z) { return 'z'; }
    }
    
    if (aShift == true && aCtrl == false && aAlt == false) {
        if (pKey == __KEY__0) { return ')'; }
        if (pKey == __KEY__1) { return '!'; }
        if (pKey == __KEY__2) { return '@'; }
        if (pKey == __KEY__3) { return '#'; }
        if (pKey == __KEY__4) { return '$'; }
        if (pKey == __KEY__5) { return '%'; }
        if (pKey == __KEY__6) { return '^'; }
        if (pKey == __KEY__7) { return '&'; }
        if (pKey == __KEY__8) { return '*'; }
        if (pKey == __KEY__9) { return '('; }
        
        if (pKey == __KEY__MINUS) { return '_'; }
        if (pKey == __KEY__EQUALS) { return '+'; }
        if (pKey == __KEY__SEMICOLON) { return ':'; }
        
        if (pKey == __KEY__APOSTROPHE) { return '\"'; }
        
        if (pKey == __KEY__GRAVE) { return '~'; }
        
        if (pKey == __KEY__BACKSLASH) { return '|'; }
        if (pKey == __KEY__SLASH) { return '?'; }
        
        if (pKey == __KEY__LBRACKET) { return '{'; }
        if (pKey == __KEY__RBRACKET) { return '}'; }
        
        if (pKey == __KEY__PERIOD) { return '>'; }
        if (pKey == __KEY__COMMA) { return '<'; }
        
        if (pKey == __KEY__A) { return 'A'; }
        if (pKey == __KEY__B) { return 'B'; }
        if (pKey == __KEY__C) { return 'C'; }
        if (pKey == __KEY__D) { return 'D'; }
        if (pKey == __KEY__E) { return 'E'; }
        if (pKey == __KEY__F) { return 'F'; }
        if (pKey == __KEY__G) { return 'G'; }
        if (pKey == __KEY__H) { return 'H'; }
        if (pKey == __KEY__I) { return 'I'; }
        if (pKey == __KEY__J) { return 'J'; }
        if (pKey == __KEY__K) { return 'K'; }
        if (pKey == __KEY__L) { return 'L'; }
        if (pKey == __KEY__M) { return 'M'; }
        if (pKey == __KEY__N) { return 'N'; }
        if (pKey == __KEY__O) { return 'O'; }
        if (pKey == __KEY__P) { return 'P'; }
        if (pKey == __KEY__Q) { return 'Q'; }
        if (pKey == __KEY__R) { return 'R'; }
        if (pKey == __KEY__S) { return 'S'; }
        if (pKey == __KEY__T) { return 'T'; }
        if (pKey == __KEY__U) { return 'U'; }
        if (pKey == __KEY__V) { return 'V'; }
        if (pKey == __KEY__W) { return 'W'; }
        if (pKey == __KEY__X) { return 'X'; }
        if (pKey == __KEY__Y) { return 'Y'; }
        if (pKey == __KEY__Z) { return 'Z'; }
    }
    
    return 0;
}


