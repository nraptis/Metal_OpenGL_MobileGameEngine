//
//  QuadSpewer.cpp
//  Digplex
//
//  Created by Nick Raptis on 9/23/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FDrawQuad.hpp"

FDrawQuad::FDrawQuad() {
    
    mVertex[0].mX = 0.0f;
    mVertex[0].mY = 0.0f;
    mVertex[0].mZ = 0.0f;
    mVertex[0].mR = 1.0f;
    mVertex[0].mG = 1.0f;
    mVertex[0].mB = 1.0f;
    mVertex[0].mA = 1.0f;
    mVertex[0].mU = 0.0f;
    mVertex[0].mV = 0.0f;
    mVertex[0].mW = 0.0f;
    
    mVertex[1].mX = 0.0f;
    mVertex[1].mY = 0.0f;
    mVertex[1].mZ = 0.0f;
    mVertex[1].mR = 1.0f;
    mVertex[1].mG = 1.0f;
    mVertex[1].mB = 1.0f;
    mVertex[1].mA = 1.0f;
    mVertex[1].mU = 1.0f;
    mVertex[1].mV = 0.0f;
    mVertex[1].mW = 0.0f;
    
    mVertex[2].mX = 0.0f;
    mVertex[2].mY = 0.0f;
    mVertex[2].mZ = 0.0f;
    mVertex[2].mR = 1.0f;
    mVertex[2].mG = 1.0f;
    mVertex[2].mB = 1.0f;
    mVertex[2].mA = 1.0f;
    mVertex[2].mU = 0.0f;
    mVertex[2].mV = 1.0f;
    mVertex[2].mW = 0.0f;
    
    mVertex[3].mX = 0.0f;
    mVertex[3].mY = 0.0f;
    mVertex[3].mZ = 0.0f;
    mVertex[3].mR = 1.0f;
    mVertex[3].mG = 1.0f;
    mVertex[3].mB = 1.0f;
    mVertex[3].mA = 1.0f;
    mVertex[3].mU = 1.0f;
    mVertex[3].mV = 1.0f;
    mVertex[3].mW = 0.0f;
}

FDrawQuad::~FDrawQuad() {
    
}

static GFX_MODEL_INDEX_TYPE cDrawQuadIndex[6] = { 0, 1, 2, 1, 3, 2 };
void FDrawQuad::Draw(FSprite *pSprite) {
    if ((pSprite != NULL) && (pSprite->mTexture != NULL)) {
        float *aPtr = (float *)(&(mVertex[0]));
        if (Graphics::ArrayWriteData(aPtr, 4 * sizeof(FDrawNode))) {
            Graphics::TextureBind(pSprite->mTexture);
            Graphics::ArrayBufferPositions(NULL, 0);
            Graphics::ArrayBufferTextureCoords(NULL, sizeof(float) * 3);
            Graphics::ArrayBufferColors(NULL, sizeof(float) * 6);
            Graphics::UniformBind();
            Graphics::DrawTrianglesIndexed(cDrawQuadIndex, 6);
        }
    } else {
        Draw();
    }
}

void FDrawQuad::Draw(FSprite &pSprite) {
    Draw(&pSprite);
}

void FDrawQuad::Draw() {
    
    float *aPtr = (float *)(&(mVertex[0]));
    if (Graphics::ArrayWriteData(aPtr, 4 * sizeof(FDrawNode))) {
        Graphics::ArrayBufferPositions(NULL, 0);
        Graphics::ArrayBufferTextureCoords(NULL, sizeof(float) * 3);
        Graphics::ArrayBufferColors(NULL, sizeof(float) * 6);
        Graphics::UniformBind();
        Graphics::DrawTrianglesIndexed(cDrawQuadIndex, 6);
    }
}

void FDrawQuad::DrawCorners() {
    Graphics::PipelineStateSetShape2DAlphaBlending();
    for (int i=0;i<4;i++) {
        float aX = mVertex[i].mX;
        float aY = mVertex[i].mY;
        Graphics::OutlineRect(aX - 3, aY - 3, 7, 7, 2);
    }
}

