//
//  DragableCanvas.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "DragableCanvas.hpp"
#include "FApp.hpp"

DragableCanvas::DragableCanvas() {
    mConsumesTouches = true;
    //TODO...?
    mRecievesOutsideTouches = false;
    mRecievesConsumedTouches = false;
    mClipEnabled = false;
    mResizeDragTouchX = 0.0f;
    mResizeDragTouchY = 0.0f;
    mResizeCornerIndex = -1;
    mResizeDragData = 0;
    mResizeCornerX[0] = gVirtualDevX;
    mResizeCornerY[0] = gVirtualDevY;
    mResizeCornerX[1] = gVirtualDevX;
    mResizeCornerY[1] = gVirtualDevY + gVirtualDevHeight;
    mResizeCornerX[2] = gVirtualDevX + gVirtualDevWidth;
    mResizeCornerY[2] = gVirtualDevY;
    mResizeCornerX[3] = gVirtualDevX + gVirtualDevWidth;
    mResizeCornerY[3] = gVirtualDevY + gVirtualDevHeight;
    mPanDragTouchX = 0.0f;
    mPanDragTouchY = 0.0f;
    mPanDragData = 0;
    mSizeMinWidth = 280.0f;
    mSizeMinHeight = 80.0f;
    mResizeDragAllowed = true;
    mResizeDragAllowedH = true;
    mResizeDragAllowedV = true;
    mClipEnabled = false;
    mPanConstrainToScreen = false;
}

DragableCanvas::~DragableCanvas() {

}


void DragableCanvas::Draw() {
    FCanvas::Draw();
    float aFillRed = 0.33f;
    float aFillGreen = 0.33f;
    float aFillBlue = 0.33f;
    if (mMouseLeftDown) {
        aFillRed = 0.66f;
    }
    if (mMouseMiddleDown) {
        aFillGreen = 0.66f;
    }
    if (mMouseRightDown) {
        aFillBlue = 0.66f;
    }
    if (mMouseLeftDownInside) {
        aFillRed = 1.0f;
    }
    if (mMouseMiddleDownInside) {
        aFillGreen = 1.0f;
    }
    if (mMouseRightDownInside) {
        aFillBlue = 1.0f;
    }
    Graphics::SetColor(aFillRed, aFillGreen, aFillBlue, 0.33);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    Graphics::SetColor();
    Graphics::OutlineRectInside(0.0f, 0.0f, mWidth, mHeight, 4.0f);
    if (mTouchDown) {
        Graphics::SetColor(0.44f, 0.44f, 0.44f, 1.0f);
        Graphics::DrawPoint(mMouseX, mMouseY, 22.0f);
        Graphics::SetColor(0.66f, 0.66f, 0.75f, 1.0f);
        Graphics::DrawPoint(mMouseX, mMouseY, 18.0f);
    } else {
        Graphics::SetColor(0.88f, 0.88f, 0.88f, 1.0f);
        Graphics::DrawPoint(mMouseX, mMouseY, 22.0f);
        Graphics::SetColor(0.33f, 0.33f, 0.89f, 1.0f);
        Graphics::DrawPoint(mMouseX, mMouseY, 18.0f);
    }
    Graphics::SetColor();
}

FCanvas *DragableCanvas::BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent, bool &pConsumed) {
    FCanvas *aChild = FCanvas::BaseTouchDown(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent, pConsumed);
    if (mResizeCornerIndex != -1 || mPanDragData != 0) {
        return aChild;
    }

    if (mResizeDragAllowed == false) {
        mResizeDragData = 0;
        mResizeCornerIndex = -1;
    } else {
        ResetCorners();
        float aCornerDist = 40.0f;
        if (!pConsumed && !pOutsideParent) {
            for (int i=0;i<4;i++) {
                float aX = mResizeCornerX[i];
                float aY = mResizeCornerY[i];
                float aDist = Distance(aX, aY, pX, pY);
                if (aDist < aCornerDist) {
                    mResizeDragCornerX = aX;
                    mResizeDragCornerY = aY;
                    aCornerDist = aDist;
                    mResizeCornerIndex = i;
                }
            }
        }
    }

    if (mResizeCornerIndex != -1) {
        mDragFrameStartX = mX;
        mDragFrameStartY = mY;
        mDragFrameStartWidth = mWidth;
        mDragFrameStartHeight = mHeight;
        mResizeDragData = pData;
        mResizeDragTouchX = pX;
        mResizeDragTouchY = pY;
        pConsumed = true;
        return aChild;
    }

    if (!pConsumed && !pOutsideParent) {
        if (aChild == this) {
            if (pX >= mX && pX <= (mX + mWidth) && pY >= mY && pY <= (mY +mHeight)) {
                mPanDragData = pData;
                mPanDragTouchX = pX;
                mPanDragTouchY = pY;
                mDragFrameStartX = mX;
                mDragFrameStartY = mY;
                return aChild;
            }
        }
    }
    return aChild;
}

