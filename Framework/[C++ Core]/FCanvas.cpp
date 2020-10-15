//
//  FCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/15/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "FCanvas.hpp"
#include "FAnimation.hpp"
#include "FHashMap.hpp"

FCanvas::FCanvas() {
    mX = 0.0f;
    mY = 0.0f;
    mWidth = 256.0f;
    mHeight = 256.0f;
    mWidth2 = 128.0;
    mHeight2 = 128.0;
    mKill = 0;
    mLayoutBubbleUpDepth = 1;
    
    mClipEnabled = false;
    mClipDisabled = false;
    mDidUpdate = false;
    mConsumesTouches = true;
    mRecievesOutsideTouches = false;
    mRecievesConsumedTouches = false;
    mExclusiveKeyDownCaptureWhenSelected = false;
    mExclusiveKeyUpCaptureWhenSelected = false;
    mEnabled = true;
    mHidden = false;
    mDrawManual = false;
    mTouchDownInside = false;
    mMouseOver = false;
    mTouchDown = false;
    mDeleteWhenKilled = true;
    mTouchCount = 0;
    mParent = 0;
    mColor.mRed = 1.0f;
    mColor.mGreen = 1.0f;
    mColor.mBlue = 1.0f;
    mColor.mAlpha = 0.0f;
    mTouchX = 0.0f;
    mTouchY = 0.0f;
    mMouseX = 0.0f;
    mMouseY = 0.0f;
    mWindow = 0;
    mMouseLeftDown = false;
    mMouseMiddleDown = false;
    mMouseRightDown = false;
    mMouseLeftDownInside = false;
    mMouseMiddleDownInside = false;
    mMouseRightDownInside = false;
    
    mUpdateID = 0;
    
    mLastKeyDown = -1;
    mLastKeyDownUpdateID = -1;
    
    mLastKeyUp = -1;
    mLastKeyUpUpdateID = -1;
    

    //SetTransformAnchor(gRand.GetFloat(), gRand.GetFloat());

    if (gRand.GetBool()) {
        //SetTransformRotation(gRand.GetFloat(-5.0f, 5.0f));
    }
}

FCanvas::~FCanvas() {
    
    //Log("Dealloc[%s :: %LX]\n", mName.c(), this);
    
    gNotify.Unregister(this);
    if (mWindow) {
        FWindow *aWindow = mWindow;
        mWindow = 0;
        aWindow->RegisterDealloc(this);
    }
}

void FCanvas::Kill() {
    mKill = 4;
    if (mWindow) {
        mWindow->RegisterKill(this);
    }
}

void FCanvas::Layout() { }
void FCanvas::LayoutTransform() { }

void FCanvas::Update() { }
void FCanvas::Draw() {
    if (mColor.mAlpha != 0.0f) {
        //
        Graphics::PipelineStateSetShape2DAlphaBlending();
        Graphics::SetColor(mColor);
        //
        Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
        Graphics::SetColor();
        //
    }
}

void FCanvas::MouseDown(float pX, float pY, int pButton) { }
void FCanvas::MouseMove(float pX, float pY) { }
void FCanvas::MouseUp(float pX, float pY, int pButton) { }
void FCanvas::MouseWheel(int pDirection) { }
void FCanvas::TouchDown(float pX, float pY, void *pData) { }
void FCanvas::TouchMove(float pX, float pY, void *pData) { }
void FCanvas::TouchUp(float pX, float pY, void *pData) { }
void FCanvas::TouchFlush() { }
void FCanvas::KeyDown(int pKey) { }
void FCanvas::KeyUp(int pKey) { }
void FCanvas::Notify(void *pSender, const char *pNotification) { }


void FCanvas::DrawManual() {
    if (mDidUpdate == true && mHidden == false && mKill == 0) {
        DrawTransform();
        
        if (mClipEnabled) {
            Graphics::ClipEnable();
            Graphics::Clip(mTransformAbsolute.mCornerX[0],
                           mTransformAbsolute.mCornerY[0],
                           mWidth * mTransformAbsolute.mScale * mTransformAbsolute.mScaleX,
                           mHeight * mTransformAbsolute.mScale * mTransformAbsolute.mScaleY);
        }
        
        Draw();
        EnumList(FCanvas, aCanvas, mChildren) {
            if (aCanvas->mDrawManual == false) {
                aCanvas->DrawManual();
            }
        }
        
        if (mClipEnabled || mClipDisabled) { Graphics::ClipDisable(); }
        
    }
}

void FCanvas::DrawTransform() {
    FMatrix aProjection = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -2048.0f, 2048.0f);
    FMatrix aModelView;
    
    float aX = mTransformAbsolute.mX;
    float aY = mTransformAbsolute.mY;
    if (aX != 0.0f || aY != 0.0f) {
        aModelView.Translate(aX, aY);
    }
    float aRotation = mTransformAbsolute.mRotation;
    if (aRotation != 0.0f) {
        aModelView.Rotate(aRotation);
    }
    float aScaleX = mTransformAbsolute.mScale * mTransformAbsolute.mScaleX;
    float aScaleY = mTransformAbsolute.mScale * mTransformAbsolute.mScaleY;
    float aScale = mTransformAbsolute.mScale;
    if (aScaleX != 1.0f || aScaleY != 1.0f || aScale != 1.0f) {
        aModelView.Scale(aScaleX, aScaleY, aScale);
    }
    float aAnchorX = mTransformAbsolute.mAnchorX;
    float aAnchorY = mTransformAbsolute.mAnchorY;
    if ((aAnchorX != 0.0f) || (aAnchorY != 0.0f)) {
        aModelView.Translate(aAnchorX * (-mWidth), aAnchorY * (-mHeight));
    }
    Graphics::MatrixProjectionSet(aProjection);
    Graphics::MatrixModelViewSet(aModelView);
}

void FCanvas::AddChild(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    pCanvas->mParent = this;
    pCanvas->mWindow = mWindow;
    mChildren.Add(pCanvas);
    if (mWindow) {
        mWindow->RegisterRealize(pCanvas);
        mWindow->RegisterChildrenDidUpdate(this);
    }
}

void FCanvas::AddChild(FCanvas &pCanvas) {
    pCanvas.mDeleteWhenKilled = false;
    AddChild(&pCanvas);
}

bool FCanvas::IsChild(FCanvas *pCanvas) {
    EnumList(FCanvas, aChild, mChildren) {
        if (aChild->mKill == 0) {
            if (aChild == pCanvas) {
                return true;
            }
        }
    }
    EnumList(FCanvas, aChild, mChildren) {
        if (aChild->mKill == 0) {
            if (aChild->IsChild(pCanvas)) {
                return true;
            }
        }
    }
    return false;
}

void FCanvas::BringChildToFront(FCanvas *pCanvas) {
    if (mChildren.Last() != pCanvas && mChildren.Exists(pCanvas)) {
        mChildren.MoveToLast(pCanvas);
        if (mWindow) { mWindow->RegisterChildrenDidUpdate(this); }
    }
}

