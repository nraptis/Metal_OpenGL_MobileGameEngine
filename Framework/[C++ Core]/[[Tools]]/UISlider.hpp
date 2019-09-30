//
//  UISlider.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UI_SLIDER_HPP
#define UI_SLIDER_HPP

#include "ToolMenuSectionRow.hpp"
#include "FSlider.hpp"
#include "UIRoundedRect.hpp"
#include "UILabel.hpp"
#include "UIButton.hpp"

class UISlider : public ToolMenuSectionRow {
public:
    UISlider();
    virtual ~UISlider();


    virtual void                                Layout();

    virtual void                                Update();
    virtual void                                Draw();

    virtual void                                Notify(void *pSender, const char *pNotification);

    void                                        SetText(const char *pText);
    void                                        SetRange(float pMin, float pMax);

    float                                       GetValue();
    void                                        SetTarget(float *pTargetValue);
    float                                       *mTargetValue;
    float                                       mValue;
    
    void                                        SliderDidUpdate();
    
    
    ToolMenuSection                             mSliderContainer;
    ToolMenuSectionRow                          mButtonsContainer;
    
    UIButton                                    *mButtonResetZero;
    UIButton                                    *mButtonResetDefault;
    UIButton                                    *mButtonResetOne;
    
    
    UILabel                                     mLabelTitle;
    UILabel                                     mLabelValue;

    float                                       mLabelTitleWidth;
    float                                       mLabelValueWidth;

    FSlider                                     mBaseSlider;
    float                                       mBarHeight;
    float                                       mBarHeightInner;

    float                                       mDefaultValue;
    bool                                        mDefaultValueAssigned;
    
    
    UIRoundedRect                               mRectBarOutline;
    UIRoundedRect                               mRectBarLeft;
    UIRoundedRect                               mRectBarRight;

    UIRoundedRect                               mRectThumbOutline;
    UIRoundedRect                               mRectThumb;

    float                                       mPreviousDrawMin;
    float                                       mPreviousDrawMax;

};

#endif /* UISlider_hpp */