void FDrawQuad::DrawOutline() {
    Graphics::PipelineStateSetShape2DAlphaBlending();
    for (int aStart=0, aEnd=3;aStart<4;aEnd = aStart++) {
        Graphics::DrawLine(mVertex[aEnd].mX, mVertex[aEnd].mY, mVertex[aStart].mX, mVertex[aStart].mY, 2);
    }
}

void FDrawQuad::SetQuad(float pStartX, float pStartY, float pEndX, float pEndY) {
    SetQuad(pStartX, pStartY, pEndX, pStartY, pStartX, pEndY, pEndX, pEndY);
}

void FDrawQuad::SetQuad(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4) {
    mVertex[0].mX = pX1;
    mVertex[0].mY = pY1;
    mVertex[1].mX = pX2;
    mVertex[1].mY = pY2;
    mVertex[2].mX = pX3;
    mVertex[2].mY = pY3;
    mVertex[3].mX = pX4;
    mVertex[3].mY = pY4;
}

void FDrawQuad::SetRect(float pX, float pY, float pWidth, float pHeight) {
    SetQuad(pX, pY, pX + pWidth, pY, pX, pY + pHeight, pX + pWidth, pY + pHeight);
}

void FDrawQuad::SetTextureQuad(float pStartU, float pStartV, float pEndU, float pEndV) {
    mVertex[0].mU = pStartU;
    mVertex[0].mV = pStartV;
    mVertex[1].mU = pEndU;
    mVertex[1].mV = pStartV;
    mVertex[2].mU = pStartU;
    mVertex[2].mV = pEndV;
    mVertex[3].mU = pEndU;
    mVertex[3].mV = pEndV;
}

void FDrawQuad::Shift(float pX, float pY, float pZ) {
    for(int i=0;i<4;i++) {
        mVertex[i].mX += pX;
        mVertex[i].mY += pY;
        mVertex[i].mZ += pZ;
    }
}

void FDrawQuad::Copy(FDrawQuad *pQuad) {
    if (pQuad) {
        for (int i=0;i<4;i++) {
            mVertex[i].mX = pQuad->mVertex[i].mX;mVertex[i].mY = pQuad->mVertex[i].mY;mVertex[i].mZ = pQuad->mVertex[i].mZ;
            mVertex[i].mU = pQuad->mVertex[i].mU;mVertex[i].mV = pQuad->mVertex[i].mV;mVertex[i].mW = pQuad->mVertex[i].mW;
            mVertex[i].mR = pQuad->mVertex[i].mR;mVertex[i].mG = pQuad->mVertex[i].mG;mVertex[i].mB = pQuad->mVertex[i].mB;mVertex[i].mA = pQuad->mVertex[i].mA;
        }
    }
}

void FDrawQuad::CopyXYZ(FDrawQuad *pQuad) {
    if (pQuad) {
        for (int i=0;i<4;i++) {
            mVertex[i].mX = pQuad->mVertex[i].mX;mVertex[i].mY = pQuad->mVertex[i].mY;mVertex[i].mZ = pQuad->mVertex[i].mZ;
        }
    }
}

void FDrawQuad::CopyUVW(FDrawQuad *pQuad) {
    if (pQuad) {
        for (int i=0;i<4;i++) {
            mVertex[i].mU = pQuad->mVertex[i].mU;mVertex[i].mV = pQuad->mVertex[i].mV;mVertex[i].mW = pQuad->mVertex[i].mW;
        }
    }
}

void FDrawQuad::CopyRGBA(FDrawQuad *pQuad) {
    if (pQuad) {
        for (int i=0;i<4;i++) {
            mVertex[i].mR = pQuad->mVertex[i].mR;mVertex[i].mG = pQuad->mVertex[i].mG;mVertex[i].mB = pQuad->mVertex[i].mB;mVertex[i].mA = pQuad->mVertex[i].mA;
        }
    }
}

