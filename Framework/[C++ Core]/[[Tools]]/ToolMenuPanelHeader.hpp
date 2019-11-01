//
//  ToolMenuPanelHeader.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenuPanelHeader_hpp
#define ToolMenuPanelHeader_hpp

#include "FCanvas.hpp"
#include "UIRoundedRect.hpp"
#include "UIButton.hpp"
#include "UILabel.hpp"

class ToolMenuPanel;
class ToolMenuPanelHeader : public FCanvas {
public:
    ToolMenuPanelHeader();
    virtual ~ToolMenuPanelHeader();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);

    void                                    SetExpandedLayout();
    void                                    SetCollapsedLayout();

    void                                    SetSectionDepth(int pSectionDepth);

    
    ToolMenuPanel                           *mPanel;

    UILabel                                 mLabelTitle;
    UIButton                                mButtonMinimize;

    UIRoundedRect                           mMenuBackground;
};


#endif /* ToolMenuPanelHeader_hpp */
