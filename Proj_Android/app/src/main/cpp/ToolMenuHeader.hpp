//
//  ToolMenuHeader.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenuHeader_hpp
#define ToolMenuHeader_hpp

#include "FCanvas.hpp"
#include "UIRoundedRect.hpp"
#include "UIButton.hpp"
#include "UILabel.hpp"

class ToolMenu;
class ToolMenuHeader : public FCanvas {
public:
    ToolMenuHeader();
    virtual ~ToolMenuHeader();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();
    virtual void                            Notify(void *pSender, const char *pNotification);

    void                                    SetExpandedLayout();
    void                                    SetCollapsedLayout();


    ToolMenu                                *mMenu;

    UILabel                                 mLabelTitle;
    UIButton                                mButtonClose;
    UIButton                                mButtonMinimize;

    UIRoundedRect                           mMenuBackground;
};

#endif /* ToolMenuHeader_hpp */
