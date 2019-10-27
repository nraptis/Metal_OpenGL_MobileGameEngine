//
//  DragableCanvas.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef DragableCanvas_hpp
#define DragableCanvas_hpp

#include "FCanvas.hpp"

class DragableCanvas : public FCanvas {
public:
    DragableCanvas();
    virtual ~DragableCanvas();

    virtual void                            Draw();

    virtual FCanvas                         *BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed);
    virtual void                            BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    virtual void                            BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);

    void                                    UpdateCornerDrag(float pX, float pY, void *pData);
    void                                    UpdatePanDrag(float pX, float pY, void *pData);
    void                                    ResetCorners();
    float                                   mResizeCornerX[4];
    float                                   mResizeCornerY[4];
    float                                   mDragFrameStartX;
    float                                   mDragFrameStartY;
    float                                   mDragFrameStartWidth;
    float                                   mDragFrameStartHeight;
    float                                   mResizeDragCornerX;
    float                                   mResizeDragCornerY;
    float                                   mResizeDragTouchX;
    float                                   mResizeDragTouchY;
    void                                    *mResizeDragData;
    int                                     mResizeCornerIndex;
    float                                   mPanDragTouchX;
    float                                   mPanDragTouchY;
    void                                    *mPanDragData;
    bool                                    mPanConstrainToScreen;
    bool                                    mResizeDragAllowed;
    bool                                    mResizeDragAllowedH;
    bool                                    mResizeDragAllowedV;
    float                                   mSizeMinWidth;
    float                                   mSizeMinHeight;
    float                                   mResizeDragMinX;
    float                                   mResizeDragMinY;
    float                                   mResizeDragMaxX;
    float                                   mResizeDragMaxY;
};

#endif /* DragableCanvas_hpp */