void FCanvas::SendChildToBack(FCanvas *pCanvas) {
    if (mChildren.First() != pCanvas && mChildren.Exists(pCanvas)) {
        mChildren.MoveToFirst(pCanvas);
        if (mWindow) { mWindow->RegisterChildrenDidUpdate(this); }
    }
}

void FCanvas::BringChildForward(FCanvas *pCanvas) {
    if (mChildren.Last() != pCanvas && mChildren.Exists(pCanvas)) {
        mChildren.MoveObjectDown(pCanvas);
        if (mWindow) { mWindow->RegisterChildrenDidUpdate(this); }
    }
}

void FCanvas::SendChildBackward(FCanvas *pCanvas) {
    if (mChildren.First() != pCanvas && mChildren.Exists(pCanvas)) {
        mChildren.MoveObjectUp(pCanvas);
        if (mWindow) { mWindow->RegisterChildrenDidUpdate(this); }
    }
}

void FCanvas::SetFrame(float pX, float pY, float pWidth, float pHeight) {
    SetX(pX);
    SetY(pY);
    SetWidth(pWidth);
    SetHeight(pHeight);
}

void FCanvas::SetX(float pX) {
    float aDifference = mX - pX;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.01f) {
        mX = pX;
        FrameDidUpdate();
    }
}

void FCanvas::SetY(float pY) {
    float aDifference = mY - pY;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.01f) {
        mY = pY;
        FrameDidUpdate();
    }
}

void FCanvas::SetWidth(float pWidth) {
    float aDifference = mWidth - pWidth;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.01f) {
        mWidth = pWidth;
        mWidth2 = mWidth * 0.5f;
        FrameDidUpdate();
    }
}

void FCanvas::SetHeight(float pHeight) {
    float aDifference = mHeight - pHeight;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.01f) {
        mHeight = pHeight;
        mHeight2 = mHeight * 0.5f;
        FrameDidUpdate();
    }
}

void FCanvas::SetTransformTranslate(float pX, float pY) {
    SetTransformX(pX);
    SetTransformY(pY);
}

