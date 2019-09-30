//
//  ToolMenuSectionRow.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "ToolMenuSectionRow.hpp"
#include "UIElement.hpp"
#include "UIStepper.hpp"
#include "UILabel.hpp"
#include "UIButton.hpp"
#include "UISlider.hpp"
#include "UISegment.hpp"
#include "UICheckBox.hpp"
#include "UITextBox.hpp"
#include "UIAlignmentPicker.hpp"

ToolMenuSectionRow::ToolMenuSectionRow() {
    mName = "row";
    SetHeight(ToolMenuSectionRow::RowHeight());
    SetTransparentBackground();
}

ToolMenuSectionRow::~ToolMenuSectionRow() {

}

float ToolMenuSectionRow::RowHeight() {
    return 44.0f;
}

void ToolMenuSectionRow::Layout() {
    ToolMenuSection::Layout();

    float aElementGroupWidth = 0.0f;
    float aSpacing = 2.0f;
    int aResizableCount = 0;
    int aButtonCount = 0;
    int aLabelCount = 0;

    EnumList(UIElement, aElement, mElementList) {
        if (aElement->mType == UI_ELEMENT_BUTTON) {
            UIButton *aButton = (UIButton *)(aElement->mElement);
            float aIdealWidth = aButton->GetIdealSize();
            if (aIdealWidth < 60.0f) aIdealWidth = 60.0f;
            aElement->mIdealWidth = aIdealWidth;
            aElementGroupWidth += aIdealWidth + aSpacing;
            aResizableCount += 1;
            aButtonCount += 1;
        }
        if (aElement->mType == UI_ELEMENT_CHECKBOX) {
            UICheckBox *aCheckBox = (UICheckBox *)(aElement->mElement);
            float aIdealWidth = aCheckBox->GetIdealSize();
            aElement->mIdealWidth = aIdealWidth;
            aElementGroupWidth += aIdealWidth + aSpacing;
            aResizableCount += 1;
        }
        if (aElement->mType == UI_ELEMENT_LABEL) {
            UILabel *aLabel = (UILabel *)(aElement->mElement);
            float aIdealWidth = aLabel->GetIdealSize();
            aElement->mIdealWidth = aIdealWidth;
            aElementGroupWidth += aIdealWidth + aSpacing;
            aResizableCount += 1;
            aLabelCount += 1;
        }
        if (aElement->mType == UI_ELEMENT_TEXT_BOX) {
            UITextBox *aTextBox = (UITextBox *)(aElement->mElement);
            float aIdealWidth = aTextBox->GetIdealSize();
            if (aIdealWidth < 80.0f) { aIdealWidth = 80.0f; }
            if (aIdealWidth > 120.0f) { aIdealWidth = 120.0f; }
            
            
            aElement->mIdealWidth = aIdealWidth;
            aElementGroupWidth += aIdealWidth + aSpacing;
            aResizableCount += 1;
            aLabelCount += 1;
        }

        if (aElement->mType == UI_ELEMENT_ALIGNMENT_PICKER) {
            float aIdealWidth = ToolMenuSectionRow::GetHeight();
            aElement->mIdealWidth = aIdealWidth;
            aElementGroupWidth += aIdealWidth + aSpacing;
        }
    }

    float aOverFlow = mWidth - aElementGroupWidth;
    if (aOverFlow < 0) {
        aOverFlow = -aOverFlow;
        int aShrinkCount = aButtonCount + aLabelCount;
        if (aShrinkCount > 0) {

            bool aReloop = true;
            while (aReloop && aOverFlow > 0.0f) {
                aReloop = false;

                EnumList(UIElement, aElement, mElementList) {
                    if (aElement->mType == UI_ELEMENT_BUTTON ||
                        aElement->mType == UI_ELEMENT_LABEL ||
                        aElement->mType == UI_ELEMENT_TEXT_BOX) {
                        if (aElement->mIdealWidth > 60.0f && aOverFlow > 0.0f) {
                            aReloop = true;
                            aElement->mIdealWidth -= 1.0f;
                            aOverFlow -= 1.0f;
                        }
                        if (aElement->mIdealWidth > 120.0f && aOverFlow > 0.0f) {
                            aReloop = true;
                            aElement->mIdealWidth -= 1.0f;
                            aOverFlow -= 1.0f;
                        }
                    }
                }
            }
        }
    } else {
        if (aResizableCount > 0) {
            float aGrowPerElement = aOverFlow / ((float)aResizableCount);
            EnumList(UIElement, aElement, mElementList) {
                if (aElement->mType == UI_ELEMENT_BUTTON ||
                    aElement->mType == UI_ELEMENT_CHECKBOX ||
                    aElement->mType == UI_ELEMENT_LABEL ||
                    aElement->mType == UI_ELEMENT_TEXT_BOX) {
                    aElement->mIdealWidth += aGrowPerElement;
                }
            }
        }
    }

    float aElementX = 0.0f;
    EnumList(UIElement, aElement, mElementList) {
        aElement->mElement->SetWidth(aElement->mIdealWidth);
        aElement->mElement->SetX(aElementX);
        aElementX += aElement->mElement->GetWidth() + aSpacing;
    }
}

void ToolMenuSectionRow::Update() {

}

void ToolMenuSectionRow::Draw() {
    
    Graphics::PipelineStateSetShape2DAlphaBlending();
    Graphics::SetColor();
    
    
    mSectionBackgroundOutline.Draw();
    mSectionBackground.Draw();
}

void ToolMenuSectionRow::Notify(void *pSender, const char *pNotification) {
    ToolMenuSection::Notify(pSender, pNotification);
    
}

void ToolMenuSectionRow::AddLabel(UILabel *pLabel) {
    if (pLabel) {
        
        UIElement *aElement = new UIElement();
        aElement->SetLabel(pLabel);
        AddElement(aElement);
    }
}

void ToolMenuSectionRow::AddTextBox(UITextBox *pTextBox) {
    
    if (pTextBox) {
        
        UIElement *aElement = new UIElement();
        aElement->SetTextBox(pTextBox);
        AddElement(aElement);
        gNotify.Register(this, pTextBox, "text_box_change");
        gNotify.Register(this, pTextBox, "text_box_submit");
        
    }
}

void ToolMenuSectionRow::AddButton(UIButton *pButton) {
    if (pButton) {
        UIElement *aElement = new UIElement();
        aElement->SetButton(pButton);
        AddElement(aElement);
        gNotify.Register(this, pButton, "button_click");
    }
}

void ToolMenuSectionRow::AddCheckBox(UICheckBox *pCheckBox) {
    if (pCheckBox) {
        UIElement *aElement = new UIElement();
        aElement->SetCheckBox(pCheckBox);
        AddElement(aElement);
        gNotify.Register(this, pCheckBox, "checkbox");
    }
}

void ToolMenuSectionRow::AddAlignmentPicker(UIAlignmentPicker *pAlignmentPicker) {
    if (pAlignmentPicker) {
        UIElement *aElement = new UIElement();
        aElement->SetAlignmentPicker(pAlignmentPicker);
        AddElement(aElement);
        gNotify.Register(this, pAlignmentPicker, "alignment");
    }
}
                              ;

void ToolMenuSectionRow::AddElement(UIElement *pElement) {
    if (pElement) {
        if (pElement->mElement) {
            AddChild(pElement->mElement);
            mElementList.Add(pElement);
        }
    }
}
