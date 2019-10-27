//
//  UILabel.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UILabel_hpp
#define UILabel_hpp

#include "FCanvas.hpp"
#include "UIRoundedRect.hpp"

class UILabel : public FCanvas {
public:
    UILabel();
    virtual ~UILabel();

    virtual void                            Draw();
    virtual void                            Layout();
    
    float                                   GetIdealSize();

    void                                    SetText(const char *pText);
    void                                    SetText(FString pText) { SetText((const char *)pText.c()); }
    
    void                                    SetTransparentBackground();

    UIRoundedRect                           mSectionBackgroundOutline;
    UIRoundedRect                           mSectionBackground;

    FColor                                  mColor;
    FString                                 mText;
    int                                     mAlignment;
    bool                                    mBold;
    bool                                    mShrink;
    float                                   mPadding;
    float                                   mScale;
    float                                   mMinWidth;

};

#endif

