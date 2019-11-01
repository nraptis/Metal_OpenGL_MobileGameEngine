//
//  Util_ScreenFrame.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef UTILITY_VIRTUAL_FRAME_RESIZE_TOOL_H
#define UTILITY_VIRTUAL_FRAME_RESIZE_TOOL_H

#include "FCanvas.hpp"

class Util_ScreenFrame : public FCanvas
{
public:
    Util_ScreenFrame();
    virtual ~Util_ScreenFrame();
    
    virtual void                            Layout();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    void                                    UpdateDrag(float pX, float pY, void *pData, bool pNotifyApp);
    
    void                                    RefreshVirtualFrame();
    
    void                                    ComputeResizeRect();
    
    float                                   mScreenResizeCornerX[4];
    float                                   mScreenResizeCornerY[4];
    float                                   mScreenResizeCornerDragStartX[4];
    float                                   mScreenResizeCornerDragStartY[4];
    
    float                                   mResizeLeft;
    float                                   mResizeTop;
    float                                   mResizeRight;
    float                                   mResizeBottom;
    float                                   mResizeWidth;
    float                                   mResizeHeight;
    
    float									mResizeDragCornerX;
    float									mResizeDragCornerY;
    int                                     mResizeCornerIndex;
    
    float                                   mPanWindowStartX;
    float                                   mPanWindowStartY;
    float                                   mPanTouchStartX;
    float                                   mPanTouchStartY;
    void                                    *mPanDragData;
};

#endif