void FDrawQuad::Print() {
    Log("SetQuad(%.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f)\n", mVertex[0].mX, mVertex[0].mY,
        mVertex[1].mX, mVertex[1].mY, mVertex[2].mX, mVertex[2].mY, mVertex[3].mX, mVertex[3].mY);
}

void FDrawQuad::TransformSpriteCorners(float pCenterX, float pCenterY, FSprite *pSprite, float pRotation, float pScale) {
    mVertex[0].mX = pSprite->GetStartX();
    mVertex[0].mY = pSprite->GetStartY();
    mVertex[1].mX = pSprite->GetEndX();
    mVertex[1].mY = pSprite->GetStartY();
    mVertex[2].mX = pSprite->GetEndX();
    mVertex[2].mY = pSprite->GetEndY();
    mVertex[3].mX = pSprite->GetStartX();
    mVertex[3].mY = pSprite->GetEndY();
    RotateAndScale(pRotation, 1.0f);
    Shift(pCenterX, pCenterY);
}

void FDrawQuad::RotateAndScale(float pDegrees, float pScale) {
    Rotate(pDegrees);
    Scale(pScale);
}

void FDrawQuad::SetTextureCoords(FSprite *pSprite) {
    if (pSprite != NULL) {
        float aStartU = pSprite->GetStartU();
        float aStartV = pSprite->GetStartV();
        float aEndU = pSprite->GetEndU();
        float aEndV = pSprite->GetEndV();
        SetTextureQuad(aStartU, aStartV, aEndU, aEndV);
    }
}

void FDrawQuad::Rotate(float pDegrees, float pCenterX, float pCenterY) {
    if (pDegrees != 0.0f) {
        pDegrees = pDegrees * D_R;
        float aX = 0.0f;
        float aY = 0.0f;
        float aDist = 0.0f;
        float aPivot = 0.0f;
        for (int i=0;i<4;i++) {
            aX = pCenterX - mVertex[i].mX;
            aY = pCenterY - mVertex[i].mY;
            aDist = aX * aX + aY * aY;
            if (aDist > SQRT_EPSILON) {
                aDist = sqrtf(aDist);
                aX /= aDist;
                aY /= aDist;
            }
            aPivot = (pDegrees - atan2f(aX, aY));
            mVertex[i].mX = (sinf(aPivot)) * aDist + pCenterX;
            mVertex[i].mY = (-cosf(aPivot)) * aDist + pCenterY;
        }
    }
}


void FDrawQuad::Translate(float pX, float pY) {
    if(pX != 0)for(int i=0;i<4;i++)mVertex[i].mX += pX;
    if(pY != 0)for(int i=0;i<4;i++)mVertex[i].mY += pY;
}

void FDrawQuad::Scale(float pScale) {
    for (int i=0;i<4;i++) {
        mVertex[i].mX *= pScale;
        mVertex[i].mY *= pScale;
        mVertex[i].mZ *= pScale;
    }
}

void FDrawQuad::Rotate(float pDegrees) {
    if (pDegrees != 0) {
        for (int i=0;i<4;i++) {
            if ((mVertex[i].mX != 0) || (mVertex[i].mY != 0)) {
                float aPivotRotation = FaceTarget(mVertex[i].mX, mVertex[i].mY);
                float aDist = mVertex[i].mX * mVertex[i].mX + mVertex[i].mY * mVertex[i].mY;
                if(aDist > SQRT_EPSILON)aDist = sqrtf(aDist);
                aPivotRotation += pDegrees;
                float aDirX = Sin(-aPivotRotation);
                float aDirY = Cos(-aPivotRotation);
                mVertex[i].mX = aDirX * (aDist);
                mVertex[i].mY = aDirY * (aDist);
            }
        }
    }
}

void FDrawQuad::ColorFlipH() {
    ColorSwap(0, 1);
    ColorSwap(2, 3);
}

void FDrawQuad::ColorFlipV() {
    ColorSwap(0, 2);
    ColorSwap(1, 3);
}

