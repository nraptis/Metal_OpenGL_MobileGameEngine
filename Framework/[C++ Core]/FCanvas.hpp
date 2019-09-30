//
//  FCanvas.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_CANVAS_HPP
#define FRAMEWORK_CANVAS_HPP

#define CANVAS_TRACKED_TOUCH_COUNT 6

#include "FList.hpp"
#include "FRect.hpp"
#include "FColor.hpp"
#include "FString.hpp"
#include "FSprite.hpp"
#include "FVec2.hpp"
#include "FObject.hpp"

class FCanvasTransform {
public:
    FCanvasTransform();
    ~FCanvasTransform();

    float                                       mX;
    float                                       mY;

    float                                       mScale;

    float                                       mScaleX;
    float                                       mScaleY;

    float                                       mRotation;

    float                                       mAnchorX;
    float                                       mAnchorY;
};

class FCanvasAbsoluteTransform {
public:
    FCanvasAbsoluteTransform();
    ~FCanvasAbsoluteTransform();

    void                                        Transform(float &pX, float &pY);
    void                                        Untransform(float &pX, float &pY);

    void                                        Transform(float &pX, float &pY, float pWidth, float pHeight);
    void                                        Untransform(float &pX, float &pY, float pWidth, float pHeight);

    void                                        ApplyAbsoluteTransformation(FCanvasAbsoluteTransform *pParentTransform, float pParentX, float pParentY, float pParentWidth, float pParentHeight, FCanvasTransform *pTransform, float pX, float pY, float pWidth, float pHeight);

    void                                        ApplyAbsoluteTransformation(FCanvasTransform *pTransform, float pX, float pY, float pWidth, float pHeight);

    bool                                        ContainsPoint(float pX, float pY);

    float                                       mX;
    float                                       mY;

    float                                       mScale;

    float                                       mScaleX;
    float                                       mScaleY;

    float                                       mRotation;

    float                                       mAnchorX;
    float                                       mAnchorY;

    float                                       mCornerX[4];
    float                                       mCornerY[4];
};

class FWindow;
class FCanvas : public FObject {
    friend class FWindow;
    friend class FNotificationCenter;
    
public:
    FCanvas();
    virtual ~FCanvas();

    virtual void                                Layout();
    virtual void                                LayoutTransform();
    
    
    virtual void                                Update();
    virtual void                                Draw();

    virtual void                                MouseDown(float pX, float pY, int pButton);
    virtual void                                MouseMove(float pX, float pY);
    virtual void                                MouseUp(float pX, float pY, int pButton);
    virtual void                                MouseWheel(int pDirection);

    virtual void                                TouchDown(float pX, float pY, void *pData);
    virtual void                                TouchMove(float pX, float pY, void *pData);
    virtual void                                TouchUp(float pX, float pY, void *pData);
    virtual void                                TouchFlush();

    virtual void                                KeyDown(int pKey);
    virtual void                                KeyUp(int pKey);

    virtual void                                Notify(void *pSender, const char *pNotification);

    void                                        AddChild(FCanvas *pCanvas);
    void                                        AddChild(FCanvas &pCanvas);
    void                                        Kill();

    bool                                        IsChild(FCanvas *pCanvas);

    float                                       mMouseX;
    float                                       mMouseY;

    float                                       mTouchX;
    float                                       mTouchY;
    
    void                                        DrawManual();
    bool                                        mDrawManual;
    
    void                                        DrawTransform();
    
    FString                                     mName;

    int                                         mLayoutBubbleUpDepth;
    
    FCanvasTransform                            mTransform;
    FCanvasAbsoluteTransform                    mTransformAbsolute;
    
    FColor                                      mColor;

    float                                       mX;
    float                                       mY;
    float                                       mWidth;
    float                                       mHeight;
    float                                       mWidth2;
    float                                       mHeight2;

    FWindow                                     *mWindow;
    FCanvas                                     *mParent;
    
    FList                                       mChildren;
    
    bool                                        mExclusiveKeyDownCaptureWhenSelected;
    bool                                        mExclusiveKeyUpCaptureWhenSelected;
    
    
    bool                                        mClipEnabled;
    bool                                        mClipDisabled;;

    void                                        Activate();
    void                                        Deactivate();

    bool                                        mHidden;
    bool                                        mEnabled;
    
