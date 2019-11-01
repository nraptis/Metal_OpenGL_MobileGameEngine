//
//  FWindow.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/14/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_WINDOW_HPP
#define FRAMEWORK_WINDOW_HPP

#include "FCanvas.hpp"
#include "FList.hpp"
#include "FFileTable.hpp"

class FWindow {
public:
    FWindow();
    ~FWindow();

    void                                            AddChild(FCanvas *pCanvas);
    void                                            AddChild(FCanvas &pCanvas);

    void                                            Update();
    void                                            Draw();
    void                                            Active();
    void                                            Inactive();
    void                                            MemoryWarning(bool pSevere);
    
    bool                                            TouchDown(float pX, float pY, void *pData);
    void                                            TouchMove(float pX, float pY, void *pData);
    void                                            TouchUp(float pX, float pY, void *pData);
    void                                            TouchFlush();

    bool                                            MouseDown(float pX, float pY, int pButton);
    bool                                            MouseMove(float pX, float pY);
    void                                            MouseUp(float pX, float pY, int pButton);
    void                                            MouseWheel(int pDirection);

    void                                            KeyDown(int pKey);
    void                                            KeyUp(int pKey);
    
    void                                            SetDeviceSize(int pWidth, int pHeight);

    //This is the "virtual" or "app" frame,
    void                                            SetVirtualFrame(int pX, int pY, int pWidth, int pHeight);
    
    void                                            SetSafeAreaInsets(int pInsetUp, int pInsetRight, int pInsetDown, int pInsetLeft);

    void                                            RegisterRealize(FCanvas *pCanvas);
    //1.) A child was added.
    //2.) A child was removed.
    //3.) A child's frame has changed.
    void                                            RegisterChildrenDidUpdate(FCanvas *pCanvas);

    //1.) The parent's frame has changed.
    //void                                            RegisterParentDidUpdate(FCanvas *pCanvas);

    void                                            RegisterTransformDidUpdate(FCanvas *pCanvas);
    void                                            RegisterFrameDidUpdate(FCanvas *pCanvas);
    void                                            RegisterKill(FCanvas *pCanvas);
    void                                            RegisterDealloc(FCanvas *pCanvas);
    
    
    void                                            RefreshAll();
    void                                            RefreshAll(FCanvas *pCanvas, FList *pList);
    
//protected:

    
    FCanvas                                         *mSelectedCanvas;
    
    
    void                                            PrintTempList(const char *pName);

    //As bucket items are being processed, we empty them into the
    //temp list. Essentially we do this because the bucket's content
    //may change as it is being iterated over. We just re-visit on
    //the next cycle through the layout pipeline.
    FList                                           mTemp;

    //bucket of items which must be layed out, and recursively have
    //all of their children layed out. Intelligently stores only the
    //highest level / necessary nodes, children are removed as the
    //bucket's contents update...
    FCanvasBucket                                   mRealizeBucket;

    //bucket of items which will must be layed out...
    FCanvasBucket                                   mLayoutBucket;

    //bucket of items who's frames have changed since their previous
    //layout. Both the parent and children must have layout called
    //again. In a bad conceivable case, frame and layout buckets will
    //juggle canvases back and forth up to 5 or 6 times, if the layouts
    //are getting stuck in an infinite loop, please make sure that your
    //parent and child canvases don't have a "layout cycle" e.g. just
    //have either the parent depend on the child or vice-versa. Use
    //transforms to accomplish more complex layout scemes.
    //FCanvasBucket                                   mFrameUpdateBucket;
    FCanvasBucket                                   mTransformUpdateBucket;

    //The parent update bucket and children update bucket will be
    //layed out on the next layout iteration. These buckets may be
    //able to be simply added into the layout bucket.
    //FCanvasBucket                                 mParentUpdateBucket;
    //FCanvasBucket                                 mChildrenUpdateBucket;

    FCanvasBucket                                   mKillBucket;

    int                                             mDeviceWidth;
    int                                             mDeviceHeight;

    int                                             mVirtualFrameX;
    int                                             mVirtualFrameY;
    int                                             mVirtualFrameWidth;
    int                                             mVirtualFrameHeight;
    
    int                                             mSafeAreaInsetTop;
    int                                             mSafeAreaInsetRight;
    int                                             mSafeAreaInsetBottom;
    int                                             mSafeAreaInsetLeft;
    
    FCanvas                                         mRoot;
};

#endif