void FDrawQuad::ColorSwap(int pIndex1, int pIndex2) {
    if ((pIndex1 >= 0) && (pIndex1 < 4) && (pIndex2 >= 0) && (pIndex2 < 4)) {
        float aHoldR = mVertex[pIndex1].mR;
        float aHoldG = mVertex[pIndex1].mG;
        float aHoldB = mVertex[pIndex1].mB;
        float aHoldA = mVertex[pIndex1].mA;
        mVertex[pIndex1].mR = mVertex[pIndex2].mR;
        mVertex[pIndex1].mG = mVertex[pIndex2].mG;
        mVertex[pIndex1].mB = mVertex[pIndex2].mB;
        mVertex[pIndex1].mA = mVertex[pIndex2].mA;
        mVertex[pIndex2].mR = aHoldR;
        mVertex[pIndex2].mG = aHoldG;
        mVertex[pIndex2].mB = aHoldB;
        mVertex[pIndex2].mA = aHoldA;
    }
}

void FDrawQuad::ColorDarkenAll(float pPercent)
{
    for(int i=0;i<4;i++)
    {
        float aPercent = (1.0f - pPercent);
        mVertex[i].mR *= aPercent;
        mVertex[i].mG *= aPercent;
        mVertex[i].mB *= aPercent;
        mVertex[i].mA *= aPercent;
    }
}

void FDrawQuad::ColorLightenAll(float pPercent)
{
    for(int i=0;i<4;i++)
    {
        mVertex[i].mR = mVertex[i].mR + (1.0f - mVertex[i].mR) * pPercent;
        mVertex[i].mG = mVertex[i].mG + (1.0f - mVertex[i].mG) * pPercent;
        mVertex[i].mB = mVertex[i].mB + (1.0f - mVertex[i].mB) * pPercent;
        mVertex[i].mA = mVertex[i].mA + (1.0f - mVertex[i].mA) * pPercent;
    }
}




void FDrawQuad::ResetColor(float pAlpha)
{
    for(int i=0;i<4;i++)
    {
        mVertex[i].mR = 1.0f;
        mVertex[i].mG = 1.0f;
        mVertex[i].mB = 1.0f;
        mVertex[i].mA = pAlpha;
    }
}

void FDrawQuad::ResetColor(float pRed, float pGreen, float pBlue, float pAlpha)
{
    for(int i=0;i<4;i++)
    {
        mVertex[i].mR = pRed;
        mVertex[i].mG = pGreen;
        mVertex[i].mB = pBlue;
        mVertex[i].mA = pAlpha;
    }
}

void FDrawQuad::SetHexRGB(int pCorner, unsigned int pHexColor)
{
    if((pCorner >= 0) && (pCorner < 4))
    {
        mVertex[pCorner].mR = ((float)((((unsigned int)(pHexColor))>>16)&0xFF)) / (255.0f);
        mVertex[pCorner].mG = ((float)((((unsigned int)(pHexColor))>>8)&0xFF)) / (255.0f);
        mVertex[pCorner].mB = ((float)(((unsigned int)(pHexColor))&0xFF)) / (255.0f);
    }
}

void FDrawQuad::SetHexRGBA(int pCorner, unsigned int pHexColor)
{
    if((pCorner >= 0) && (pCorner < 4))
    {
        mVertex[pCorner].mR = ((float)((((unsigned int)(pHexColor))>>16)&0xFF)) / (255.0f);
        mVertex[pCorner].mG = ((float)((((unsigned int)(pHexColor))>>8)&0xFF)) / (255.0f);
        mVertex[pCorner].mB = ((float)(((unsigned int)(pHexColor))&0xFF)) / (255.0f);
        mVertex[pCorner].mA = ((float)((((unsigned int)(pHexColor))>>24)&0xFF)) / (255.0f);
    }
}