    bool                                        mConsumesTouches;
    bool                                        mRecievesOutsideTouches;
    bool                                        mRecievesConsumedTouches;

    bool                                        mMouseOver;

    bool                                        mMouseLeftDown;
    bool                                        mMouseMiddleDown;
    bool                                        mMouseRightDown;

    bool                                        mMouseLeftDownInside;
    bool                                        mMouseMiddleDownInside;
    bool                                        mMouseRightDownInside;

    bool                                        mTouchDownInside;
    bool                                        mTouchDown;
    int                                         mTouchCount;

    void                                        BringChildToFront(FCanvas *pCanvas);
    inline void                                 BringChildToFront(FCanvas &pCanvas){BringChildToFront(&pCanvas);}
    void                                        SendChildToBack(FCanvas *pCanvas);
    inline void                                 SendChildToBack(FCanvas &pCanvas){SendChildToBack(&pCanvas);}
    void                                        SendChildBackward(FCanvas *pCanvas);
    inline void                                 SendChildBackward(FCanvas &pCanvas){SendChildBackward(&pCanvas);}
    void                                        BringChildForward(FCanvas *pCanvas);
    inline void                                 BringChildForward(FCanvas &pCanvas){BringChildForward(&pCanvas);}
    
    virtual void                                SetFrame(float pX, float pY, float pWidth, float pHeight);
    inline void                                 SetFrame(FRect pRect){SetFrame(pRect.mX, pRect.mY, pRect.mWidth, pRect.mHeight);}
    
    inline void                                 SetSize(float pWidth, float pHeight) { SetFrame(GetX(), GetY(), pWidth, pHeight); }
    inline void                                 SetSize(FSprite *pSprite){ if (pSprite) SetSize(pSprite->mWidth, pSprite->mHeight); }
    inline void                                 SetSize(FSprite &pSprite) { SetSize(&pSprite); }

    void                                        SetPos(float pX, float pY) { SetX(pX); SetY(pY); }
    void                                        SetX(float pX);
    void                                        SetY(float pY);
    void                                        SetWidth(float pWidth);
    void                                        SetHeight(float pHeight);

    float                                       GetX() { float aResult = mX;return aResult; }
    float                                       GetY() { float aResult = mY;return aResult; }
    float                                       GetLeft() { return GetX(); }
    float                                       GetTop() { return GetY(); }
    float                                       GetWidth() { float aResult = mWidth;return aResult; }
    float                                       GetHeight(){ float aResult = mHeight;return aResult; }
    float                                       GetWidth2(){ float aResult = mWidth2;return aResult; }
    float                                       GetHeight2(){ float aResult = mHeight2;return aResult; }
    float                                       GetCenterX(){ return GetWidth2(); }
    float                                       GetCenterY(){ return GetHeight2(); }
    float                                       GetRight(){ float aResult = GetX() + GetWidth();return aResult; }
    float                                       GetBottom(){ float aResult = GetY() + GetHeight();return aResult; }
    FVec2                                       GetCenter() { FVec2 aResult;aResult.mX=GetCenterX();aResult.mY=GetCenterY();return aResult; }

    void                                        SetTransformTranslate(float pX, float pY);
    void                                        SetTransformX(float pX);
    void                                        SetTransformY(float pY);
    void                                        SetTransformScale(float pScale);
    void                                        SetTransformScale(float pScaleX, float pScaleY);
    void                                        SetTransformScaleX(float pScaleX);
    void                                        SetTransformScaleY(float pScaleY);
    void                                        SetTransformRotation(float pRotation);
    void                                        SetTransformAnchorX(float pAnchorX);
    void                                        SetTransformAnchorY(float pAnchorY);
    void                                        SetTransformAnchor(float pAnchorX, float pAnchorY);
    
    float                                       GetTransformX(){return mTransform.mX;}
    float                                       GetTransformY(){return mTransform.mY;}
    float                                       GetTransformScale(){return mTransform.mScale;}
    float                                       GetTransformScaleX(){return mTransform.mScaleX;}
    float                                       GetTransformScaleY(){return mTransform.mScaleY;}
    float                                       GetTransformRotation(){return mTransform.mRotation;}
    float                                       GetTransformAnchorX(){return mTransform.mAnchorX;}
    float                                       GetTransformAnchorY(){return mTransform.mAnchorY;}
    
