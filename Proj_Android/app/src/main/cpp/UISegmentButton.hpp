//
//  UISegmentButton.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UISegmentButton_hpp
#define UISegmentButton_hpp

#include "UIRoundedRect.hpp"
#include "UIButton.hpp"

class UISegmentButton : public UIButton {
public:
    UISegmentButton();
    virtual ~UISegmentButton();
    
    virtual void                            Layout();

    void                                    SetSelected(bool pState);
    bool                                    mSelected;

    void                                    StyleSetLeft();
    void                                    StyleSetMiddle();
    void                                    StyleSetRight();
};

#endif /* UISegmentButton_hpp */
