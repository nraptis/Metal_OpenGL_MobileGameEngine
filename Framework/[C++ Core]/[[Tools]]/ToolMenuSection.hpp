//
//  ToolMenuSection.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenuSection_hpp
#define ToolMenuSection_hpp

#include "UIRoundedRect.hpp"
#include "UIButton.hpp"

class ToolMenu;
class ToolMenuSection : public FCanvas {
public:
    ToolMenuSection();
    virtual ~ToolMenuSection();

    
    virtual void                            Update() override;
    virtual void                            Draw() override;
    virtual void                            Layout() override;
    
    virtual void                            TouchDown(float pX, float pY, void *pData) override;
    virtual void                            TouchMove(float pX, float pY, void *pData) override;
    virtual void                            TouchUp(float pX, float pY, void *pData) override;
    virtual void                            TouchFlush() override;
    
    virtual void                            Notify(void *pSender, const char *pNotification) override;

    void                                    SetTransparentBackground();
    
    void                                    StyleSetPicker();
    

    

    int                                     mSectionDepth;

    UIRoundedRect                           mSectionBackgroundOutline;
    UIRoundedRect                           mSectionBackground;

    FList                                   mSectionList;

    ToolMenu                                *mMenu;
};

#endif