void FCanvas::SetTransformX(float pX) {
    float aDifference = mTransform.mX - pX;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.01f) {
        mTransform.mX = pX;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformY(float pY) {
    float aDifference = mTransform.mY - pY;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.01f) {
        mTransform.mY = pY;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformScale(float pScale) {
    float aDifference = mTransform.mScale - pScale;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mScale = pScale;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformScale(float pScaleX, float pScaleY) {
    SetTransformScaleX(pScaleX);
    SetTransformScaleY(pScaleY);
}

void FCanvas::SetTransformScaleX(float pScaleX) {
    float aDifference = mTransform.mScaleX - pScaleX;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mScaleX = pScaleX;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformScaleY(float pScaleY) {
    float aDifference = mTransform.mScaleY - pScaleY;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mScaleY = pScaleY;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformRotation(float pRotation) {
    float aDifference = mTransform.mRotation - pRotation;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.001f) {
        mTransform.mRotation = pRotation;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformAnchor(float pAnchorX, float pAnchorY) {
    SetTransformAnchorX(pAnchorX);
    SetTransformAnchorY(pAnchorY);
}

void FCanvas::SetTransformAnchorX(float pAnchorX) {
    float aDifference = mTransform.mAnchorX - pAnchorX;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mAnchorX = pAnchorX;
        TransformDidUpdate();
    }
}

void FCanvas::SetTransformAnchorY(float pAnchorY) {
    float aDifference = mTransform.mAnchorY - pAnchorY;
    if (aDifference < 0.0) aDifference = -aDifference;
    if (aDifference > 0.0001f) {
        mTransform.mAnchorY = pAnchorY;
        TransformDidUpdate();
    }
}

void FCanvas::Activate() {
    if (mHidden == true || mEnabled == false) {
        mHidden = false;
        mEnabled = true;
        FrameDidUpdate();
    }
}
void FCanvas::Deactivate() {
    if (mHidden == false || mEnabled == true) {
        mHidden = true;
        mEnabled = false;
        FrameDidUpdate();
    }
}

void FCanvas::ConvertPoint(float &pX, float &pY, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    if (pFromCanvas) {
        pFromCanvas->mTransformAbsolute.Untransform(pX, pY, pFromCanvas->mWidth, pFromCanvas->mHeight);
    }
    if (pToCanvas) {
        pToCanvas->mTransformAbsolute.Transform(pX, pY, pToCanvas->mWidth, pToCanvas->mHeight);
    }
}

FVec2 FCanvas::Convert(float pX, float pY, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    FVec2 aResult;
    aResult.mX = pX; aResult.mY = pY;
    ConvertPoint(aResult.mX, aResult.mY, pFromCanvas, pToCanvas);
    return aResult;
}

float FCanvas::ConvertScale(float pScale, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    return 0.0f;
}

float FCanvas::ConvertRotation(float pDegrees, FCanvas *pFromCanvas, FCanvas *pToCanvas) {
    return 0.0f;
}

void FCanvas::TransformDidUpdate() {
    if (mWindow) {
        mWindow->RegisterTransformDidUpdate(this);
    }
}

void FCanvas::FrameDidUpdate() {
    if (mWindow) {
        mWindow->RegisterFrameDidUpdate(this);
    }
}

void FCanvas::ComputeAbsoluteTransformation() {
    if (mParent) {
        mTransformAbsolute.ApplyAbsoluteTransformation(&mParent->mTransformAbsolute, mParent->mX, mParent->mY, mParent->mWidth, mParent->mHeight, &mTransform, mX, mY, mWidth, mHeight);
    } else {
        mTransformAbsolute.ApplyAbsoluteTransformation(&mTransform, mX, mY, mWidth, mHeight);
    }
    EnumList(FCanvas, aCanvas, mChildren) {
        aCanvas->ComputeAbsoluteTransformation();
    }
}

void FCanvas::BaseNotify(void *pSender, const char *pNotification) {
    Notify(pSender, pNotification);
}

void FCanvas::BaseLayout() {
    Layout();
}

void FCanvas::BaseLayoutTransform() {
    LayoutTransform();
    EnumList(FCanvas, aCanvas, mChildren) {
        aCanvas->BaseLayoutTransform();
    }
}


void FCanvas::BaseUpdate() {
    mDidUpdate = true;
    
    Update();

    mProcessChildren.RemoveAll();
    mProcessChildren.Add(mChildren);
    EnumList(FCanvas, aCanvas, mProcessChildren) {
        if (aCanvas->mKill == 0) {
            aCanvas->BaseUpdate();
        }
    }
    
    mUpdateID++;
    if (mUpdateID > 0x7FFFFFF) {
        mUpdateID = 0;
    }
}

void FCanvas::BaseDraw() {
    if (mDidUpdate == true && mDrawManual == false && mHidden == false && mKill == 0) {
        DrawTransform();
        
        if (mClipEnabled) {
            Graphics::ClipEnable();
            Graphics::Clip(mTransformAbsolute.mCornerX[0],
                           mTransformAbsolute.mCornerY[0],
                           mWidth * mTransformAbsolute.mScale * mTransformAbsolute.mScaleX,
                           mHeight * mTransformAbsolute.mScale * mTransformAbsolute.mScaleY);
        }
        if (mClipDisabled) {
            Graphics::ClipDisable();
        }
        
        Draw();
        
        mProcessChildren.RemoveAll();
        mProcessChildren.Add(mChildren);
        
        EnumList(FCanvas, aCanvas, mProcessChildren) { aCanvas->BaseDraw(); }
        
        if (mClipEnabled || mClipDisabled) { Graphics::ClipDisable(); }
        
        /*
        if (mMouseOver) {
        Graphics::ClipDisable();
        Graphics::MatrixModelViewReset();
        Graphics::MatrixProjectionReset();
        //Graphics::Ortho2D(0, gDeviceWidth, gDeviceHeight, 0); //, -4096.0f, 4096.0f);
        
            FMatrix aProj = FMatrixCreateOrtho(0.0f, gDeviceWidth, gDeviceHeight, 0.0f, -1024.0f, 1024.0f);
            Graphics::MatrixProjectionSet(aProj);
            Graphics::MatrixModelViewReset();
            Graphics::PipelineStateSetShape2DAlphaBlending();
            
            
        for (int i=0;i<4;i++) {

            Graphics::SetColor(0.0f, 0.0f, 0.0f, 1.0f);
            Graphics::DrawPoint(mTransformAbsolute.mCornerX[i], mTransformAbsolute.mCornerY[i], 20.0f);
            Graphics::SetColorSwatch(i);
            Graphics::DrawPoint(mTransformAbsolute.mCornerX[i], mTransformAbsolute.mCornerY[i], 14.0f);
        }
         
        Graphics::SetColor(0.75f, 0.65f, 0.125f, 0.90f);
         
        Graphics::DrawLine(mTransformAbsolute.mCornerX[0],
                           mTransformAbsolute.mCornerY[0],
                           mTransformAbsolute.mCornerX[1],
                           mTransformAbsolute.mCornerY[1], 5.0);
         
        Graphics::DrawLine(mTransformAbsolute.mCornerX[1],
                           mTransformAbsolute.mCornerY[1],
                           mTransformAbsolute.mCornerX[2],
                           mTransformAbsolute.mCornerY[2], 5.0);
         
        Graphics::DrawLine(mTransformAbsolute.mCornerX[2],
                           mTransformAbsolute.mCornerY[2],
                           mTransformAbsolute.mCornerX[3],
                           mTransformAbsolute.mCornerY[3], 5.0);
         
        Graphics::DrawLine(mTransformAbsolute.mCornerX[3],
                           mTransformAbsolute.mCornerY[3],
                           mTransformAbsolute.mCornerX[0],
                           mTransformAbsolute.mCornerY[0], 5.0);
        }
        */
    }
}

FCanvas *FCanvas::BaseMouseDown(float pX, float pY, float pOriginalX, float pOriginalY, int pButton, bool pOutsideParent, bool &pConsumed) {
    FCanvas *aResult = 0;
    FCanvas *aCollider = 0;
    if (mKill == 0 && mEnabled == true) {
        bool aContainsPoint = false;
        if ((pConsumed == true) && (mRecievesConsumedTouches == false)) {
            aContainsPoint = false;
        } else {
            if (pOutsideParent) {
                aContainsPoint = false;
            } else {
                aContainsPoint = mTransformAbsolute.ContainsPoint(pX, pY);
                if (aContainsPoint == false) {
                    pOutsideParent = true;
                }
            }
        }
        mProcessChildren.RemoveAll();
        mProcessChildren.Add(mChildren);
        EnumListReverse(FCanvas, aChild, mProcessChildren) {
            aCollider = aChild->BaseMouseDown(pX, pY, pOriginalX, pOriginalY, pButton, pOutsideParent, pConsumed);
            if (aCollider) {
                if (aCollider->mConsumesTouches) {
                    pConsumed = true;
                    if(aResult == 0) {
                        aResult = aCollider;
                    }
                    if ((mRecievesOutsideTouches == false) && (mRecievesConsumedTouches == false)) {
                        aContainsPoint = false;
                    }
                }
            }
        }
        if ((mRecievesConsumedTouches == true) || (pConsumed == false)) {
            if ((aContainsPoint == true) || (mRecievesOutsideTouches == true)) {
                if (aContainsPoint == true && aResult == 0) {
                    aResult = this;
                }
                if (pButton == MOUSE_BUTTON_LEFT) {
                    mMouseLeftDown = true;
                    mMouseLeftDownInside = aContainsPoint;
                } else if (pButton == MOUSE_BUTTON_MIDDLE) {
                    mMouseMiddleDown = true;
                    mMouseMiddleDownInside = aContainsPoint;
                } else if (pButton == MOUSE_BUTTON_RIGHT) {
                    mMouseRightDown = true;
                    mMouseRightDownInside = aContainsPoint;
                }
                mMouseX = pX;
                mMouseY = pY;
                mTransformAbsolute.Transform(mMouseX, mMouseY, mWidth, mHeight);
                mTouchDown = true;
                mMouseOver = true;
                MouseDown(mMouseX, mMouseY, pButton);
            }
        }
    } else {
        BaseTouchFlush();
    }
    return aResult;
}

bool FCanvas::BaseMouseMove(float pX, float pY, float pOriginalX, float pOriginalY, bool pOutsideParent) {
    bool aResult = false;
    if (mKill == 0 && mEnabled == true) {
        bool aContainsPoint = false;
        if (pOutsideParent) {
            aContainsPoint = false;
        } else {
            aContainsPoint = mTransformAbsolute.ContainsPoint(pX, pY);
            if (aContainsPoint == false) {
                pOutsideParent = true;
            }
        }
        bool aChildContainsMouse = false;
        mProcessChildren.RemoveAll();
        mProcessChildren.Add(mChildren);
        EnumListReverse (FCanvas, aChild, mProcessChildren) {
            if (aChildContainsMouse == false) {
                if (aChild->BaseMouseMove(pX, pY, pOriginalX, pOriginalY, pOutsideParent)) {
                    aChildContainsMouse = true;
                }
            }
        }
        if (aChildContainsMouse) {
            aResult = true;
        }
        if (aContainsPoint && !aChildContainsMouse) {
            aResult = true;
            mMouseOver = true;
            mMouseLeftDownInside = mMouseLeftDown;
            mMouseMiddleDownInside = mMouseMiddleDown;
            mMouseRightDownInside = mMouseRightDown;
        } else {
            mMouseOver = false;
            mMouseLeftDownInside = false;
            mMouseMiddleDownInside = false;
            mMouseRightDownInside = false;
        }
        bool aMouseDown = mMouseLeftDown || mMouseMiddleDown || mMouseRightDown;
        if ((!aChildContainsMouse && aContainsPoint) || aMouseDown) {
            mMouseX = pX;
            mMouseY = pY;
            mTransformAbsolute.Transform(mMouseX, mMouseY, mWidth, mHeight);
            MouseMove(mMouseX, mMouseY);
        }
    } else {
        BaseTouchFlush();
    }
    return aResult;
}

void FCanvas::BaseMouseUp(float pX, float pY, float pOriginalX, float pOriginalY, int pButton, bool pOutsideParent) {
    bool aContainsMouse = false;
    if (pButton == MOUSE_BUTTON_LEFT) {
        aContainsMouse = mMouseLeftDown;
        mMouseLeftDown = false;
        mMouseLeftDownInside = false;
    } else if (pButton == MOUSE_BUTTON_MIDDLE) {
        aContainsMouse = mMouseMiddleDown;
        mMouseMiddleDown = false;
        mMouseMiddleDownInside = false;
    } else if (pButton == MOUSE_BUTTON_RIGHT) {
        aContainsMouse = mMouseRightDown;
        mMouseRightDown = false;
        mMouseRightDownInside = false;
    }

    if (mKill == 0 && mEnabled == true) {
        bool aContainsPoint = false;
        if (pOutsideParent) {
            aContainsPoint = false;
        } else {
            aContainsPoint = mTransformAbsolute.ContainsPoint(pX, pY);
            if (aContainsPoint == false) {
                pOutsideParent = true;
            }
        }
        mProcessChildren.RemoveAll();
        mProcessChildren.Add(mChildren);
        EnumListReverse (FCanvas, aChild, mProcessChildren) {
            aChild->BaseMouseUp(pX, pY, pOriginalX, pOriginalY, pButton, pOutsideParent);
        }
        if (aContainsMouse) {
            mMouseX = pX;
            mMouseY = pY;
            mTransformAbsolute.Transform(mMouseX, mMouseY, mWidth, mHeight);
            MouseUp(mMouseX, mMouseY, pButton);
        }
    } else {
        BaseTouchFlush();
    }
}

void FCanvas::BaseMouseWheel(int pDirection) {
    MouseWheel(pDirection);
    mProcessChildren.RemoveAll();
    mProcessChildren.Add(mChildren);
    EnumList(FCanvas, aChild, mProcessChildren) {
        aChild->BaseMouseWheel(pDirection);
    }
}

FCanvas *FCanvas::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed) {
    FCanvas *aResult = 0;
    FCanvas *aCollider = 0;
    if ((mKill == 0) && (mEnabled == true)) {
        bool aContainsPoint = false;
        if ((pConsumed == true) && (mRecievesConsumedTouches == false)) {
            aContainsPoint = false;
        } else {
            if (pOutsideParent) {
                aContainsPoint = false;
            } else {
                aContainsPoint = mTransformAbsolute.ContainsPoint(pX, pY);
                if (aContainsPoint == false) {
                    pOutsideParent = true;
                }
            }
        }

        mProcessChildren.RemoveAll();
        mProcessChildren.Add(mChildren);
        EnumListReverse(FCanvas, aChild, mProcessChildren) {
            aCollider = aChild->BaseTouchDown(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent, pConsumed);
            if (aCollider) {
                if (aCollider->mConsumesTouches) {
                    pConsumed = true;
                    if(aResult == 0) {
                        aResult = aCollider;
                    }
                    if ((mRecievesOutsideTouches == false) && (mRecievesConsumedTouches == false)) {
                        aContainsPoint = false;
                    }
                }
            }
        }

        if ((mRecievesConsumedTouches == true) || (pConsumed == false)) {
            if ((aContainsPoint == true) || (mRecievesOutsideTouches == true)) {
                mTouchDown = true;
                if (mTouchCount < CANVAS_TRACKED_TOUCH_COUNT) {
                    mTouchData[mTouchCount] = pData;
                    if (aContainsPoint == true) {
                        if (aResult == 0) {
                            aResult = this;
                        }
                        mTouchInside[mTouchCount] = true;
                        mTouchDownInside = true;
                    } else {
                        mTouchInside[mTouchCount] = false;
                        mTouchDown = true;
                        bool aAnyTouchesInside = false;
                        for (int i=0;i<mTouchCount;i++) {
                            if(mTouchInside[i] == true)aAnyTouchesInside = true;
                        }
                        mTouchDownInside = aAnyTouchesInside;
                    }

                    mTouchCount++;

                    mTouchX = pX;
                    mTouchY = pY;
                    mTransformAbsolute.Transform(mTouchX, mTouchY, mWidth, mHeight);
                    mTouchDown = true;
                    TouchDown(mTouchX, mTouchY, pData);
                }
            }
        }
    } else {
        BaseTouchFlush();
    }
    return aResult;
}

void FCanvas::BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {
    if (mKill == 0 && mEnabled == true) {
        int aTouchIndex = -1;
        for (int i=0;i<mTouchCount;i++) {
            if (mTouchData[i] == pData) {
                aTouchIndex = i;
            }
        }
        bool aContainsPoint = false;
        if (pOutsideParent) {
            aContainsPoint = false;
        } else {
            aContainsPoint = mTransformAbsolute.ContainsPoint(pX, pY);
            if (aContainsPoint == false) {
                pOutsideParent = true;
            }
        }

        mProcessChildren.RemoveAll();
        mProcessChildren.Add(mChildren);
        EnumListReverse (FCanvas, aChild, mProcessChildren) {
            aChild->BaseTouchMove(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);
        }
        if (aTouchIndex >= 0) {
            if (aContainsPoint) {
                mTouchInside[aTouchIndex] = true;
                mTouchDownInside = true;
            } else {
                mTouchInside[aTouchIndex] = false;
                bool aAnyTouchesInside = false;
                for (int i=0;i<mTouchCount;i++) {
                    if(mTouchInside[i] == true) { aAnyTouchesInside = true; }
                }
                mTouchDownInside = aAnyTouchesInside;
            }
            mTouchX = pX;
            mTouchY = pY;
            mTransformAbsolute.Transform(mTouchX, mTouchY, mWidth, mHeight);
            TouchMove(mTouchX, mTouchY, pData);
        }
    } else {
        BaseTouchFlush();
    }
}

void FCanvas::BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {
    int aTouchIndex = -1;
    for (int i=0;i<mTouchCount;i++) {
        if (mTouchData[i] == pData) {
            aTouchIndex = i;
        }
    }
    if (aTouchIndex >= 0) {
        for (int i=aTouchIndex;i<(mTouchCount - 1);i++) {
            mTouchData[i] = mTouchData[i + 1];
            mTouchInside[i] = mTouchInside[i + 1];
        }
        mTouchCount--;
    }
    if (mKill == 0 && mEnabled == true) {
        bool aContainsPoint = false;
        if (pOutsideParent) {
            aContainsPoint = false;
        } else {
            aContainsPoint = mTransformAbsolute.ContainsPoint(pX, pY);
            if (aContainsPoint == false) {
                pOutsideParent = true;
            }
        }
        mProcessChildren.RemoveAll();
        mProcessChildren.Add(mChildren);
        EnumListReverse (FCanvas, aChild, mProcessChildren) {
            aChild->BaseTouchUp(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);
        }
        if (mTouchCount <= 0) {
            mTouchDown = false;
            mTouchDownInside = false;
        } else {
            bool aAnyTouchesInside = false;
            for (int i=0;i<mTouchCount;i++) {
                if (mTouchInside[i] == true) { aAnyTouchesInside = true; }
            }
            mTouchDownInside = aAnyTouchesInside;
        }

        if (aTouchIndex >= 0) {
            mTouchX = pX;
            mTouchY = pY;
            mTransformAbsolute.Transform(mTouchX, mTouchY, mWidth, mHeight);
            TouchUp(mTouchX, mTouchY, pData);
        }
    } else {
        BaseTouchFlush();
    }
}

void FCanvas::BaseTouchFlush() {
    mTouchDown = false;
    mTouchDownInside = false;
    mTouchCount = 0;
    mMouseOver = false;
    TouchFlush();
    mMouseLeftDown = false;
    mMouseMiddleDown = false;
    mMouseRightDown = false;
    mMouseLeftDownInside = false;
    mMouseMiddleDownInside = false;
    mMouseRightDownInside = false;
    mProcessChildren.RemoveAll();
    mProcessChildren.Add(mChildren);
    EnumList(FCanvas, aChild, mProcessChildren) {
        aChild->BaseTouchFlush();
    }
}

void FCanvas::BaseKeyDown(int pKey) {
    
    if ((mLastKeyDown == pKey) && (mLastKeyDownUpdateID == mUpdateID)) {
        Log("[[TRAPPED KEY DOWN, %d:%d]]\n", pKey, mUpdateID);
        return;
    }
    
    mLastKeyDown = pKey;
    mLastKeyUpUpdateID = mUpdateID;

    
    KeyDown(pKey);
    
    if (mWindow != NULL && mWindow->mSelectedCanvas == this && mExclusiveKeyDownCaptureWhenSelected == true) {
        return;
    }
    
    mProcessChildren.RemoveAll();
    mProcessChildren.Add(mChildren);
    EnumList(FCanvas, aChild, mProcessChildren) {
        aChild->BaseKeyDown(pKey);
    }
}

void FCanvas::BaseKeyUp(int pKey) {
    KeyUp(pKey);
    
    if ((mLastKeyUp == pKey) && (mLastKeyUpUpdateID == mUpdateID)) {
        Log("[[TRAPPED KEY UP, %d:%d]]\n", pKey, mUpdateID);
        return;
    }
    
    mLastKeyUp = pKey;
    mLastKeyUpUpdateID = mUpdateID;
    
    if (mWindow != NULL && mWindow->mSelectedCanvas == this && mExclusiveKeyUpCaptureWhenSelected == true) {
        return;
    }
    
    mProcessChildren.RemoveAll();
    mProcessChildren.Add(mChildren);
    EnumList(FCanvas, aChild, mProcessChildren) {
        aChild->BaseKeyUp(pKey);
    }
}

FCanvasBucketNode::FCanvasBucketNode() {
    mCanvas = 0;
    mTableNext = 0;
    mListPrev = 0;
    mListNext = 0;
    mTableIndex = -1;
}

FCanvasBucketNode::~FCanvasBucketNode() { }

FCanvasBucket::FCanvasBucket() {
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
    mListHead = 0;
    mListTail = 0;
}

FCanvasBucket::~FCanvasBucket() {
    FCanvasBucketNode *aNode = 0;
    FCanvasBucketNode *aNext = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            delete aNode;
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;

    // We will assume that something outside
    // is deleting the canvases for real.
    mQueue.RemoveAll();

    mListHead = 0;
    mListTail = 0;
}

void FCanvasBucket::RemoveAll() {
    FCanvasBucketNode *aNode = mListHead;
    while (aNode) {
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = 0;
        aNode = aNode->mListNext;
    }
    mListHead = 0;
    mListTail = 0;
    mTableCount = 0;
}

void FCanvasBucket::Add(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    FCanvasBucketNode *aNode = 0;
    FCanvasBucketNode *aHold = 0;
    unsigned int aHashBase = FHashMap::Hash(pCanvas);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mCanvas == pCanvas) {
                return;
            }
            aNode = aNode->mTableNext;
        }
        if (mTableCount >= (mTableSize / 2)) {
            int aNewSize = FHashMap::IncreaseTableSize(mTableCount);
            SetTableSize(aNewSize);
            aHash = (aHashBase % mTableSize);
        }
    } else {
        SetTableSize(7);
        aHash = (aHashBase % mTableSize);
    }

    FCanvasBucketNode *aNew = (FCanvasBucketNode *)mQueue.PopLast();
    if (aNew == 0) {
        aNew = new FCanvasBucketNode();
    }
    aNew->mCanvas = pCanvas;
    aNew->mTableNext = 0;
    aNew->mTableIndex = aHash;
    if (mTable[aHash]) {
        aNode = mTable[aHash];
        while (aNode) {
            aHold = aNode;
            aNode = aNode->mTableNext;
        }
        aHold->mTableNext = aNew;
    } else {
        mTable[aHash] = aNew;
    }
    ListAdd(aNew);
    mTableCount += 1;
}

void FCanvasBucket::Remove(FCanvas *pCanvas) {
    if (mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pCanvas) % mTableSize);
        FCanvasBucketNode *aPreviousNode = 0;
        FCanvasBucketNode *aNode = mTable[aHash];
        while (aNode) {
            if(aNode->mCanvas == pCanvas) {
                if (aPreviousNode) {
                    aPreviousNode->mTableNext = aNode->mTableNext;
                } else {
                    mTable[aHash] = aNode->mTableNext;
                }
                mQueue.Add(aNode);
                ListRemove(aNode);
                mTableCount -= 1;
                return;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
}

void FCanvasBucket::ListAdd(FCanvasBucketNode *pNode) {
    pNode->mListNext = NULL;
    if (mListHead == NULL) {
        mListHead = pNode;
        mListTail = pNode;
        pNode->mListPrev = NULL;
    } else {
        pNode->mListPrev = mListTail;
        mListTail->mListNext = pNode;
        mListTail = pNode;
    }
}

void FCanvasBucket::ListRemove(FCanvasBucketNode *pNode) {
    if (pNode == mListHead) {
        if (mListHead->mListNext) {
            mListHead = mListHead->mListNext;
            mListHead->mListPrev = NULL;
        } else {
            mListTail = NULL;
            mListHead = NULL;
        }
    } else if(pNode == mListTail) {
        mListTail = mListTail->mListPrev;
        mListTail->mListNext = NULL;
    } else {
        pNode->mListPrev->mListNext = pNode->mListNext;
        pNode->mListNext->mListPrev = pNode->mListPrev;
    }
    pNode->mListPrev = NULL;
    pNode->mListNext = NULL;
}

bool FCanvasBucket::IsEmpty() {
    return mTableCount <= 0;
}

bool FCanvasBucket::Exists(FCanvas *pCanvas) {
    if(mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pCanvas) % mTableSize);
        FCanvasBucketNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mCanvas == pCanvas) {
                return true;
            }
            aNode = aNode->mTableNext;
        }
    }
    return false;
}

