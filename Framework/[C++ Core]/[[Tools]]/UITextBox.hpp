//
//  UITextBox.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/19/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef UITextBox_hpp
#define UITextBox_hpp

#include "FCanvas.hpp"
#include "UIRoundedRect.hpp"

class UITextBox : public FCanvas {
public:
    UITextBox();
    virtual ~UITextBox();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Layout();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    virtual void                            KeyDown(int pKey);
    virtual void                            KeyUp(int pKey);
    
    float                                   GetIdealSize();
    
    void                                    SetText(const char *pText);
    void                                    SetText(FString pText) { SetText((const char *)pText.c()); }
    void                                    SetTransparentBackground();
    
    char                                    CharForKey(int pKey);
    
    UIRoundedRect                           mSectionBackgroundOutline;
    UIRoundedRect                           mSectionBackgroundOutlineSelected;
    
    UIRoundedRect                           mSectionBackground;
    
    FString                                 mText;
    
    bool                                    mBold;
    bool                                    mShrink;
    float                                   mPadding;
    float                                   mScale;
    float                                   mMinWidth;
    
    int                                     mCursor;
    int                                     mCursorBlinkTimer;
};


#endif /* UITextBox_hpp */
