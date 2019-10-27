//
//  UIAlignmentPicker.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIAlignmentPicker.hpp"

//
//  UIAlignmentPicker.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIAlignmentPicker.hpp"
#include "ToolMenuSectionRow.hpp"
#include "FApp.hpp"

UIAlignmentPicker::UIAlignmentPicker() {
    mConsumesTouches = false;
    mName = "UIAlignmentPicker";

    mTarget = 0;

    mAlignX = -1;
    mAlignY = -1;

    SetSize(ToolMenuSectionRow::RowHeight(), ToolMenuSectionRow::RowHeight());

    mButtonTL = new UIAlignmentPickerButton();
    AddChild(mButtonTL);
    gNotify.Register(this, mButtonTL, "button_click");
    mButtonTC = new UIAlignmentPickerButton();
    AddChild(mButtonTC);
    gNotify.Register(this, mButtonTC, "button_click");
    mButtonTR = new UIAlignmentPickerButton();
    AddChild(mButtonTR);
    gNotify.Register(this, mButtonTR, "button_click");
    mButtonML = new UIAlignmentPickerButton();
    AddChild(mButtonML);
    gNotify.Register(this, mButtonML, "button_click");
    mButtonMC = new UIAlignmentPickerButton();
    AddChild(mButtonMC);
    gNotify.Register(this, mButtonMC, "button_click");
    mButtonMR = new UIAlignmentPickerButton();
    AddChild(mButtonMR);
    gNotify.Register(this, mButtonMR, "button_click");
    mButtonBL = new UIAlignmentPickerButton();
    AddChild(mButtonBL);
    gNotify.Register(this, mButtonBL, "button_click");
    mButtonBC = new UIAlignmentPickerButton();
    AddChild(mButtonBC);
    gNotify.Register(this, mButtonBC, "button_click");
    mButtonBR = new UIAlignmentPickerButton();
    AddChild(mButtonBR);
    gNotify.Register(this, mButtonBR, "button_click");
    UpdateDisplay();
}

UIAlignmentPicker::~UIAlignmentPicker() { }

void UIAlignmentPicker::Layout() {
    float aSpacing = 2.0f;
    float aSize = (float)((int)((mWidth - (aSpacing * 4.0f)) / 3.0f));
    float aCenterX = ((float)((int)(mWidth2 - aSize / 2.0f)));
    float aCenterY = ((float)((int)(mHeight2 - aSize / 2.0f)));
    float aLeft = aCenterX - (aSize + aSpacing);
    float aTop = aCenterY - (aSize + aSpacing);
    float aRight = aCenterX + (aSize + aSpacing);
    float aBottom = aCenterY + (aSize + aSpacing);
    mButtonTL->SetFrame(aLeft, aTop, aSize, aSize);
    mButtonTC->SetFrame(aCenterX, aTop, aSize, aSize);
    mButtonTR->SetFrame(aRight, aTop, aSize, aSize);
    mButtonML->SetFrame(aLeft, aCenterY, aSize, aSize);
    mButtonMC->SetFrame(aCenterX, aCenterY, aSize, aSize);
    mButtonMR->SetFrame(aRight, aCenterY, aSize, aSize);
    mButtonBL->SetFrame(aLeft, aBottom, aSize, aSize);
    mButtonBC->SetFrame(aCenterX, aBottom, aSize, aSize);
    mButtonBR->SetFrame(aRight, aBottom, aSize, aSize);
}

void UIAlignmentPicker::Notify(void *pSender, const char *pNotification) {
    if (pSender == mButtonTL) {
        mAlignX = -1;
        mAlignY = -1;
    }
    if (pSender == mButtonTC) {
        mAlignX =  0;
        mAlignY = -1;
    }
    if (pSender == mButtonTR) {
        mAlignX =  1;
        mAlignY = -1;
    }
    if (pSender == mButtonML) {
        mAlignX = -1;
        mAlignY =  0;
    }
    if (pSender == mButtonMC) {
        mAlignX = 0;
        mAlignY = 0;
    }
    if (pSender == mButtonMR) {
        mAlignX = 1;
        mAlignY = 0;
    }
    if (pSender == mButtonBL) {
        mAlignX = -1;
        mAlignY =  1;
    }
    if (pSender == mButtonBC) {
        mAlignX = 0;
        mAlignY = 1;
    }
    if (pSender == mButtonBR) {
        mAlignX = 1;
        mAlignY = 1;
    }
    if (mTarget) {
        mTarget->mX = mAlignX;
        mTarget->mY = mAlignY;
    }
    UpdateDisplay();
}

void UIAlignmentPicker::SetTarget(FIVec2 *pTarget) {
    if (pTarget) {
        mTarget = pTarget;
        mAlignX = pTarget->mX;
        mAlignY = pTarget->mY;
        UpdateDisplay();
    } else {
        mTarget = 0;
    }
}

void UIAlignmentPicker::UpdateDisplay() {
    if (mButtonTL) {
        mButtonTL->SetSelected(mAlignX == -1 && mAlignY == -1);
    }
    if (mButtonTC) {
        mButtonTC->SetSelected(mAlignX == 0 && mAlignY == -1);
    }
    if (mButtonTR) {
        mButtonTR->SetSelected(mAlignX == 1 && mAlignY == -1);
    }
    if (mButtonML) {
        mButtonML->SetSelected(mAlignX == -1 && mAlignY == 0);
    }
    if (mButtonMC) {
        mButtonMC->SetSelected(mAlignX == 0 && mAlignY == 0);
    }
    if (mButtonMR) {
        mButtonMR->SetSelected(mAlignX == 1 && mAlignY == 0);
    }
    if (mButtonBL) {
        mButtonBL->SetSelected(mAlignX == -1 && mAlignY == 1);
    }
    if (mButtonBC) {
        mButtonBC->SetSelected(mAlignX == 0 && mAlignY == 1);
    }
    if (mButtonBR) {
        mButtonBR->SetSelected(mAlignX == 1 && mAlignY == 1);
    }
}