bool FCanvasBucket::ParentExists(FCanvas *pCanvas) {
    FCanvas *aCanvas = pCanvas->mParent;
    while (aCanvas != 0) {
        if (Exists(aCanvas)) {
            return true;
        }
        aCanvas = aCanvas->mParent;
    }
    return false;
}

void FCanvasBucket::RemoveAllChildren(FCanvas *pCanvas){
    EnumList(FCanvas, aChild, pCanvas->mChildren) {
        Remove(aChild);
        RemoveAllChildren(aChild);
    }
}

void FCanvasBucket::AddCanvasesToList(FList *pList) {
    FCanvasBucketNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mCanvas);
        aNode = aNode->mListNext;
    }
}

void FCanvasBucket::AddCanvasesToListAndRemoveAll(FList *pList) {
    FCanvasBucketNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mCanvas);
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = 0;
        aNode = aNode->mListNext;
    }
    mListHead = 0;
    mListTail = 0;
    mTableCount = 0;
}

void FCanvasBucket::AddCanvasesAndChildrenRecursivelyToListAndRemoveAll(FList *pList) {
    AddCanvasesToListAndRemoveAll(pList);
    int aIndex = 0;
    while (aIndex < pList->mCount) {
        FCanvas *aCanvas = (FCanvas *)(pList->mData[aIndex]);
        for (int aChildIndex = 0;aChildIndex<aCanvas->mChildren.mCount;aChildIndex++) {
            pList->Add(aCanvas->mChildren.mData[aChildIndex]);
        }
        aIndex += 1;
    }
}

