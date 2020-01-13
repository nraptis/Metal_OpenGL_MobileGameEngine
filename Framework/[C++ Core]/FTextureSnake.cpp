//
//  FTextureSnake.cpp
//  Crazy Darts 2 iOS
//
//  Created by Nick Raptis on 1/8/20.
//  Copyright © 2020 Froggy Studios. All rights reserved.
//

#include "core_includes.h"
#include "os_core_graphics.h"
#include "FTextureSnake.hpp"

FTextureSnake::FTextureSnake() {
    mCount = 0;
    mSize = 0;
    
    mCenterX = 0;
    mCenterY = 0;
    
    mDirX = 0;
    mDirY = 0;
    
    mNormX = 0;
    mNormY = 0;
    
    mU = 0;
    mV = 0;
    
    mDist = 0;
    mPercent = 0;
    
    mOffsetU = 0.0f;
    
    mSprite = 0;
    
    mWidthFactor = 1.0f;
    
    mLength = 0.0f;
    
    //mNodeList.mStrips = false;
    
    mRefresh = false;
}

FTextureSnake::~FTextureSnake()
{
    Clear();
}


void FTextureSnake::Draw() {
    if (mRefresh) { Generate(); }
    mNodeList.DrawTris(mSprite);
}

void FTextureSnake::DrawMarkers() {
    
    for (int i=0;i<mCount;i++) {
        /*
         float aX = mCenterX[i];
         float aY = mCenterY[i];
         
         Graphics::SetColor(1.0f, 0.0f, 0.0f);
         
         Graphics::DrawPoint(aX, aY, 8);
         
         Graphics::SetColor(0.0f, 0.0f, 0.0f);
         
         Graphics::DrawPoint(aX, aY, 6.0f);
         */
    }
    
    for (int i=0;i<mCount;i++) {
        float aX = mCenterX[i];
        float aY = mCenterY[i];
        
        
        float aNormX = mNormX[i];
        float aNormY = mNormY[i];
        
        float aPush = 40.0f;
        
        float aCornerX1 = aX + aNormX * aPush;
        float aCornerY1 = aY + aNormY * aPush;
        
        float aCornerX2 = aX - aNormX * aPush;
        float aCornerY2 = aY - aNormY * aPush;
        
        
        Graphics::SetColor(0.5f, 0.95f, 0.0f);
        Graphics::DrawLine(aX, aY, aCornerX1, aCornerY1);
        
        Graphics::SetColor(0.95f, 0.5f, 0.0f);
        Graphics::DrawLine(aX, aY, aCornerX2, aCornerY2);
        
        Graphics::SetColor(0.25f, 0.5f, 0.75f);
        
        
        
    }
    
    
    Graphics::SetColor();
    
}

void FTextureSnake::Reset() {
    mCount = 0;
    mRefresh = true;
    mNodeList.Reset();
}

void FTextureSnake::Clear() {
    delete [] mCenterX;
    
    mCenterX = 0;
    mCenterY = 0;
    
    mCount = 0;
    mSize = 0;
    
    mDirX = 0;
    mDirY = 0;
    
    mNormX = 0;
    mNormY = 0;
    
    mU = 0;
    mV = 0;
    
    mDist = 0;
    
    mLength = 0.0f;
    
    mRefresh = true;
}

