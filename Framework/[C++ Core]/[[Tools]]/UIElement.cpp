//
//  UIElement.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/5/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "UIElement.hpp"
#include "UIStepper.hpp"
#include "UILabel.hpp"
#include "UIButton.hpp"
#include "UISlider.hpp"
#include "UISegment.hpp"
#include "UICheckBox.hpp"
#include "UIAlignmentPicker.hpp"
#include "UITextBox.hpp"

UIElement::UIElement() {
    mElement = 0;
    mType = UI_ELEMENT_UNKNOWN;

    mFixedWidth = false;
    mMaxWidth = 64;

    mIdealWidth = 0.0f;
}

UIElement::~UIElement() {

}

void UIElement::SetLabel(UILabel *pLabel) {
    mElement = pLabel;
    mType = UI_ELEMENT_LABEL;
    mFixedWidth = true;
}

void UIElement::SetTextBox(UITextBox *pTextBox) {
    mElement = pTextBox;
    mType = UI_ELEMENT_TEXT_BOX;
    mFixedWidth = false;
    mMaxWidth = 200;
}

void UIElement::SetButton(UIButton *pButton) {
    mElement = pButton;
    mType = UI_ELEMENT_BUTTON;
    mFixedWidth = false;
    mMaxWidth = 120;
}

void UIElement::SetCheckBox(UICheckBox *pCheckBox) {
    mElement = pCheckBox;
    mType = UI_ELEMENT_CHECKBOX;
    mFixedWidth = true;
}

void UIElement::SetAlignmentPicker(UIAlignmentPicker *pAlignmentPicker) {
    mElement = pAlignmentPicker;
    mType = UI_ELEMENT_ALIGNMENT_PICKER;
}