void FCanvasBucket::SetTableSize(int pSize) {
    FCanvasBucketNode *aCheck = 0;
    FCanvasBucketNode *aNext = 0;
    FCanvasBucketNode *aNode = 0;
    int aNewSize = pSize;
    FCanvasBucketNode **aTableNew = new FCanvasBucketNode*[aNewSize];
    for(int i=0;i<aNewSize;i++) {
        aTableNew[i] = 0;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            aNode->mTableNext = 0;
            aHash = FHashMap::Hash(aNode->mCanvas) % aNewSize;

            aNode->mTableIndex = aHash;
            if(aTableNew[aHash] == 0) {
                aTableNew[aHash] = aNode;
            } else {
                aCheck = aTableNew[aHash];
                while (aCheck->mTableNext) {
                    aCheck = aCheck->mTableNext;
                }
                aCheck->mTableNext = aNode;
            }
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = aTableNew;
    mTableSize = aNewSize;
}

FCanvasAnimation::FCanvasAnimation() {
    BaseInitialize();
    mCanvas = 0;
}

FCanvasAnimation::FCanvasAnimation(FCanvas *pCanvas) {
    BaseInitialize();
    SetUp(pCanvas);
}

FCanvasAnimation::~FCanvasAnimation() {
    delete [] mPercent;
    mPercent = 0;
}

void FCanvasAnimation::BaseInitialize() {
    mStartX = 0.0f;
    mTargetX = 0.0f;
    mStartY = 0.0f;
    mTargetY = 0.0f;
    mStartScale = 1.0f;
    mTargetScale = 1.0f;
    mStartScaleX = 1.0f;
    mTargetScaleX = 1.0f;
    mStartScaleY = 1.0f;
    mTargetScaleY = 1.0f;
    mStartRotation = 0.0f;
    mTargetRotation = 0.0f;
    mStartAnchorX = 0.0f;
    mTargetAnchorX = 0.0f;
    mStartAnchorY = 0.0f;
    mTargetAnchorY = 0.0f;
    mTimerTick = 0;
    mTime = 0;
    mPercent = 0;
}

bool FCanvasAnimation::Update() {
    bool aComplete = false;
    float aAnimationPercent = 0.0f;

    mTimerTick++;
    if (mTime > 0) {
        if (mTimerTick >= mTime) {
            aAnimationPercent = 1.0f;
            aComplete = true;
        } else {
            aAnimationPercent = mPercent[mTimerTick];
        }
    } else {
        aComplete = true;
    }

    if (mCanvas) {
        if (aComplete) {
            Finish();
        } else {
            mCanvas->SetTransformX(mStartX + (mTargetX - mStartX) * aAnimationPercent);
            mCanvas->SetTransformY(mStartY + (mTargetY - mStartY) * aAnimationPercent);
            mCanvas->SetTransformScale(mStartScale + (mTargetScale - mStartScale) * aAnimationPercent);
            mCanvas->SetTransformScaleX(mStartScaleX + (mTargetScaleX - mStartScaleX) * aAnimationPercent);
            mCanvas->SetTransformScaleY(mStartScaleY + (mTargetScaleY - mStartScaleY) * aAnimationPercent);
            mCanvas->SetTransformRotation(mStartRotation + (mTargetRotation - mStartRotation) * aAnimationPercent);
            mCanvas->SetTransformAnchorX(mStartAnchorX + (mTargetAnchorX - mStartAnchorX) * aAnimationPercent);
            mCanvas->SetTransformAnchorY(mStartAnchorY + (mTargetAnchorY - mStartAnchorY) * aAnimationPercent);
        }
    }
    return aComplete;
}

void FCanvasAnimation::SetUp(FCanvas *pCanvas) {
    mCanvas = pCanvas;
    if (pCanvas) {
        mStartX = pCanvas->GetTransformX();
        mStartY = pCanvas->GetTransformY();
        mStartRotation = pCanvas->GetTransformRotation();
        mStartScale = pCanvas->GetTransformScale();
        mStartScaleX = pCanvas->GetTransformScaleX();
        mStartScaleY = pCanvas->GetTransformScaleY();
        mStartAnchorX = pCanvas->GetTransformAnchorX();
        mStartAnchorY = pCanvas->GetTransformAnchorY();

        mTargetX = mStartX;
        mTargetY = mStartY;
        mTargetRotation = mStartRotation;
        mTargetScale = mStartScale;
        mTargetScaleX = mStartScaleX;
        mTargetScaleY = mStartScaleY;
        mTargetAnchorX = mStartAnchorX;
        mTargetAnchorY = mStartAnchorY;
    }
}

float FCanvasAnimation::Percent() {
    float aResult = 0;
    if ((mTimerTick >= 0) && (mTime > 0)) {
        if (mPercent != 0) {
            if (mTimerTick >= mTime) {
                aResult = 1.0f;
            } else {
                aResult = mPercent[mTimerTick];
            }
        } else {
            aResult = ((float)mTimerTick) / ((float)mTime);
        }
    }

    if(aResult > 1.0f)aResult = 1.0f;
    if(aResult < 0.0f)aResult = 0.0f;

    return aResult;
}

void FCanvasAnimation::Generate(int pFunction, int pTicks) {
    mTimerTick = 0;
    mTime = pTicks;
    if (mTime < 1)mTime = 1;
    if (mPercent) {
        delete [] mPercent;
        mPercent = 0;
    }
    mPercent = new float[mTime];
    float aPercent = 0.0f;
    for (int i=0;i<mTime;i++) {
        aPercent = ((float)i) / ((float)mTime);
        mPercent[i] = aPercent;
    }
    for (int i=0;i<mTime;i++) {
        mPercent[i] = FAnimation::ApplyFunction(pFunction, mPercent[i]);
    }
}

void FCanvasAnimation::GenerateIn(int pTicks) {
    Generate(ANIMATION_TYPE_EASE_OUT_CIRC, pTicks);
}

void FCanvasAnimation::GenerateOut(int pTicks) {
    Generate(ANIMATION_TYPE_EASE_OUT_CIRC, pTicks);
}

void FCanvasAnimation::GenerateSmooth(int pTicks) {
    Generate(ANIMATION_TYPE_EASE_OUT_IN_SIN, pTicks);
}

void FCanvasAnimation::Finish() {
    if (mCanvas) {
        mCanvas->SetTransformX(mTargetX);
        mCanvas->SetTransformY(mTargetY);
        mCanvas->SetTransformScale(mTargetScale);
        mCanvas->SetTransformScaleX(mTargetScaleX);
        mCanvas->SetTransformScaleY(mTargetScaleY);
        mCanvas->SetTransformRotation(mTargetRotation);
    }
}


FCanvasTransform::FCanvasTransform() {
    mX = 0.0f;
    mY = 0.0f;
    mScale = 1.0f;
    mScaleX = 1.0f;
    mScaleY = 1.0f;
    mRotation = 0.0f;
    mAnchorX = 0.0f;
    mAnchorY = 0.0f;
}

FCanvasTransform::~FCanvasTransform() { }

FCanvasAbsoluteTransform::FCanvasAbsoluteTransform() {
    mX = 0.0f;
    mY = 0.0f;
    mScale = 1.0f;
    mScaleX = 1.0f;
    mScaleY = 1.0f;
    mRotation = 0.0f;
    mAnchorX = 0.0f;
    mAnchorY = 0.0f;
    for (int i=0;i<4;i++) {
        mCornerX[i] = 0.0f;
        mCornerY[i] = 0.0f;
    }
}

FCanvasAbsoluteTransform::~FCanvasAbsoluteTransform() { }

void FCanvasAbsoluteTransform::ApplyAbsoluteTransformation(FCanvasAbsoluteTransform *pParentTransform, float pParentX, float pParentY, float pParentWidth, float pParentHeight, FCanvasTransform *pTransform, float pX, float pY, float pWidth, float pHeight) {
    mAnchorX = pTransform->mAnchorX;
    mAnchorY = pTransform->mAnchorY;
    float aAnchorWidth = mAnchorX * pWidth;
    float aAnchorHeight = mAnchorY * pHeight;
    float aAnchorX = aAnchorWidth * pTransform->mScale * pTransform->mScaleX;
    float aAnchorY = aAnchorHeight * pTransform->mScale * pTransform->mScaleY;
    mRotation = pTransform->mRotation;
    mScale = pTransform->mScale;
    mScaleX = pTransform->mScaleX;
    mScaleY = pTransform->mScaleY;
    float aParentX = pParentTransform->mX;
    float aParentY = pParentTransform->mY;
    float aParentScaleX = pParentTransform->mScale * pParentTransform->mScaleX;
    float aParentScaleY = pParentTransform->mScale * pParentTransform->mScaleY;
    mScale *= pParentTransform->mScale;
    mScaleX *= pParentTransform->mScaleX;
    mScaleY *= pParentTransform->mScaleY;
    if ((pParentTransform->mAnchorX != 0.0f) || (pParentTransform->mAnchorY != 0.0f)) {
        float aParentShiftX = (pParentTransform->mAnchorX * pParentWidth) * aParentScaleX;
        float aParentShiftY = (pParentTransform->mAnchorY * pParentHeight) * aParentScaleY;
        if (pParentTransform->mRotation != 0.0f) {
            float aDist = aParentShiftX * aParentShiftX + aParentShiftY * aParentShiftY;
            float aSwivel = 180.0f - FaceTarget(-aParentShiftX, -aParentShiftY);
            if (aDist > SQRT_EPSILON) { aDist = sqrtf(aDist); }
            aSwivel -= pParentTransform->mRotation;
            float aDirX = Sin(aSwivel);
            float aDirY = Cos(aSwivel);
            aParentShiftX = aDirX * aDist;
            aParentShiftY = aDirY * aDist;
        }
        aParentX -= aParentShiftX;
        aParentY -= aParentShiftY;
    }
    mX = ((pX + pTransform->mX + aAnchorX + ((aAnchorWidth) - (aAnchorX))) * (aParentScaleX));
    mY = ((pY + pTransform->mY + aAnchorY + ((aAnchorHeight) - (aAnchorY))) * (aParentScaleY));
    if (pParentTransform->mRotation != 0) {
        float aPivotRotation = FaceTarget(mX, mY);
        float aDist = mX * mX + mY * mY;
        if(aDist > SQRT_EPSILON) { aDist = sqrtf(aDist); }
        aPivotRotation += pParentTransform->mRotation;
        float aDirX = Sin(-aPivotRotation);
        float aDirY = Cos(-aPivotRotation);
        mX = aDirX * (aDist) + aParentX;
        mY = aDirY * (aDist) + aParentY;
    } else {
        mX += aParentX;
        mY += aParentY;
    }
    mRotation += pParentTransform->mRotation;
    float aScaleX = mScale * mScaleX;
    float aScaleY = mScale * mScaleY;
    float aWidth = pWidth * (aScaleX);
    float aHeight = pHeight * (aScaleY);
    float aCornerStartX = mX;
    float aCornerStartY = mY;
    if (mRotation != 0) {
        float aDirX = Sin(-mRotation);
        float aDirY = Cos(-mRotation);
        float aNormalX = (aDirY);
        float aNormalY = (-aDirX);
        float aHeightShiftX = (aHeight * aDirX);
        float aHeightShiftY = (aHeight * aDirY);
        float aWidthShiftX = (aWidth * aNormalX);
        float aWidthShiftY = (aWidth * aNormalY);
        aCornerStartX -= ((aWidthShiftX * mAnchorX + aHeightShiftX * mAnchorY));
        aCornerStartY -= ((aWidthShiftY * mAnchorX + aHeightShiftY * mAnchorY));
        mCornerX[0] = aCornerStartX;
        mCornerY[0] = aCornerStartY;
        mCornerX[1] = aCornerStartX + aHeightShiftX;
        mCornerY[1] = aCornerStartY + aHeightShiftY;
        mCornerX[2] = aCornerStartX + (aWidthShiftX + aHeightShiftX);
        mCornerY[2] = aCornerStartY + (aWidthShiftY + aHeightShiftY);
        mCornerX[3] = aCornerStartX + aWidthShiftX;
        mCornerY[3] = aCornerStartY + aWidthShiftY;
    } else {
        aCornerStartX -= aAnchorWidth * aScaleX;
        aCornerStartY -= aAnchorHeight * aScaleY;
        mCornerX[0] = aCornerStartX;
        mCornerY[0] = aCornerStartY;
        mCornerX[1] = aCornerStartX;
        mCornerY[1] = aCornerStartY + aHeight;
        mCornerX[2] = aCornerStartX + aWidth;
        mCornerY[2] = aCornerStartY + aHeight;
        mCornerX[3] = aCornerStartX + aWidth;
        mCornerY[3] = aCornerStartY;
    }
}

void FCanvasAbsoluteTransform::ApplyAbsoluteTransformation(FCanvasTransform *pTransform, float pX, float pY, float pWidth, float pHeight) {
    mAnchorX = pTransform->mAnchorX;
    mAnchorY = pTransform->mAnchorY;
    mRotation = pTransform->mRotation;
    mScale = pTransform->mScale;
    mScaleX = pTransform->mScaleX;
    mScaleY = pTransform->mScaleY;
    float aAnchorWidth = mAnchorX * pWidth;
    float aAnchorHeight = mAnchorY * pHeight;
    float aAnchorX = aAnchorWidth * pTransform->mScale * pTransform->mScaleX;
    float aAnchorY = aAnchorHeight * pTransform->mScale * pTransform->mScaleY;
    mX = pX + pTransform->mX + aAnchorX + (aAnchorWidth - aAnchorX);
    mY = pY + pTransform->mY + aAnchorY + (aAnchorHeight - aAnchorY);
    float aScaleX = mScale * mScaleX;
    float aScaleY = mScale * mScaleY;
    float aWidth = pWidth * (aScaleX);
    float aHeight = pHeight * (aScaleY);
    float aCornerStartX = mX;
    float aCornerStartY = mY;
    if (mRotation != 0) {
        float aDirX = Sin(-mRotation);
        float aDirY = Cos(-mRotation);
        float aNormalX = (aDirY);
        float aNormalY = (-aDirX);
        float aHeightShiftX = (aHeight * aDirX);
        float aHeightShiftY = (aHeight * aDirY);
        float aWidthShiftX = (aWidth * aNormalX);
        float aWidthShiftY = (aWidth * aNormalY);
        aCornerStartX -= ((aWidthShiftX * mAnchorX + aHeightShiftX * mAnchorY));
        aCornerStartY -= ((aWidthShiftY * mAnchorX + aHeightShiftY * mAnchorY));
        mCornerX[0] = aCornerStartX;
        mCornerY[0] = aCornerStartY;
        mCornerX[1] = aCornerStartX + aHeightShiftX;
        mCornerY[1] = aCornerStartY + aHeightShiftY;
        mCornerX[2] = aCornerStartX + (aWidthShiftX + aHeightShiftX);
        mCornerY[2] = aCornerStartY + (aWidthShiftY + aHeightShiftY);
        mCornerX[3] = aCornerStartX + aWidthShiftX;
        mCornerY[3] = aCornerStartY + aWidthShiftY;
    } else {
        aCornerStartX -= aAnchorWidth * aScaleX;
        aCornerStartY -= aAnchorHeight * aScaleY;
        mCornerX[0] = aCornerStartX;
        mCornerY[0] = aCornerStartY;
        mCornerX[1] = aCornerStartX;
        mCornerY[1] = aCornerStartY + aHeight;
        mCornerX[2] = aCornerStartX + aWidth;
        mCornerY[2] = aCornerStartY + aHeight;
        mCornerX[3] = aCornerStartX + aWidth;
        mCornerY[3] = aCornerStartY;
    }
}

bool FCanvasAbsoluteTransform::ContainsPoint(float pX, float pY) {
    bool aResult = false;
    if (mRotation != 0) {
        for (int aStart=0,aEnd=3;aStart<4;aEnd=aStart++) {
            if ((((mCornerY[aStart] <= pY) && (pY < mCornerY[aEnd]))||
                ((mCornerY[aEnd] <= pY) && (pY < mCornerY[aStart])))&&
               (pX < (mCornerX[aEnd] - mCornerX[aStart]) * (pY - mCornerY[aStart])
                / (mCornerY[aEnd] - mCornerY[aStart]) + mCornerX[aStart])) {
                   aResult = !aResult;
               }
        }
    } else {
        aResult = ((pX >= mCornerX[0]) && (pY >= mCornerY[0]) && (pX <= mCornerX[2]) && (pY <= mCornerY[2]));
    }
    return aResult;
}

void FCanvasAbsoluteTransform::Untransform(float &pX, float &pY, float pWidth, float pHeight) {
    float aDiffX = (pX - (mAnchorX * pWidth)) * mScale * mScaleX;
    float aDiffY = (pY - (mAnchorY * pHeight)) * mScale * mScaleY;
    float aPivotRotation = FaceTarget(aDiffX, aDiffY) + mRotation;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if (aDist > SQRT_EPSILON) {
        aDist = sqrtf(aDist);
    }
    float aDirX = Sin(-aPivotRotation);
    float aDirY = Cos(-aPivotRotation);
    pX = aDirX * (aDist) + mX;
    pY = aDirY * (aDist) + mY;
}

void FCanvasAbsoluteTransform::Untransform(float &pX, float &pY) {
    float aDiffX = pX * mScale * mScaleX;
    float aDiffY = pY * mScale * mScaleY;
    float aPivotRotation = FaceTarget(aDiffX, aDiffY) + mRotation;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if (aDist > SQRT_EPSILON) { aDist = sqrtf(aDist); }
    float aDirX = Sin(-aPivotRotation);
    float aDirY = Cos(-aPivotRotation);
    pX = aDirX * (aDist) + mX;
    pY = aDirY * (aDist) + mY;
}

void FCanvasAbsoluteTransform::Transform(float &pX, float &pY) {
    float aX = pX;
    float aY = pY;
    float aDiffX = (aX - mX);
    float aDiffY = (aY - mY);
    float aRot = FaceTarget(aDiffX, aDiffY) - mRotation;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if (aDist > SQRT_EPSILON) { aDist = sqrtf(aDist); }
    float aDirX = Sin(-aRot);
    float aDirY = Cos(-aRot);
    pX = aDirX * (aDist / (mScale * mScaleX));
    pY = aDirY * (aDist / (mScale * mScaleY));
}

void FCanvasAbsoluteTransform::Transform(float &pX, float &pY, float pWidth, float pHeight) {
    float aX = pX;
    float aY = pY;
    float aDiffX = (aX - mX);
    float aDiffY = (aY - mY);
    float aRot = FaceTarget(aDiffX, aDiffY) - mRotation;
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    if (aDist > SQRT_EPSILON) { aDist = sqrtf(aDist); }
    float aDirX = Sin(-aRot);
    float aDirY = Cos(-aRot);
    pX = aDirX * (aDist / (mScale * mScaleX)) + mAnchorX * pWidth;
    pY = aDirY * (aDist / (mScale * mScaleY)) + mAnchorY * pHeight;
}
