//
//  ToolMenuSectionRow.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef ToolMenuSectionRow_hpp
#define ToolMenuSectionRow_hpp

#include "FCanvas.hpp"
#include "UIRoundedRect.hpp"
#include "ToolMenuSection.hpp"
#include "UIElement.hpp"

class ToolMenuSectionRow : public ToolMenuSection {
public:
    ToolMenuSectionRow();
    virtual ~ToolMenuSectionRow();

    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            Layout();

    static float                            RowHeight();
    virtual void                            Notify(void *pSender, const char *pNotification);

    void                                    AddLabel(UILabel *pLabel);
    void                                    AddTextBox(UITextBox *pTextBox);
    
    void                                    AddButton(UIButton *pButton);
    void                                    AddCheckBox(UICheckBox *pCheckBox);
    void                                    AddAlignmentPicker(UIAlignmentPicker *pAlignmentPicker);
    

    void                                    AddElement(UIElement *pElement);

    FList                                   mElementList;
};

#endif
