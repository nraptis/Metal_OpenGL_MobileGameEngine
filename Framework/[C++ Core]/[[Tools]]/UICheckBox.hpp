//
//  UICheckBox.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/5/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UICheckBox_hpp
#define UICheckBox_hpp

#include "FButton.hpp"
#include "UIRoundedRect.hpp"

class UICheckBox : public FButton {
public:
    UICheckBox();
    virtual ~UICheckBox();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchUp(float pX, float pY, void *pData);
    void                                    CheckedStateDidUpdate();
    
    float                                   GetIdealSize();
    

    void                                    SetTarget(bool *pTarget);
    bool                                    *mTarget;

    UIRoundedRect                           mButtonBackground;
    UIRoundedRect                           mButtonOutline;
    UIRoundedRect                           mButtonBackgroundDown;
    UIRoundedRect                           mButtonOutlineDown;

    UIRoundedRect                           mCheckBackground;
    UIRoundedRect                           mCheckOutline;
    
    
    void                                    SetText(const char *pText) { mText = pText; }
    FString                                 mText;

    void                                    SetChecked(bool pChecked);
    

    float                                   mFontScale;
    float                                   mTextCenterX;

    bool                                    mIsChecked;
};

#endif