void FTextureSnake::Size(int pSize) {
    
    if (pSize <= 0) {
        return;
    }
    
    mSize = pSize;
    
    int aSize = pSize * 10;
    
    float *aCenterX = new float[aSize];
    float *aCenterY = &(aCenterX[pSize]);
    
    float *aDirX = &(aCenterY[pSize]);
    float *aDirY = &(aDirX[pSize]);
    
    float *aNormX = &(aDirY[pSize]);
    float *aNormY = &(aNormX[pSize]);
    
    float *aU = &(aNormY[pSize]);
    float *aV = &(aU[pSize]);
    
    float *aDist = &(aV[pSize]);
    float *aPercent = &(aDist[pSize]);
    
    for (int i=0;i<mCount;i++) { aCenterX[i] = mCenterX[i]; }
    for (int i=0;i<mCount;i++) { aCenterY[i] = mCenterY[i]; }
    
    for (int i=0;i<mCount;i++) { aDirX[i] = mDirX[i]; }
    for (int i=0;i<mCount;i++) { aDirY[i] = mDirY[i]; }
    
    for (int i=0;i<mCount;i++) { aNormX[i] = mNormX[i]; }
    for (int i=0;i<mCount;i++) { aNormY[i] = mNormY[i]; }
    
    for (int i=0;i<mCount;i++) { aU[i] = mU[i]; }
    for (int i=0;i<mCount;i++) { aV[i] = mV[i]; }
    
    for (int i=0;i<mCount;i++) { aDist[i] = mDist[i]; }
    for (int i=0;i<mCount;i++) { aPercent[i] = mPercent[i]; }
    
    for (int i=mCount;i<mSize;i++) { aCenterX[i] = 0.0f; }
    for (int i=mCount;i<mSize;i++) { aCenterY[i] = 0.0f; }
    
    for (int i=mCount;i<mSize;i++) { aDirX[i] = 0.0f; }
    for (int i=mCount;i<mSize;i++) { aDirY[i] = 0.0f; }
    
    for (int i=mCount;i<mSize;i++) { aNormX[i] = 0.0f; }
    for (int i=mCount;i<mSize;i++) { aNormY[i] = 0.0f; }
    
    for (int i=mCount;i<mSize;i++) { aU[i] = 0.0f; }
    for (int i=mCount;i<mSize;i++) { aV[i] = 0.0f; }
    
    for (int i=mCount;i<mSize;i++) { aDist[i] = 0.0f; }
    for (int i=mCount;i<mSize;i++) { aPercent[i] = 1.0f; }
    
    delete [] mCenterX;
    
    mCenterX = aCenterX;
    mCenterY = aCenterY;
    
    mDirX = aDirX;
    mDirY = aDirY;
    
    mNormX = aNormX;
    mNormY = aNormY;
    
    mU = aU;
    mV = aV;
    
    mDist = aDist;
    mPercent = aPercent;
}

void FTextureSnake::SetPoint(int pIndex, float pX, float pY) {
    mRefresh = true;
    
    if (pIndex >= mSize) {
        Size(pIndex + pIndex / 2 + 1);
    }
    
    mCenterX[pIndex] = pX;
    mCenterY[pIndex] = pY;
    
    if (pIndex > mCount) {
        mCount = pIndex;
    }
}

void FTextureSnake::AddPoint(float pX, float pY) {
    mRefresh = true;
    
    if (mCount >= mSize) {
        Size(mCount + mCount / 2 + 1);
    }
    
    mCenterX[mCount] = pX;
    mCenterY[mCount] = pY;
    
    mCount++;
}

void FTextureSnake::SetSprite(FSprite *pSprite) {
    if (mSprite != pSprite) {
        mSprite = pSprite;
        mRefresh = true;
    }
}