    static void                                 ConvertPoint(float &pX, float &pY, FCanvas *pFromCanvas, FCanvas *pToCanvas);
    void                                        ConvertPoint(float &pX, float &pY, FCanvas *pFromCanvas) { ConvertPoint(pX, pY, pFromCanvas, this); }
    void                                        ConvertPoint(float &pX, float &pY, FCanvas &pFromCanvas) { ConvertPoint(pX, pY, &pFromCanvas, this); }
    static void                                 ConvertPoint(float &pX, float &pY, FCanvas &pFromCanvas, FCanvas &pToCanvas) { ConvertPoint(pX, pY, &pFromCanvas, &pToCanvas); }
    static void                                 ConvertPoint(float &pX, float &pY, FCanvas *pFromCanvas, FCanvas &pToCanvas) { ConvertPoint(pX, pY, pFromCanvas, &pToCanvas); }
    static void                                 ConvertPoint(float &pX, float &pY, FCanvas &pFromCanvas, FCanvas *pToCanvas) { ConvertPoint(pX, pY, &pFromCanvas, pToCanvas); }
    
    static FVec2                               Convert(float pX, float pY, FCanvas *pFromCanvas, FCanvas *pToCanvas);
    static FVec2                               Convert(float pX, float pY, FCanvas &pFromCanvas, FCanvas &pToCanvas) { return Convert(pX, pY, &pFromCanvas, &pToCanvas); }
    static FVec2                               Convert(float pX, float pY, FCanvas *pFromCanvas, FCanvas &pToCanvas) { return Convert(pX, pY, pFromCanvas, &pToCanvas); }
    static FVec2                               Convert(float pX, float pY, FCanvas &pFromCanvas, FCanvas *pToCanvas) { return Convert(pX, pY, &pFromCanvas, pToCanvas); }
    
    static FVec2                               Convert(FVec2 pPos, FCanvas *pFromCanvas, FCanvas *pToCanvas) { return Convert(pPos.mX, pPos.mY, pFromCanvas, pToCanvas); }
    static FVec2                               Convert(FVec2 pPos, FCanvas &pFromCanvas, FCanvas &pToCanvas) { return Convert(pPos, &pFromCanvas, &pToCanvas); }
    static FVec2                               Convert(FVec2 pPos, FCanvas *pFromCanvas, FCanvas &pToCanvas) { return Convert(pPos.mX, pPos.mY, pFromCanvas, &pToCanvas); }
    static FVec2                               Convert(FVec2 pPos, FCanvas &pFromCanvas, FCanvas *pToCanvas) { return Convert(pPos.mX, pPos.mY, &pFromCanvas, pToCanvas); }
    
    static float                                ConvertScale(float pScale, FCanvas *pFromCanvas, FCanvas *pToCanvas);
    static float                                ConvertScale(float pScale, FCanvas &pFromCanvas, FCanvas &pToCanvas) { return ConvertScale(pScale, &pFromCanvas, &pToCanvas); }
    static float                                ConvertScale(float pScale, FCanvas *pFromCanvas, FCanvas &pToCanvas) { return ConvertScale(pScale, pFromCanvas, &pToCanvas); }
    static float                                ConvertScale(float pScale, FCanvas &pFromCanvas, FCanvas *pToCanvas) { return ConvertScale(pScale, &pFromCanvas, pToCanvas); }
    
    static float                                ConvertRotation(float pDegrees, FCanvas *pFromCanvas, FCanvas *pToCanvas);
    static float                                ConvertRotation(float pDegrees, FCanvas &pFromCanvas, FCanvas &pToCanvas) { return ConvertRotation(pDegrees, &pFromCanvas, &pToCanvas); }
    static float                                ConvertRotation(float pDegrees, FCanvas *pFromCanvas, FCanvas &pToCanvas) { return ConvertRotation(pDegrees, pFromCanvas, &pToCanvas); }
    static float                                ConvertRotation(float pDegrees, FCanvas &pFromCanvas, FCanvas *pToCanvas) { return ConvertRotation(pDegrees, &pFromCanvas, pToCanvas); }

    void                                        *mTouchData[CANVAS_TRACKED_TOUCH_COUNT];
    bool                                        mTouchInside[CANVAS_TRACKED_TOUCH_COUNT];

    void                                        ComputeAbsoluteTransformation();
    
    bool                                        mDeleteWhenKilled;

    bool                                        mDidUpdate;

