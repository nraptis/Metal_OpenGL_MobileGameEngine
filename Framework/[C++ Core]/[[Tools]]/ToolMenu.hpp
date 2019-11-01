//
//  ToolMenu.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenu_hpp
#define ToolMenu_hpp

#include "DragableCanvas.hpp"
#include "UIRoundedRect.hpp"
#include "ToolMenuHeader.hpp"
#include "UISlider.hpp"
#include "UIButton.hpp"
#include "UISegment.hpp"
#include "UICheckBox.hpp"
#include "UITextBox.hpp"
#include "UIStepper.hpp"
#include "UIAlignmentPicker.hpp"
#include "FScrollCanvas.hpp"
#include "ToolMenuSection.hpp"
#include "ToolMenuPanel.hpp"

class ToolMenu;
class ToolMenuScrollCanvas : public FScrollCanvas {
public:
    ToolMenuScrollCanvas();
    virtual ~ToolMenuScrollCanvas();
    virtual void                            TouchDown(float pX, float pY, void *pData) override;
    ToolMenu                                *mMenu;
};

class ToolMenuCanvas : public FCanvas {
public:
    ToolMenuCanvas();
    virtual ~ToolMenuCanvas();
    virtual void                            TouchDown(float pX, float pY, void *pData) override;
    ToolMenu                                *mMenu;
};

class ToolMenu : public DragableCanvas {
public:
    ToolMenu();
    virtual ~ToolMenu();

    virtual void                            Update() override;
    virtual void                            Draw() override;
    virtual void                            Layout() override;
    
    virtual void                            TouchDown(float pX, float pY, void *pData) override;
    virtual void                            TouchMove(float pX, float pY, void *pData) override;
    virtual void                            TouchUp(float pX, float pY, void *pData) override;
    virtual void                            TouchFlush() override;

    virtual void                            Notify(void *pSender, const char *pNotification) override;

    //Step 1
    void                                    SetTitle(const char *pText);

    //Step 2
    void                                    SetScrollMode(bool pScroll);

    //Step 3
    void                                    AddSection(ToolMenuSection *pSection);

    void                                    SetSectionDepths(ToolMenuSection *pSection, int pDepth);
    void                                    SetMenu(ToolMenuSection *pSection);


    void                                    DeactivateCloseButton();

    void                                    Expand();
    void                                    Collapse();
    bool                                    mExpanded;
    float                                   mExpandedHeight;


    ToolMenuHeader                          mHeader;

    //Use either flat content or scroll content...
    ToolMenuCanvas                          mContent;
    ToolMenuScrollCanvas                    mScrollContent;

    bool                                    mManualSectionLayout;

    FList                                   mSectionList;

    bool                                    mScrollMode;

    UIRoundedRect                           mMenuBackground;
    UIRoundedRect                           mMenuBackgroundOutline;
    UIRoundedRect                           mMenuBackgroundShadow;
};

#endif /* ToolMenu_hpp */