void FTextureSnake::Generate() {
    
    mLength = 0.0f;
    mRefresh = false;
    
    if (mCount < 2) { return; }
    if (mSprite == 0) { return; }
    
    float aImageWidth = mSprite->mHeight;
    float aPushWidth = mSprite->mWidth / 2.0f;
    
    aPushWidth *= mWidthFactor;
    aImageWidth *= mWidthFactor;
    
    if ((aImageWidth < 1.0f) || (aPushWidth < 1.0f)) { return; }
    
    float aLastX = mCenterX[0];
    float aLastY = mCenterY[0];
    
    float aX = aLastX;
    float aY = aLastY;
    
    float aDirX = 0.0f;
    float aDirY = -1.0f;
    
    float aDiffX = 0.0f;
    float aDiffY = 0.0f;
    float aDist = 0.1f;
    
    int aIndex = 0;
    
    mDist[0] = 0.0f;
    
    for (int i=1;i<mCount;i++) {
        aX = mCenterX[i];
        aY = mCenterY[i];
        
        aDiffX = aX - aLastX;
        aDiffY = aY - aLastY;
        
        aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if (aDist > SQRT_EPSILON) {
            aDist = sqrtf(aDist);
            
            aDirX = aDiffX / aDist;
            aDirY = aDiffY / aDist;
        } else {
            aDist = 0.1f;
        }

        mDist[i] = aDist;
        mLength += aDist;
        
        mDirX[aIndex] = aDirX;
        mDirY[aIndex] = aDirY;
        
        mNormX[aIndex] = -aDirY;
        mNormY[aIndex] = aDirX;
        
        aIndex++;
        
        aLastX = aX;
        aLastY = aY;
    }
    
    mDirX[aIndex] = aDirX;
    mDirY[aIndex] = aDirY;
    
    mNormX[aIndex] = -aDirY;
    mNormY[aIndex] = aDirX;

    if (mLength < 1.0f) {
        mLength = 1.0f;
    }
    
    float aPercent = 0.0f;
    
    //float aStartU = mSprite->GetStartU();
    float aStartV = mSprite->GetStartV();
    //float aEndU = mSprite->GetEndU();
    float aEndV = mSprite->GetEndV();
    
    aDist = 0.0f;
    mU[0] = mOffsetU;
    
    
    for (int i=mCount-1;i>=0;i--) {
        aPercent = aDist / aImageWidth;
        mU[i] = mOffsetU + aPercent;
        aDist += mDist[i];
    }
    
    float aOvershoot = 1.0f - fmodf(aPercent, 1.0f);
    for (int i=0;i<mCount;i++) {
        mU[i] += aOvershoot;
    }
    
    /*
    for (int i=1;i<mCount;i++) {
        aDist += mDist[i];
        aPercent = aDist / aImageWidth;
        mU[i] = mOffsetU + aPercent;
    }
    */
    
    
    float aNormX = 0.0f;
    float aNormY = 0.0f;
    
    mNodeList.Reset();
    
    int aStripIndex = 0;
    
    float aX1 = mCenterX[0] - mNormX[0] * aPushWidth;
    float aY1 = mCenterY[0] - mNormY[0] * aPushWidth;
    
    float aX2 = mCenterX[0] + mNormX[0] * aPushWidth;
    float aY2 = mCenterY[0] + mNormY[0] * aPushWidth;
    
    float aLastX1 = aX1;
    float aLastY1 = aY1;
    
    float aLastX2 = aX2;
    float aLastY2 = aY2;
    
    aX = mCenterX[0];
    aY = mCenterY[0];
    
    float aU =  mU[0];
    float aLastU = mU[0];
    
    for (int i=1;i<mCount;i++) {
        aX = mCenterX[i];
        aY = mCenterY[i];
        
        aNormX = mNormX[i];
        aNormY = mNormY[i];
        
        aU = mU[i];
        
        
        //printf("U[%d] == %.3f (%.3f)\n", i, aU, aLastU);
        
        aX1 = aX - aNormX * aPushWidth;
        aY1 = aY - aNormY * aPushWidth;
        
        aX2 = aX + aNormX * aPushWidth;
        aY2 = aY + aNormY * aPushWidth;
        
        ////////////
        //////////// - Triangle 1 - /////////
        ////////////
        
        //Top Left (startU, startV)
        mNodeList.SetXYZ(aStripIndex, aLastX1, aLastY1, 0.0f);
        mNodeList.SetUV(aStripIndex, aStartV, aLastU);
        aStripIndex++;
        
        //Bottom Left (startU, endV)
        mNodeList.SetXYZ(aStripIndex, aX1, aY1, 0.0f);
        mNodeList.SetUV(aStripIndex, aStartV, aU);
        aStripIndex++;
        
        //Top Right (endU, startV)
        mNodeList.SetXYZ(aStripIndex, aLastX2, aLastY2, 0.0f);
        mNodeList.SetUV(aStripIndex, aEndV, aLastU);
        aStripIndex++;
        
        ////////////
        //////////// - Triangle 2 - /////////
        ////////////
        
        //Top Right (endU, startV)
        mNodeList.SetXYZ(aStripIndex, aLastX2, aLastY2, 0.0f);
        mNodeList.SetUV(aStripIndex, aEndV, aLastU);
        aStripIndex++;
        
        //Bottom Left (startU, endV)
        mNodeList.SetXYZ(aStripIndex, aX1, aY1, 0.0f);
        mNodeList.SetUV(aStripIndex, aStartV, aU);
        aStripIndex++;
        
        //Bottom Right (endU, endV)
        mNodeList.SetXYZ(aStripIndex, aX2, aY2, 0.0f);
        mNodeList.SetUV(aStripIndex, aEndV, aU);
        aStripIndex++;
        
        aLastX1 = aX1;
        aLastY1 = aY1;
        aLastX2 = aX2;
        aLastY2 = aY2;
        aLastU = aU;
        
        
    }
}