void DragableCanvas::BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {
    FCanvas::BaseTouchMove(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);
    if (mResizeCornerIndex != -1) {
        UpdateCornerDrag(pX, pY, pData);
        return;
    }
    if (mPanDragData == pData) {
        UpdatePanDrag(pX, pY, pData);
        return;
    }
}

void DragableCanvas::BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData, bool pOutsideParent) {
    FCanvas::BaseTouchUp(pX, pY, pOriginalX, pOriginalY, pData, pOutsideParent);
    if (mResizeCornerIndex != -1) {
        UpdateCornerDrag(pX, pY, pData);
        mPanDragData = 0;
        mResizeCornerIndex = -1;
        ResetCorners();
        return;
    }
    if (mPanDragData == pData) {
        UpdatePanDrag(pX, pY, pData);
        mPanDragData = 0;
        mResizeCornerIndex = -1;
        ResetCorners();
        return;
    }
    mPanDragData = 0;
    mResizeCornerIndex = -1;
}

void DragableCanvas::UpdatePanDrag(float pX, float pY, void *pData) {
    if (mPanDragData == pData) {
        float aNewX = mDragFrameStartX + (pX - mPanDragTouchX);
        float aNewY = mDragFrameStartY + (pY - mPanDragTouchY);
        float aNewWidth = mWidth;
        float aNewHeight = mHeight;
        if (mPanConstrainToScreen) {
            if (aNewX < 0) { aNewX = 0; }
            if (aNewY < 0) { aNewY = 0; }
            if (aNewX + aNewWidth > mParent->mWidth) {
                aNewX = mParent->mWidth - aNewWidth;
            }
            if (aNewY + aNewHeight > mParent->mHeight) {
                aNewY = mParent->mHeight - aNewHeight;
            }
        }
        SetX(aNewX);
        SetY(aNewY);
        SetWidth(aNewWidth);
        SetHeight(aNewHeight);
    }
}

