//
//  UIStepper.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/5/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UIStepper_hpp
#define UIStepper_hpp

#include "ToolMenuSectionRow.hpp"
#include "FSlider.hpp"
#include "UIRoundedRect.hpp"
#include "UILabel.hpp"
#include "UITextBox.hpp"

class UIStepper : public ToolMenuSectionRow {
public:
    UIStepper();
    virtual ~UIStepper();

    virtual void                                Layout();
    virtual void                                Update();
    virtual void                                Draw();
    virtual void                                Notify(void *pSender, const char *pNotification);


    void                                        SetText(const char *pText);
    void                                        SetValue(int pValue);
    void                                        SetTarget(int *pTarget);
    int                                         *mTarget;
    int                                         mValue;
    
    UILabel                                     mLabelTitle;
    
    int                                         mMax;
    int                                         mMin;
    
    UITextBox                                   mTextBox;
    
    UIButton                                    mButtonZero;
    
    UIButton                                    mButtonAdd50;
    UIButton                                    mButtonAdd10;
    UIButton                                    mButtonAdd1;
    UIButton                                    mButtonSub1;
    UIButton                                    mButtonSub10;
    UIButton                                    mButtonSub50;
    
    float                                       mLabelTitleWidth;
    float                                       mTextBoxWidth;
    
};

#endif
