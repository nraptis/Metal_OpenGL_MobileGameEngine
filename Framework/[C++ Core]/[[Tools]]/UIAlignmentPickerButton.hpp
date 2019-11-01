//
//  UIAlignmentPickerButton.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/6/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UIAlignmentPickerButton_hpp
#define UIAlignmentPickerButton_hpp

#include "FButton.hpp"
#include "UIRoundedRect.hpp"
#include "UIButton.hpp"

class UIAlignmentPickerButton : public UIButton {
public:
    UIAlignmentPickerButton();
    virtual ~UIAlignmentPickerButton();

    virtual void                            Layout();

    void                                    SetSelected(bool pState);
    bool                                    mSelected;
};

#endif /* UIAlignmentPickerButton_hpp */