void DragableCanvas::UpdateCornerDrag(float pX, float pY, void *pData) {
    if (mResizeDragAllowed == false) {
        mResizeDragData = 0;
        mResizeCornerIndex = -1;
    }
    if (mResizeDragData == pData) {
        if((mResizeCornerIndex >= 0) && (mResizeCornerIndex < 4)) {
            float aDeltaX = (pX - mResizeDragTouchX);
            float aDeltaY = (pY - mResizeDragTouchY);
            float aX = mResizeDragCornerX + aDeltaX;
            float aY = mResizeDragCornerY + aDeltaY;
            mResizeCornerX[mResizeCornerIndex] = aX;
            mResizeCornerY[mResizeCornerIndex] = aY;
            float aNewX = mX;
            float aNewY = mY;
            float aNewWidth = mWidth;
            float aNewHeight = mHeight;
            if (mResizeCornerIndex == 0) {
                aNewX = mDragFrameStartX + aDeltaX;
                aNewWidth = mDragFrameStartWidth - aDeltaX;
                aNewY = mDragFrameStartY + aDeltaY;
                aNewHeight = mDragFrameStartHeight - aDeltaY;
            }
            if (mResizeCornerIndex == 1) {
                aNewWidth = mDragFrameStartWidth + aDeltaX;
                aNewY = mDragFrameStartY + aDeltaY;
                aNewHeight = mDragFrameStartHeight - aDeltaY;
            }
            if (mResizeCornerIndex == 2) {
                aNewX = mDragFrameStartX + aDeltaX;
                aNewWidth = mDragFrameStartWidth - aDeltaX;
                aNewHeight = mDragFrameStartHeight + aDeltaY;
            }
            if (mResizeCornerIndex == 3) {
                aNewWidth = mDragFrameStartWidth + aDeltaX;
                aNewHeight = mDragFrameStartHeight + aDeltaY;
            }
            if (mResizeCornerIndex == 0) {
                if (aNewX < 0) {
                    aNewWidth += aNewX;
                    aNewX = 0;
                }
                if (aNewY < 0) {
                    aNewHeight += aNewY;
                    aNewY = 0;
                }
                if (aNewWidth < mSizeMinWidth) {
                    aNewX -= (mSizeMinWidth - aNewWidth);
                    aNewWidth = mSizeMinWidth;
                }
                if (aNewHeight < mSizeMinHeight) {
                    aNewY -= (mSizeMinHeight - aNewHeight);
                    aNewHeight = mSizeMinHeight;
                }
            }

            if (mResizeCornerIndex == 1) {
                if (aNewWidth + aNewX > mParent->mWidth) {
                    aNewWidth -= (aNewWidth + aNewX) - mParent->mWidth;
                    aNewX = mParent->mWidth - aNewWidth;
                }
                if (aNewY < 0) {
                    aNewHeight += aNewY;
                    aNewY = 0;
                }
                if (aNewWidth < mSizeMinWidth) {
                    aNewX = mX;
                    aNewWidth = mSizeMinWidth;
                }
                if (aNewHeight < mSizeMinHeight) {
                    aNewY -= (mSizeMinHeight - aNewHeight);
                    aNewHeight = mSizeMinHeight;
                }
            }

            if (mResizeCornerIndex == 2) {
                if (aNewX < 0) {
                    aNewWidth += aNewX;
                    aNewX = 0;
                }
                if (aNewHeight + aNewY > mParent->mHeight) {
                    aNewHeight -= (aNewHeight + aNewY) - mParent->mHeight;
                    aNewY = mParent->mHeight - aNewHeight;
                }
                if (aNewWidth < mSizeMinWidth) {
                    aNewX -= (mSizeMinWidth - aNewWidth);
                    aNewWidth = mSizeMinWidth;
                }
                if (aNewHeight < mSizeMinHeight) {
                    aNewY = mY;
                    aNewHeight = mSizeMinHeight;
                }
            }

            if (mResizeCornerIndex == 3) {
                if (aNewWidth + aNewX > mParent->mWidth) {
                    aNewWidth -= (aNewWidth + aNewX) - mParent->mWidth;
                    aNewX = mParent->mWidth - aNewWidth;
                }
                if (aNewHeight + aNewY > mParent->mHeight) {
                    aNewHeight -= (aNewHeight + aNewY) - mParent->mHeight;
                    aNewY = mParent->mHeight - aNewHeight;
                }
                if (aNewWidth < mSizeMinWidth) {
                    aNewWidth = mSizeMinWidth;
                }
                if (aNewHeight < mSizeMinHeight) {
                    aNewHeight = mSizeMinHeight;
                }
            }
            if (mResizeDragAllowedH) {
                SetX(aNewX);
                SetWidth(aNewWidth);
            }
            if (mResizeDragAllowedV) {
                SetY(aNewY);
                SetHeight(aNewHeight);
            }
            ResetCorners();
        }
    }
}

void DragableCanvas::ResetCorners() {
    
    
    mResizeCornerX[0] = mX;
    mResizeCornerY[0] = mY;
    mResizeCornerX[1] = mX + mWidth;
    mResizeCornerY[1] = mY;
    mResizeCornerX[2] = mX;
    mResizeCornerY[2] = mY + mHeight;
    mResizeCornerX[3] = mX + mWidth;
    mResizeCornerY[3] = mY + mHeight;
    
    if (mParent) {
    for (int i=0;i<4;i++) {
        mResizeCornerX[i] += mParent->mTransformAbsolute.mCornerX[0];
        mResizeCornerY[i] += mParent->mTransformAbsolute.mCornerY[0];
    }
    }
    
}