void FDrawQuad::SetHexRGB(unsigned int pHexColor)
{
    float aR = ((float)((((unsigned int)(pHexColor))>>16)&0xFF)) / (255.0f);
    float aG = ((float)((((unsigned int)(pHexColor))>>8)&0xFF)) / (255.0f);
    float aB = ((float)(((unsigned int)(pHexColor))&0xFF)) / (255.0f);
    
    for(int i=0;i<4;i++)
    {
        mVertex[i].mR = aR;
        mVertex[i].mG = aG;
        mVertex[i].mB = aB;
    }
}

void FDrawQuad::SetHexRGBA(unsigned int pHexColor)
{
    float aR = ((float)((((unsigned int)(pHexColor))>>16)&0xFF)) / (255.0f);
    float aG = ((float)((((unsigned int)(pHexColor))>>8)&0xFF)) / (255.0f);
    float aB = ((float)(((unsigned int)(pHexColor))&0xFF)) / (255.0f);
    float aA = ((float)((((unsigned int)(pHexColor))>>24)&0xFF)) / (255.0f);
    
    for(int i=0;i<4;i++)
    {
        mVertex[i].mR = aR;
        mVertex[i].mG = aG;
        mVertex[i].mB = aB;
        mVertex[i].mA = aA;
    }
}

void FDrawQuad::ColorMultiply(float pRed, float pGreen, float pBlue, float pAlpha)
{
    for(int i=0;i<4;i++)
    {
        mVertex[i].mR *= pRed;
        mVertex[i].mG *= pGreen;
        mVertex[i].mB *= pBlue;
        mVertex[i].mA *= pAlpha;
    }
}

void FDrawQuad::ColorMultiplyAlpha(float pAlpha)
{
    for(int i=0;i<4;i++)
    {
        mVertex[i].mA *= pAlpha;
    }
}

bool FDrawQuad::ContainsPoint(float pX, float pY)
{
    bool aResult = false;
    
    
    for(int aStart=0,aEnd=3;aStart<4;aEnd=aStart++)
    {
        if((((mVertex[aStart].mY <= pY) && (pY < mVertex[aEnd].mY))||
            ((mVertex[aEnd].mY <= pY) && (pY < mVertex[aStart].mY)))&&
           (pX < (mVertex[aEnd].mX - mVertex[aStart].mX) * (pY - mVertex[aStart].mY)
            / (mVertex[aEnd].mY - mVertex[aStart].mY) + mVertex[aStart].mX))
        {
            aResult = !aResult;
        }
    }
    
    return aResult;
}

void FDrawQuad::SetTextureAspectFit(FSprite *pSprite) {
    if(pSprite) {
        float aRectWidth = (mVertex[3].mX - mVertex[0].mX);
        float aRectHeight = (mVertex[3].mY - mVertex[0].mY);
        float aImageWidth = pSprite->mWidth;
        float aImageHeight = pSprite->mHeight;
        float aImageStartU = (pSprite->GetStartU());
        float aImageStartV = (pSprite->GetStartV());
        float aImageEndU = (pSprite->GetEndU());
        float aImageEndV = (pSprite->GetEndV());
        float aRangeU = (aImageEndU - aImageStartU);
        float aRangeV = (aImageEndV - aImageStartV);
        float aSizeEpsilon = 0.5f;
        SetTextureQuad(aImageStartU, aImageStartV, aImageEndU, aImageEndV);
        if((aRectWidth >= aSizeEpsilon) && (aRectHeight >= aSizeEpsilon) && (aImageWidth >= aSizeEpsilon) && (aImageHeight >= aSizeEpsilon))
        {
            float aTextureEpsilon = 0.01f;
            if((aRangeU > aTextureEpsilon) && (aRangeV > aTextureEpsilon))
            {
                if((aRectWidth / aRectHeight) > (aImageWidth / aImageHeight))
                {
                    float aNewWidth = aImageWidth * (aRectHeight / aImageHeight);
                    float aCenterX = mVertex[0].mX + aRectWidth / 2.0f;
                    SetRect(aCenterX - aNewWidth / 2.0f, mVertex[0].mY, aNewWidth, aRectHeight);
                }
                else
                {
                    float aNewHeight = aImageHeight * (aRectWidth / aImageWidth);
                    float aCenterY = mVertex[0].mY + aRectHeight / 2.0f;
                    SetRect(mVertex[0].mX, aCenterY - aNewHeight / 2.0f, aRectWidth, aNewHeight);
                }
            }
        }
    }
}

