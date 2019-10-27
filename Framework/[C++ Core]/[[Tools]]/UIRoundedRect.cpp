//
//  UIRoundedRect.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "core_includes.h"
#include "UIRoundedRect.hpp"

UIRoundedRect::UIRoundedRect() {
    SetRect(0.0f, 0.0f, 44.0f, 44.0f);
    mCornerRadius = 12;mCornerPointCount = 12;
    mRoundBottom = true;mRoundRight = true;mRoundLeft = true;mSquare = false;
    SetColorTop(0.9575f, 0.96f, 0.9589f);
    SetColorBottom(0.875f, 0.0f, 0.0f);
    mRefresh = true;
}

UIRoundedRect::~UIRoundedRect() {

}

void UIRoundedRect::Generate() {
    float *aDirX = new float[mCornerPointCount];
    float *aDirY = new float[mCornerPointCount];
    for (int i=0;i<mCornerPointCount;i++) {
        float aPercent = ((float)(i + 1)) / (mCornerPointCount + 2);
        float aAngle = 0.0f + (0.0f - 90.0f) * aPercent;
        aDirX[i] = Sin(aAngle) * mCornerRadius;
        aDirY[i] = -Cos(aAngle) * mCornerRadius;
    }

    mNodeList.Reset();
    int aWriteIndex = 0;
    float aStartX = X1();
    float aStartY = Y1();
    float aEndX = X4();
    float aEndY = Y4();
    if (mSquare) {
        mNodeList.SetXY(aWriteIndex++, aStartX, aStartY);
        mNodeList.SetXY(aWriteIndex++, aEndX, aStartY);
        mNodeList.SetXY(aWriteIndex++, aStartX, aEndY);
        mNodeList.SetXY(aWriteIndex++, aEndX, aEndY);
    } else {
        mNodeList.SetXY(aWriteIndex++, aStartX + mCornerRadius, aStartY);
        mNodeList.SetXY(aWriteIndex++, aEndX - mCornerRadius, aStartY);
        for (int i=0;i<mCornerPointCount;i++) {
            float aDX = aDirX[i];
            float aDY = aDirY[i];
            if (mRoundLeft) {
                mNodeList.SetXY(aWriteIndex++, (aStartX + mCornerRadius) + aDX, (aStartY + mCornerRadius) + aDY);
            } else {
                mNodeList.SetXY(aWriteIndex++, aStartX, (aStartY + mCornerRadius) + aDY);
            }
            if (mRoundRight) {
                mNodeList.SetXY(aWriteIndex++, (aEndX - mCornerRadius) - aDX, (aStartY + mCornerRadius) + aDY);
            } else {
                mNodeList.SetXY(aWriteIndex++, aEndX, (aStartY + mCornerRadius) + aDY);
            }
        }

        mNodeList.SetXY(aWriteIndex++, aStartX, aStartY + mCornerRadius);
        mNodeList.SetXY(aWriteIndex++, aEndX, aStartY + mCornerRadius);

        if (mRoundBottom == true) {
            mNodeList.SetXY(aWriteIndex++, aStartX, aEndY - mCornerRadius);
            mNodeList.SetXY(aWriteIndex++, aEndX, aEndY - mCornerRadius);
            for (int i=(mCornerPointCount-1);i>=0;i--) {
                float aDX = aDirX[i];
                float aDY = aDirY[i];
                if (mRoundLeft) mNodeList.SetXY(aWriteIndex++, (aStartX + mCornerRadius) + aDX, (aEndY - mCornerRadius) - aDY);
                else mNodeList.SetXY(aWriteIndex++, aStartX, (aEndY - mCornerRadius) - aDY);
                if (mRoundRight) mNodeList.SetXY(aWriteIndex++, (aEndX - mCornerRadius) - aDX, (aEndY - mCornerRadius) - aDY);
                else mNodeList.SetXY(aWriteIndex++, aEndX, (aEndY - mCornerRadius) - aDY);
            }
            mNodeList.SetXY(aWriteIndex++, aStartX + mCornerRadius, aEndY);
            mNodeList.SetXY(aWriteIndex++, aEndX - mCornerRadius, aEndY);
        } else {
            mNodeList.SetXY(aWriteIndex++, aStartX, aEndY);
            mNodeList.SetXY(aWriteIndex++, aEndX, aEndY);
        }
    }
    delete [] aDirX;
    delete [] aDirY;
    float aHeight = (aEndY - aStartY);
    for (int i=0;i<mNodeList.mCountNodes;i++) {
        float aPercent = (mNodeList.GetY(i) - aStartY) / aHeight;
        mNodeList.SetRGBA(i, mVertex[0].mR + (mVertex[3].mR - mVertex[0].mR) * aPercent, mVertex[0].mG + (mVertex[3].mG - mVertex[0].mG) * aPercent, mVertex[0].mB + (mVertex[3].mB - mVertex[0].mB) * aPercent, mVertex[0].mA + (mVertex[3].mA - mVertex[0].mA) * aPercent);
    }
}

void UIRoundedRect::Draw() {
    if (mRefresh) {
        Generate();
        mRefresh = false;
    }
    
    Graphics::PipelineStateSetShapeNodeAlphaBlending();
    mNodeList.DrawTriStrips();
}

void UIRoundedRect::Draw(float pOffsetX, float pOffsetY) {
    FMatrix aModelView = Graphics::MatrixModelViewGet();
    FMatrix aHold = aModelView;
    aModelView.Translate(pOffsetX, pOffsetY);
    Graphics::MatrixModelViewSet(aModelView);
    Draw();
    Graphics::MatrixModelViewSet(aHold);
}

void UIRoundedRect::Copy(UIRoundedRect *pRect, bool pIgnoreColor) {
    if (pRect) {
        FDrawQuad::CopyXYZ(pRect);
        FDrawQuad::CopyUVW(pRect);
        if (pIgnoreColor == false) {
            FDrawQuad::CopyRGBA(pRect);
        }
        mCornerRadius = pRect->mCornerRadius;
        mCornerPointCount = pRect->mCornerPointCount;
        mRoundBottom = pRect->mRoundBottom;
        mRoundRight = pRect->mRoundRight;
        mRoundLeft = pRect->mRoundLeft;
        mSquare = pRect->mSquare;
    }
}
