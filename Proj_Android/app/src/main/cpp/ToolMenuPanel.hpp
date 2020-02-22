//
//  ToolMenuPanelPanelPanel.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef TOOL_MENU_PANEL_HPP
#define TOOL_MENU_PANEL_HPP

#include "FCanvas.hpp"
#include "UIRoundedRect.hpp"
#include "ToolMenuPanelHeader.hpp"
#include "ToolMenuSection.hpp"
#include "UIButton.hpp"

class ToolMenuPanel : public ToolMenuSection {
public:
    ToolMenuPanel();
    virtual ~ToolMenuPanel();
    
    virtual void                            Layout();

    virtual void                            Notify(void *pSender, const char *pNotification);

    //Step 1
    void                                    SetTitle(const char *pText);

    //Step 2
    void                                    AddSection(ToolMenuSection *pSection);

    void                                    Expand();
    void                                    Collapse();
    bool                                    mExpanded;
    
    ToolMenuPanelHeader                     mHeader;
    FCanvas                                 mContent;
    
};

#endif