void FDrawQuad::SetTextureAspectFill(FSprite *pSprite)
{
    if(pSprite)
    {
        float aRectWidth = (mVertex[3].mX - mVertex[0].mX);
        float aRectHeight = (mVertex[3].mY - mVertex[0].mY);
        float aImageWidth = pSprite->mWidth;
        float aImageHeight = pSprite->mHeight;
        float aImageStartU = (pSprite->GetStartU());
        float aImageStartV = (pSprite->GetStartV());
        float aImageEndU = (pSprite->GetEndU());
        float aImageEndV = (pSprite->GetEndV());
        float aRangeU = (aImageEndU - aImageStartU);
        float aRangeV = (aImageEndV - aImageStartV);
        float aSizeEpsilon = 0.5f;
        SetTextureQuad(aImageStartU, aImageStartV, aImageEndU, aImageEndV);
        if((aRectWidth >= aSizeEpsilon) && (aRectHeight >= aSizeEpsilon) && (aImageWidth >= aSizeEpsilon) && (aImageHeight >= aSizeEpsilon))
        {
            float aTextureEpsilon = 0.01f;
            if((aRangeU > aTextureEpsilon) && (aRangeV > aTextureEpsilon))
            {
                if((aRectWidth / aRectHeight) < (aImageWidth / aImageHeight))
                {
                    float aExpandedWidth = aImageWidth * (aRectHeight / aImageHeight);
                    float aPercent = 1.0 - ((aExpandedWidth - (aRectWidth)) / aExpandedWidth);
                    float aCenterU = aImageStartU + (aImageEndU - aImageStartU) / 2.0;
                    float aPunchU = (aRangeU * aPercent) / 2.0;
                    aImageStartU = aCenterU - aPunchU;
                    aImageEndU = aCenterU + aPunchU;
                    SetTextureQuad(aImageStartU, aImageStartV, aImageEndU, aImageEndV);
                }
                else
                {
                    float aExpandedHeight = aImageHeight * (aRectWidth / aImageWidth);
                    float aPercent = 1.0 - ((aExpandedHeight - (aRectHeight)) / aExpandedHeight);
                    float aCenterV = aImageStartV + (aImageEndV - aImageStartV) / 2.0;
                    float aPunchV = (aRangeV * aPercent) / 2.0;
                    aImageStartV = aCenterV - aPunchV;
                    aImageEndV = aCenterV + aPunchV;
                    SetTextureQuad(aImageStartU, aImageStartV, aImageEndU, aImageEndV);
                }
            }
        }
    }
}

FDrawQuadGrid::FDrawQuadGrid() {
    mXYZ = NULL;
    mUVW = NULL;
    mRGBA = NULL;
    
    mXYZBase = NULL;
    mUVWBase = NULL;
    mRGBABase = NULL;
    
    mWidth = 0;
    mHeight = 0;
    
    mSprite = NULL;
}

FDrawQuadGrid::~FDrawQuadGrid() {
    Clear();
}

