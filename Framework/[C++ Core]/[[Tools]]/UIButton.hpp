//
//  UIButton.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include "FButton.hpp"
#include "UIRoundedRect.hpp"

class UIButton : public FButton {
public:
    UIButton();
    virtual ~UIButton();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();
    
    float                                   GetIdealSize();

    void                                    SetTransparentBackground();
    
    UIRoundedRect                           mButtonBackground;
    UIRoundedRect                           mButtonOutline;

    UIRoundedRect                           mButtonBackgroundDown;
    UIRoundedRect                           mButtonOutlineDown;

    bool                                    mDrawCloseX;
    bool                                    mDrawMinimize;
    bool                                    mDrawMaximize;

    void                                    SetText(const char *pText) { mText = pText; }
    FString                                 mText;

    float                                   mFontScale;
    bool                                    mFontBold;
    float                                   mFontPadding;
    
    float                                   mBackgroundVerticalPadding;
    
};

#endif /* UIButton_hpp */