    //Since our children could change during certain operations such
    //as update or mouse down, we copy them to this buffer before
    //batching most common operations through to the children.
    FList                                       mProcessChildren;

    //When the transform updates, we do not need to re-layout the
    //parent or children.
    void                                        TransformDidUpdate();

    //When the frame updates, we need to re-layout the parent and children.
    void                                        FrameDidUpdate();

    //The frame has changed.. May be called multiple times.
    virtual void                                BaseLayout();
    
    virtual void                                BaseLayoutTransform();
    
    
    
    virtual void                                BaseUpdate();
    virtual void                                BaseDraw();

    virtual FCanvas                             *BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed);
    virtual void                                BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    virtual void                                BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent);
    virtual void                                BaseTouchFlush();

    virtual FCanvas                             *BaseMouseDown(float pX, float pY, float pOriginalX, float pOriginalY, int pButton, bool pOutsideParent, bool &pConsumed);
    virtual bool                                BaseMouseMove(float pX, float pY, float pOriginalX, float pOriginalY, bool pOutsideParent);
    virtual void                                BaseMouseUp(float pX, float pY, float pOriginalX, float pOriginalY, int pButton, bool pOutsideParent);
    virtual void                                BaseMouseWheel(int pDirection);

    virtual void                                BaseKeyDown(int pKey);
    virtual void                                BaseKeyUp(int pKey);

    virtual void                                BaseNotify(void *pSender, const char *pNotification);
};


//Canvas bucket is a fast access storage container for
//canvases
class FCanvasBucket;
class FCanvasBucketNode {
    friend class FCanvasBucket;
public:
    FCanvasBucketNode();
    virtual ~FCanvasBucketNode();

    FCanvas                                         *mCanvas;

    FCanvasBucketNode                               *mListPrev;
    FCanvasBucketNode                               *mListNext;

private:
    FCanvasBucketNode                               *mTableNext;

    int                                             mTableIndex;
};

class FCanvasBucket {
public:

    FCanvasBucket();
    ~FCanvasBucket();

    void                                            Add(FCanvas *pCanvas);
    void                                            Remove(FCanvas *pCanvas);
    bool                                            Exists(FCanvas *pCanvas);

    bool                                            IsEmpty();

    void                                            RemoveAll();
    bool                                            ParentExists(FCanvas *pCanvas);
    void                                            RemoveAllChildren(FCanvas *pCanvas);

    void                                            AddCanvasesToList(FList *pList);
    void                                            AddCanvasesToListAndRemoveAll(FList *pList);
    void                                            AddCanvasesAndChildrenRecursivelyToListAndRemoveAll(FList *pList);

public:

    FCanvasBucketNode                               *mListHead;
    FCanvasBucketNode                               *mListTail;

protected:

    void                                            ListAdd(FCanvasBucketNode *pNode);
    void                                            ListRemove(FCanvasBucketNode *pNode);
    
    void                                            SetTableSize(int pSize);

    FCanvasBucketNode                               **mTable;
    int                                             mTableCount;
    int                                             mTableSize;



    FList                                           mQueue;
};


class FCanvasAnimation {
public:
    FCanvasAnimation();
    FCanvasAnimation(FCanvas *pCanvas);
    ~FCanvasAnimation();

    bool                            Update();
    void                            SetUp(FCanvas *pCanvas);

    void                            Generate(int pFunction, int pTicks);
    void                            GenerateIn(int pTicks);
    void                            GenerateOut(int pTicks);
    void                            GenerateSmooth(int pTicks);

    bool                            IsComplete() { return (mTimerTick >= mTime); }
    
    void                            Finish();
    float                           Percent();

    float                           mStartX;
    float                           mTargetX;
    float                           mStartY;
    float                           mTargetY;
    float                           mStartScale;
    float                           mTargetScale;
    float                           mStartScaleX;
    float                           mTargetScaleX;
    float                           mStartScaleY;
    float                           mTargetScaleY;
    float                           mStartRotation;
    float                           mTargetRotation;
    float                           mStartAnchorX;
    float                           mTargetAnchorX;
    float                           mStartAnchorY;
    float                           mTargetAnchorY;

    int                             mTimerTick;
    int                             mTime;
    float                           *mPercent;
    FCanvas                         *mCanvas;

protected:
    void                            BaseInitialize();
};

#endif
