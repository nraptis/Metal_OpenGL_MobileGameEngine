//
//  UISegment.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/4/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UISegment_hpp
#define UISegment_hpp

#include "ToolMenuSectionRow.hpp"
#include "UISegmentButton.hpp"

class UISegment : public ToolMenuSectionRow {
public:
    
    UISegment();
    UISegment(int pSegmentCount);
    virtual ~UISegment();
    
    virtual void                                Layout() override;
    virtual void                                Update() override;
    virtual void                                Notify(void *pSender, const char *pNotification) override;

    void                                        SetSegmentCount(int pSegmentCount);
    void                                        SetSelectedIndex(int pIndex);


    void                                        SetTitle(int pSegment, const char *pTitle);
    void                                        SetTitles(const char *pTitle1, const char *pTitle2=0, const char *pTitle3=0, const char *pTitle4=0, const char *pTitle5=0, const char *pTitle6=0, const char *pTitle7=0, const char *pTitle8=0, const char *pTitle9=0);

    void                                        SetTarget(int *pTarget);
    int                                         *mTarget;

    UISegmentButton                             **mButton;
    int                                         mSegmentCount;
    int                                         mSelectedIndex;
};

#endif /* UISegment_hpp */