void FDrawQuadGrid::Draw(FSprite *pSprite) {
    
    int aHeight1 = (mHeight - 1);
    
    for (int n=0;n<aHeight1;n++){
        mNodeList.Reset();
        
        int aWriteIndex = 0;
        
        int aShift3Y1 = n * 3;
        int aShift4Y1 = n * 4;
        
        int aShift3Y2 = (n + 1) * 3;
        int aShift4Y2 = (n + 1) * 4;
        
        for (int i=0;i<mWidth;i++) {
            mNodeList.SetXYZ(aWriteIndex, mXYZ[i][aShift3Y2], mXYZ[i][aShift3Y2 + 1], mXYZ[i][aShift3Y2 + 2]);
            mNodeList.SetUVW(aWriteIndex, mUVW[i][aShift3Y2], mUVW[i][aShift3Y2 + 1], mUVW[i][aShift3Y2 + 2]);
            mNodeList.SetRGBA(aWriteIndex, mRGBA[i][aShift4Y2], mRGBA[i][aShift4Y2 + 1], mRGBA[i][aShift4Y2 + 2], mRGBA[i][aShift4Y2 + 3]);
            aWriteIndex++;
            mNodeList.SetXYZ(aWriteIndex, mXYZ[i][aShift3Y1], mXYZ[i][aShift3Y1 + 1], mXYZ[i][aShift3Y1 + 2]);
            mNodeList.SetUVW(aWriteIndex, mUVW[i][aShift3Y1], mUVW[i][aShift3Y1 + 1], mUVW[i][aShift3Y1 + 2]);
            mNodeList.SetRGBA(aWriteIndex, mRGBA[i][aShift4Y1], mRGBA[i][aShift4Y1 + 1], mRGBA[i][aShift4Y1 + 2], mRGBA[i][aShift4Y1 + 3]);
            aWriteIndex++;
        }
        
        if (pSprite == 0) {
            mNodeList.DrawTriStrips();
        } else {
            mNodeList.DrawTriStrips(pSprite);
        }
    }
}

void FDrawQuadGrid::Draw() {
    Draw(mSprite);
}

void FDrawQuadGrid::Size(int pWidth, int pHeight) {
    
    if ((pWidth == mWidth) && (pHeight == mHeight)) { return; }
    
    delete [] mXYZBase;
    delete [] mUVWBase;
    delete [] mRGBABase;
    
    delete [] mXYZ;
    delete [] mUVW;
    delete [] mRGBA;
    
    mWidth = pWidth;
    mHeight = pHeight;
    
    int aArea = pWidth * pHeight;
    
    mXYZBase = new float[aArea * 3];
    mUVWBase = new float[aArea * 3];
    mRGBABase = new float[aArea * 4];
    
    float *aXYZ = mXYZBase;
    float *aUVW = mUVWBase;
    float *aRGBA = mRGBABase;
    
    mXYZ = new float*[mWidth];
    mUVW = new float*[mWidth];
    mRGBA = new float*[mWidth];
    
    for (int i=0;i<mWidth;i++) {
        mXYZ[i] = aXYZ;
        mUVW[i] = aUVW;
        mRGBA[i] = aRGBA;
        aXYZ += (mHeight * 3);
        aUVW += (mHeight * 3);
        aRGBA += (mHeight * 4);
    }
}

void FDrawQuadGrid::Reset() {
    Clear();
}

void FDrawQuadGrid::Clear() {
    
    delete [] mXYZ;
    delete [] mUVW;
    delete [] mRGBA;
    
    mXYZ = NULL;
    mUVW = NULL;
    mRGBA = NULL;
    
    
    delete [] mXYZBase;
    delete [] mUVWBase;
    delete [] mRGBABase;
    
    mXYZBase = NULL;
    mUVWBase = NULL;
    mRGBABase = NULL;
    
    mWidth = 0;
    mHeight = 0;
    
    mRefresh = true;
}

void FDrawQuadGrid::SetSprite(FSprite *pSprite)
{
    mSprite = pSprite;
    mRefresh = true;
}


void FDrawQuadGrid::SetXYZ(int pGridX, int pGridY, float pX, float pY, float pZ) {
    
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridX < mWidth) && (pGridY < mHeight)) {
        int aIndexX = pGridX;
        int aIndexY = pGridY * 3;
        mXYZ[aIndexX][aIndexY + 0] = pX;
        mXYZ[aIndexX][aIndexY + 1] = pY;
        mXYZ[aIndexX][aIndexY + 2] = pZ;
        mRefresh = true;
    }
}

