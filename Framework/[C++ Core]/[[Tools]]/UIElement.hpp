//
//  UIElement.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/5/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UIElement_hpp
#define UIElement_hpp

#include "FCanvas.hpp"

#define UI_ELEMENT_UNKNOWN 1
#define UI_ELEMENT_BUTTON 1
#define UI_ELEMENT_LABEL 2
#define UI_ELEMENT_TEXT_BOX 3
#define UI_ELEMENT_ALIGNMENT_PICKER 4
#define UI_ELEMENT_CHECKBOX 5
#define UI_ELEMENT_SEGMENT 6
#define UI_ELEMENT_STEPPER 7

class UIButton;
class UILabel;
class UICheckBox;
class UIAlignmentPicker;
class UITextBox;

class UIElement {
public:
    UIElement();
    virtual ~UIElement();

    void                        SetLabel(UILabel *pLabel);
    void                        SetButton(UIButton *pButton);
    void                        SetCheckBox(UICheckBox *pCheckBox);
    void                        SetAlignmentPicker(UIAlignmentPicker *pAlignmentPicker);
    void                        SetTextBox(UITextBox *pTextBox);
    
    
    FCanvas                     *mElement;
    int                         mType;

    bool                        mFixedWidth;
    int                         mMaxWidth;

    float                       mIdealWidth;
};

#endif