void FDrawQuadGrid::SetUVW(int pGridX, int pGridY, float pU, float pV, float pW) {
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridX < mWidth) && (pGridY < mHeight)) {
        int aIndexX = pGridX;
        int aIndexY = pGridY * 3;
        mUVW[aIndexX][aIndexY + 0] = pU;
        mUVW[aIndexX][aIndexY + 1] = pV;
        mUVW[aIndexX][aIndexY + 2] = pW;
        mRefresh = true;
    }
}

void FDrawQuadGrid::SetRGBA(int pGridX, int pGridY, float pRed, float pGreen, float pBlue, float pAlpha) {
    if ((pGridX >= 0) && (pGridY >= 0) && (pGridX < mWidth) && (pGridY < mHeight)) {
        int aIndexX = pGridX;
        int aIndexY = pGridY * 4;
        mRGBA[aIndexX][aIndexY + 0] = pRed;
        mRGBA[aIndexX][aIndexY + 1] = pGreen;
        mRGBA[aIndexX][aIndexY + 2] = pBlue;
        mRGBA[aIndexX][aIndexY + 3] = pAlpha;
        mRefresh = true;
    }
}

void FDrawQuadGrid::Generate9x9(FSprite &pSprite, float pX, float pY, float pWidth, float pHeight, float pInset) {
    Generate9x9(pSprite, pX, pY, pWidth, pHeight, pInset, pInset, pInset, pInset);
}

void FDrawQuadGrid::Generate9x9(FSprite &pSprite, float pX, float pY, float pWidth, float pHeight, float pInsetTop, float pInsetRight, float pInsetBottom, float pInsetLeft) {
    SetSprite(&pSprite);
    
    float aX[4];
    float aY[4];
    float aU[4];
    float aV[4];
    
    float aScale = 1.0f;
    
    float aWidth = pWidth * aScale;
    float aHeight = pHeight * aScale;
    
    float aQuadInsetLeft = pInsetLeft * aScale;
    float aQuadInsetRight = pInsetRight * aScale;
    float aQuadInsetTop = pInsetTop * aScale;
    float aQuadInsetBottom = pInsetBottom * aScale;
    
    float aQuadRight = pX + aWidth;
    float aQuadBottom = pY + aHeight;
    
    
    float aStartU = pSprite.mTextureRect.GetStartU();
    float aStartV = pSprite.mTextureRect.GetStartV();
    float aEndU = pSprite.mTextureRect.GetEndU();
    float aEndV = pSprite.mTextureRect.GetEndV();
    
    float aSpanU = (aEndU - aStartU);
    float aSpanV = (aEndV - aStartV);
    
    aX[0] = pX;
    aX[1] = pX + aQuadInsetLeft;
    aX[3] = aQuadRight;
    aX[2] = (aQuadRight - aQuadInsetRight);
    
    aY[0] = pY;
    aY[1] = pY + aQuadInsetTop;
    aY[3] = aQuadBottom;
    aY[2] = (aQuadBottom - aQuadInsetBottom);
    
    aU[0] = aStartU;
    aU[3] = aEndU;
    aV[0] = aStartV;
    aV[3] = aEndV;
    
    aU[1] = (pInsetLeft / pSprite.mWidth);
    aU[2] = ((mWidth - pInsetRight) / pSprite.mWidth);
    aV[1] = (pInsetTop / pSprite.mHeight);
    aV[2] = ((mHeight - pInsetBottom) / pSprite.mHeight);
    
    aU[1] = (aU[1] * aSpanU) + aStartU;
    aU[2] = (aU[2] * aSpanU) + aStartU;
    aV[1] = (aV[1] * aSpanV) + aStartV;
    aV[2] = (aV[2] * aSpanV) + aStartV;
    
    Size(4, 4);
    
    for (int i=0;i<4;i++) {
        for (int n=0;n<4;n++) {
            SetXYZ(i, n, aX[i], aY[i], 0.0f);
            SetUVW(i, n, aU[i], aV[i], 0.0f);
            //SetRGBA(i, n, 1.0f, 1.0f, 1.0f, 1.0f);
        }
    }
}

