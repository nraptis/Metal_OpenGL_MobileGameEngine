//
//  QuadSpewer.cpp
//  Digplex
//
//  Created by Nick Raptis on 9/23/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FDrawQuad.hpp"


FDrawQuad::FDrawQuad() {
    for (int i = 0; i < 4; i++) {
        mVertex[i].mR = 1.0f;
        mVertex[i].mG = 1.0f;
        mVertex[i].mB = 1.0f;
        mVertex[i].mA = 1.0f;
        mVertex[i].mX = 0.0f;
        mVertex[i].mY = 0.0f;
        mVertex[i].mZ = 0.0f;
        mVertex[i].mU = 0.0f;
        mVertex[i].mV = 0.0f;
        mVertex[i].mW = 0.0f;
    }
}

FDrawQuad::~FDrawQuad() { }

static GFX_MODEL_INDEX_TYPE cQuadIndex[6] = { 0, 1, 2, 1, 3, 2 };
void FDrawQuad::Draw(FSprite *pSprite) {
    if (pSprite) {
        if (pSprite->mTexture) {
            //TODO:
            /*
            Graphics::EnableTextureCoordinateArray();
            Graphics::EnableVertexArray();
            Graphics::EnableColorArray();
            float *aPtr = (float *)(&(mVertex[0]));
            Graphics::ArrayVertices(aPtr, sizeof(FDrawNode), 3);
            Graphics::ArrayCoords(aPtr + 3, sizeof(FDrawNode), 3);
            Graphics::ArrayColor(aPtr + 6, sizeof(FDrawNode), 4);
            Graphics::TextureEnable();
            Graphics::TextureBind(pSprite->mTexture);
            Graphics::DrawTriangles(cQuadIndex, 6);
            Graphics::DisableColorArray();
            */
        } else {
            Draw();
        }
    } else {
        Draw();
    }
}

void FDrawQuad::Draw(FSprite &pSprite) {
    Draw(&pSprite);
}

void FDrawQuad::Draw() {
    
    /*
    Graphics::EnableVertexArray();
    Graphics::EnableColorArray();
    Graphics::DisableTextureCoordinateArray();
    Graphics::TextureDisable();
    float *aPtr = (float *)(&(mVertex[0]));
    Graphics::ArrayVertices(aPtr, sizeof(FDrawNode), 3);
    Graphics::ArrayColor(aPtr + 6, sizeof(FDrawNode), 4);
    Graphics::DrawTriangles(cQuadIndex, 6);
    Graphics::TextureEnable();
    Graphics::DisableColorArray();
    Graphics::EnableTextureCoordinateArray();
    */
}

void FDrawQuad::DrawUncolored(FSprite *pSprite) {
    if (pSprite) {
        if (pSprite->mTexture) {
            
            /*
            Graphics::EnableTextureCoordinateArray();
            Graphics::EnableVertexArray();
            float *aPtr = (float *)(&(mVertex[0]));
            Graphics::ArrayVertices(aPtr, sizeof(FDrawNode), 3);
            Graphics::ArrayCoords(aPtr + 3, sizeof(FDrawNode), 3);
            Graphics::TextureEnable();
            Graphics::TextureBind(pSprite->mTexture);
            Graphics::DrawTriangles(cQuadIndex, 6);
            */
        } else {
            Draw();
        }
    } else {
        Draw();
    }
}

void FDrawQuad::DrawCorners() {
    for (int i=0;i<4;i++) {
        float aX = mVertex[i].mX;
        float aY = mVertex[i].mY;
        Graphics::OutlineRect(aX - 3, aY - 3, 7, 7, 2);
    }
}

void FDrawQuad::DrawOutline() {
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

void FDrawQuad::SetTextureRect(FSprite *pSprite, float pX, float pY, float pWidth, float pHeight) {
    if(pSprite == 0)return;
    float mStartU = pSprite->GetStartU();
    float mStartV = pSprite->GetStartU();
    float mEndU = pSprite->GetEndU();
    float mEndV = pSprite->GetEndV();
    float aSpriteWidth = pSprite->mWidth;
    float aSpriteHeight = pSprite->mHeight;
    float aSliceWidth = pWidth;
    float aSliceHeight = pHeight;
    if(aSliceWidth <= 2.0f)return;
    if(aSliceHeight <= 2.0f)return;
    if(aSpriteWidth <= 6.0f)return;
    if(aSpriteHeight <= 6.0f)return;
    float mImageStartX = pX;
    float mImageStartY = pY;
    float mImageEndX = pX + pWidth;
    float mImageEndY = pY + pHeight;
    float aPercentX1 = ((float)mImageStartX) / aSpriteWidth;
    float aPercentX2 = ((float)mImageEndX) / aSpriteWidth;
    float aPercentY1 = ((float)mImageStartY) / aSpriteHeight;
    float aPercentY2 = ((float)mImageEndY) / aSpriteHeight;
    float aBaseSpanU = (mEndU - mStartU);
    float aBaseSpanV = (mEndV - mStartV);
    float aStartU = mStartU + aBaseSpanU * aPercentX1;
    float aStartV = mStartV + aBaseSpanV * aPercentY1;
    float aEndU = mStartU + aBaseSpanU * aPercentX2;
    float aEndV = mStartV + aBaseSpanV * aPercentY2;
    SetTextureQuad(aStartU, aStartV, aEndU, aEndV);
}

void FDrawQuad::Rotate(float pDegrees, float pCenterX, float pCenterY) {
    if (pDegrees != 0.0f) {
        pDegrees = pDegrees * 0.01745329251994329576923690768488;
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
            mVertex[i].mX = (sin(aPivot)) * aDist + pCenterX;
            mVertex[i].mY = (-cos(aPivot)) * aDist + pCenterY;
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
        double aRectWidth = (mVertex[3].mX - mVertex[0].mX);
        double aRectHeight = (mVertex[3].mY - mVertex[0].mY);
        double aImageWidth = pSprite->mWidth;
        double aImageHeight = pSprite->mHeight;
        double aImageStartU = (double)(pSprite->GetStartU());
        double aImageStartV = (double)(pSprite->GetStartV());
        double aImageEndU = (double)(pSprite->GetEndU());
        double aImageEndV = (double)(pSprite->GetEndV());
        double aRangeU = (aImageEndU - aImageStartU);
        double aRangeV = (aImageEndV - aImageStartV);
        double aSizeEpsilon = 0.5f;
        SetTextureQuad(aImageStartU, aImageStartV, aImageEndU, aImageEndV);
        if((aRectWidth >= aSizeEpsilon) && (aRectHeight >= aSizeEpsilon) && (aImageWidth >= aSizeEpsilon) && (aImageHeight >= aSizeEpsilon))
        {
            double aTextureEpsilon = 0.01f;
            if((aRangeU > aTextureEpsilon) && (aRangeV > aTextureEpsilon))
            {
                if((aRectWidth / aRectHeight) > (aImageWidth / aImageHeight))
                {
                    double aNewWidth = aImageWidth * (aRectHeight / aImageHeight);
                    double aCenterX = mVertex[0].mX + aRectWidth / 2.0f;
                    SetRect(aCenterX - aNewWidth / 2.0f, mVertex[0].mY, aNewWidth, aRectHeight);
                }
                else
                {
                    double aNewHeight = aImageHeight * (aRectWidth / aImageWidth);
                    double aCenterY = mVertex[0].mY + aRectHeight / 2.0f;
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
        double aRectWidth = (mVertex[3].mX - mVertex[0].mX);
        double aRectHeight = (mVertex[3].mY - mVertex[0].mY);
        double aImageWidth = pSprite->mWidth;
        double aImageHeight = pSprite->mHeight;
        double aImageStartU = (double)(pSprite->GetStartU());
        double aImageStartV = (double)(pSprite->GetStartV());
        double aImageEndU = (double)(pSprite->GetEndU());
        double aImageEndV = (double)(pSprite->GetEndV());
        double aRangeU = (aImageEndU - aImageStartU);
        double aRangeV = (aImageEndV - aImageStartV);
        double aSizeEpsilon = 0.5f;
        SetTextureQuad(aImageStartU, aImageStartV, aImageEndU, aImageEndV);
        if((aRectWidth >= aSizeEpsilon) && (aRectHeight >= aSizeEpsilon) && (aImageWidth >= aSizeEpsilon) && (aImageHeight >= aSizeEpsilon))
        {
            double aTextureEpsilon = 0.01f;
            if((aRangeU > aTextureEpsilon) && (aRangeV > aTextureEpsilon))
            {
                if((aRectWidth / aRectHeight) < (aImageWidth / aImageHeight))
                {
                    double aExpandedWidth = aImageWidth * (aRectHeight / aImageHeight);
                    double aPercent = 1.0 - ((aExpandedWidth - (aRectWidth)) / aExpandedWidth);
                    double aCenterU = aImageStartU + (aImageEndU - aImageStartU) / 2.0;
                    double aPunchU = (aRangeU * aPercent) / 2.0;
                    aImageStartU = aCenterU - aPunchU;
                    aImageEndU = aCenterU + aPunchU;
                    SetTextureQuad(aImageStartU, aImageStartV, aImageEndU, aImageEndV);
                }
                else
                {
                    double aExpandedHeight = aImageHeight * (aRectWidth / aImageWidth);
                    double aPercent = 1.0 - ((aExpandedHeight - (aRectHeight)) / aExpandedHeight);
                    double aCenterV = aImageStartV + (aImageEndV - aImageStartV) / 2.0;
                    double aPunchV = (aRangeV * aPercent) / 2.0;
                    aImageStartV = aCenterV - aPunchV;
                    aImageEndV = aCenterV + aPunchV;
                    SetTextureQuad(aImageStartU, aImageStartV, aImageEndU, aImageEndV);
                }
            }
        }
    }
}


FDrawQuadRay::FDrawQuadRay()
{
    mStartWidth = 8.0f;
    mEndWidth = 8.0f;
    
    mStartPos = FVec2(0.0f, 0.0f);
    mEndPos = FVec2(5.0f, 0.0f);
    
    mDir = FVec2(1.0f, 0.0f);
    mNormal = FVec2(0.0f, 1.0f);
    
    mSprite = 0;
    
    mLength = 24.0f;
    mAngle = 90.0f;
    
    mStartWidth = 20.0f;
    mEndWidth = 12.0f;
}

FDrawQuadRay::~FDrawQuadRay()
{
    
}

void FDrawQuadRay::Draw(FSprite *pSprite)
{
    /*
     
     SetColor(1.0f, 0.0f, 0.0f);
     
     DrawRect(mStartPos.mX, mStartPos.mY, 8.0f, 8.0f);
     
     DrawLine(mStartPos.mX, mStartPos.mY, mEndPos.mX, mEndPos.mY);
     
     */
    
    FDrawQuad::Draw(pSprite);
    
}




void FDrawQuadRay::ComputeCorners()
{
    
    if(mLength > 0.25f)
    {
        mDir = AngleToVector(mAngle);
        mEndPos = mStartPos + (mDir * mLength);
        
        
        mNormal = FVec2(-mDir.mY, mDir.mX);
        
        
        float aStartWidth2 = mStartWidth / 2.0f;
        float aEndWidth2 = mEndWidth / 2.0f;
        
        
        if(mSprite)SetTextureQuad(mSprite->mTextureRect.GetStartU(), mSprite->mTextureRect.GetStartV(), mSprite->mTextureRect.GetEndU(), mSprite->mTextureRect.GetEndV());
        
        
        
        float aStartX1 = mStartPos.mX + mNormal.mX * aStartWidth2;
        float aStartY1 = mStartPos.mY + mNormal.mY * aStartWidth2;
        
        float aStartX2 = mStartPos.mX - mNormal.mX * aStartWidth2;
        float aStartY2 = mStartPos.mY - mNormal.mY * aStartWidth2;
        
        
        float aEndX1 = mEndPos.mX + mNormal.mX * aEndWidth2;
        float aEndY1 = mEndPos.mY + mNormal.mY * aEndWidth2;
        
        float aEndX2 = mEndPos.mX - mNormal.mX * aEndWidth2;
        float aEndY2 = mEndPos.mY - mNormal.mY * aEndWidth2;
        
        
        
        aStartX1 += mDir.mX * 20.0f;
        aStartY1 += mDir.mY * 20.0f;
        
        
        
        
        //SetQuad(aStartX1, aStartY1, aEndX1, aEndY1, aStartX2, aStartY2, aEndX2, aEndY2);
        SetQuad(aEndX1, aEndY1, aEndX2, aEndY2, aStartX1, aStartY1, aStartX2, aStartY2);
        
        
        //mVertex[0].mX = aStartX1;
        
        
        
    }
    
    /*
     float aDirX = Sin(mAngle);
     float aDirY =
     
     
     float aDiffX = mEndPos.mX - pPoint.mX;
     float aDiffY = pCenter.mY - pPoint.mY;
     
     float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
     
     if(aDist > 0.25f)
     {
     
     aDist=sqrtf(aDist);
     
     float aRotation = FaceTarget(aDiffX, aDiffY);
     aRotation = pDegrees + aRotation;
     
     //if(aRotation < -360.0f || aRotation > 360.0f)
     //{
     //    aRotation = fmodf(aRotation, 360.0f);
     //}
     
     aResult.mX = pCenter.mX + Sin(180.0f -aRotation) * pScale * aDist;
     aResult.mY = pCenter.mY + Cos(180.0f -aRotation) * pScale * aDist;
     
     }
     else
     {
     aResult = pPoint;
     
     aDiffX=0.0f;
     aDiffY=0.0f;
     
     aDist=0.0f;
     }
     return aResult;
     
     */
}

void FDrawQuadRay::SetStartPos(float pX, float pY)
{
    mStartPos = FVec2(pX, pY);
    ComputeCorners();
}

void FDrawQuadRay::SetStartPos(FVec2 pPos)
{
    mStartPos = pPos;
    ComputeCorners();
}

void FDrawQuadRay::SetEndPos(float pX, float pY)
{
    mStartPos = FVec2(pX, pY);
    ComputeCorners();
}

void FDrawQuadRay::SetEndPos(FVec2 pPos)
{
    mStartPos = pPos;
    ComputeCorners();
}

void FDrawQuadRay::SetSprite(FSprite *pSprite)
{
    mSprite = pSprite;
    ComputeCorners();
}


void FDrawQuadRay::SetAngle(float pDegrees)
{
    mAngle = pDegrees;
    ComputeCorners();
}

void FDrawQuadRay::SetLength(float pLength)
{
    mLength = pLength;
    ComputeCorners();
}

void FDrawQuadRay::SetWidthStart(float pWidth)
{
    mStartWidth = pWidth;
    ComputeCorners();
}

void FDrawQuadRay::SetWidthEnd(float pWidth)
{
    mEndWidth = pWidth;
    ComputeCorners();
}

void FDrawQuadRay::SetWidth(float pStartWidth, float pEndWidth)
{
    mStartWidth = pStartWidth;
    mEndWidth = pEndWidth;
    ComputeCorners();
}

void FDrawQuadRay::SetWidth(float pWidth)
{
    mStartWidth = pWidth;
    mEndWidth = pWidth;
    ComputeCorners();
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
    
    mXYZ = 0;
    mUVW = 0;
    mRGBA = 0;
    
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

FDrawQuadSnake::FDrawQuadSnake() {
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
    
    mSprite = 0;
    
    mWidthFactor = 1.0f;
    
    mLength = 0.0f;
    
    //mNodeList.mStrips = false;
    
    mRefresh = false;
}

FDrawQuadSnake::~FDrawQuadSnake()
{
    Clear();
}


void FDrawQuadSnake::Draw() {
    if (mRefresh) {
        Generate();
    }
    
    mNodeList.DrawTris(mSprite);
    //mQuadStrip.Draw(mSprite);
}

void FDrawQuadSnake::DrawMarkers()
{
    
    
    for(int i=0;i<mCount;i++)
    {
        /*
         float aX = mCenterX[i];
         float aY = mCenterY[i];
         
         Graphics::SetColor(1.0f, 0.0f, 0.0f);
         
         Graphics::DrawPoint(aX, aY, 8);
         
         Graphics::SetColor(0.0f, 0.0f, 0.0f);
         
         Graphics::DrawPoint(aX, aY, 6.0f);
         */
        
        
    }
    
    
    for(int i=0;i<mCount;i++)
    {
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

void FDrawQuadSnake::Reset()
{
    mCount = 0;
    mRefresh = true;
    
    mNodeList.Reset();
}

void FDrawQuadSnake::Clear()
{
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

void FDrawQuadSnake::Size(int pSize)
{
    
    if(pSize <= 0)
    {
        //what..
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
    
    
    
    for(int i=0;i<mCount;i++)aCenterX[i] = mCenterX[i];
    for(int i=0;i<mCount;i++)aCenterY[i] = mCenterY[i];
    
    for(int i=0;i<mCount;i++)aDirX[i] = mDirX[i];
    for(int i=0;i<mCount;i++)aDirY[i] = mDirY[i];
    
    for(int i=0;i<mCount;i++)aNormX[i] = mNormX[i];
    for(int i=0;i<mCount;i++)aNormY[i] = mNormY[i];
    
    for(int i=0;i<mCount;i++)aU[i] = mU[i];
    for(int i=0;i<mCount;i++)aV[i] = mV[i];
    
    for(int i=0;i<mCount;i++)aDist[i] = mDist[i];
    for(int i=0;i<mCount;i++)aPercent[i] = mPercent[i];
    
    //
    
    
    
    for(int i=mCount;i<mSize;i++)aCenterX[i] = 0.0f;
    for(int i=mCount;i<mSize;i++)aCenterY[i] = 0.0f;
    
    for(int i=mCount;i<mSize;i++)aDirX[i] = 0.0f;
    for(int i=mCount;i<mSize;i++)aDirY[i] = 0.0f;
    
    for(int i=mCount;i<mSize;i++)aNormX[i] = 0.0f;
    for(int i=mCount;i<mSize;i++)aNormY[i] = 0.0f;
    
    for(int i=mCount;i<mSize;i++)aU[i] = 0.0f;
    for(int i=mCount;i<mSize;i++)aV[i] = 0.0f;
    
    for(int i=mCount;i<mSize;i++)aDist[i] = 0.0f;
    for(int i=mCount;i<mSize;i++)aPercent[i] = 1.0f;
    
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

void FDrawQuadSnake::SetPoint(int pIndex, float pX, float pY)
{
    mRefresh = true;
    
    if(pIndex >= mSize)
    {
        Size(pIndex + pIndex / 2 + 1);
    }
    
    mCenterX[pIndex] = pX;
    mCenterY[pIndex] = pY;
    
    if(pIndex > mCount)
    {
        mCount = pIndex;
    }
}

void FDrawQuadSnake::AddPoint(float pX, float pY)
{
    mRefresh = true;
    
    if(mCount >= mSize)
    {
        Size(mCount + mCount / 2 + 1);
    }
    
    mCenterX[mCount] = pX;
    mCenterY[mCount] = pY;
    
    mCount++;
}

void FDrawQuadSnake::SetSprite(FSprite *pSprite)
{
    if(mSprite != pSprite)
    {
        if(mSprite)
        {
            //Log("Snake UV [%f %f %f %f]\n", pSprite->GetStartU(), pSprite->GetStartV(), pSprite->GetEndU(), pSprite->GetEndV());
        }
        
        mSprite = pSprite;
        mRefresh = true;
    }
    
    
    
    
}

void FDrawQuadSnake::Generate()
{
    mLength = 0.0f;
    mRefresh = false;
    
    
    if(mCount < 2)return;
    if(mSprite == 0)return;
    
    float aImageWidth = mSprite->mHeight;
    float aPushWidth = mSprite->mWidth / 2.0f;
    
    
    aPushWidth *= mWidthFactor;
    aImageWidth *= mWidthFactor;
    
    if((aImageWidth < 1.0f) || (aPushWidth < 1.0f))return;
    
    
    float aLastX = mCenterX[0];
    float aLastY = mCenterY[0];
    
    float aX = aLastX;
    float aY = aLastY;
    
    float aLastDirX = 0.0f;
    float aLastDirY = -1.0f;
    
    float aLastNormX = -(aLastDirY);
    float aLastNormY = aLastDirX;
    
    float aDirX = aLastDirX;
    float aDirY = aLastDirY;
    
    float aDiffX = 0.0f;
    float aDiffY = 0.0f;
    float aDist = 0.1f;
    
    
    int aIndex = 0;
    
    mDist[0] = 0.0f;
    
    //bool aLastUWasEnd = false;
    
    for(int i=1;i<mCount;i++)
    {
        aX = mCenterX[i];
        aY = mCenterY[i];
        
        aDiffX = aX - aLastX;
        aDiffY = aY - aLastY;
        
        aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if(aDist > SQRT_EPSILON)
        {
            aDist = sqrtf(aDist);
            
            aDirX = aDiffX / aDist;
            aDirY = aDiffY / aDist;
        }
        else
        {
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
        
        aLastDirX = aDirX;
        aLastDirY = aDirY;
    }
    
    mDirX[aIndex] = aDirX;
    mDirY[aIndex] = aDirY;
    
    mNormX[aIndex] = -aDirY;
    mNormY[aIndex] = aDirX;

    if(mLength < 0.1f)mLength = 1.0f;

    float aStartPercentU = 0.0f;

    float aPercent = 0.0f;
    float aLastPercent = 0.0f;

    float aStartU = mSprite->GetStartU();
    float aStartV = mSprite->GetStartV();
    float aEndU = mSprite->GetEndU();
    float aEndV = mSprite->GetEndV();

    float aSpanU = (aEndU - aStartU);

    aDist = aStartPercentU * aImageWidth;

    float aU =  aStartU + (aSpanU * aStartPercentU);
    float aLastU = aU;
    
    mU[0] = aU;

    for (int i=1;i<mCount;i++) {
        aDist += mDist[i];
        if (aDist > aImageWidth) {
            aDist -= aImageWidth;
        }
        aPercent = aDist / aImageWidth;
        mU[i] = aPercent;
    }

    float aNormX = 0.0f;
    float aNormY = 0.0f;
    
    
    
    
    //Smooth out the norms here..
    
    mNodeList.Reset();
    
    int aStripIndex = 0;
    
    float aX1 = mCenterX[0] + mNormX[0] * aPushWidth;
    float aY1 = mCenterY[0] + mNormY[0] * aPushWidth;
    
    float aX2 = mCenterX[0] - mNormX[0] * aPushWidth;
    float aY2 = mCenterY[0] - mNormY[0] * aPushWidth;
    
    
    float aLastX1 = aX1;
    float aLastY1 = aY1;
    
    float aLastX2 = aX2;
    float aLastY2 = aY2;
    
    //float aLastU = mU[0];
    
    
    aDirX = mDirX[0];
    aDirY = mDirY[0];
    
    aLastDirX = aDirX;
    aLastDirY = aDirY;
    
    aLastNormX = -(aLastDirY);
    aLastNormY = aLastDirX;
    
    
    //float aStartV = 0.0f;
    //float aEndV = 1.0f;
    
    
    
    aX = mCenterX[0];
    aY = mCenterY[0];
    
    aLastX = aX;
    aLastY = aY;
    
    
    //aTextureU = mU[0];
    //aLastU = aTextureU;
    
    
    aLastPercent = aStartPercentU;
    aPercent = aStartPercentU;
    aDist = aStartPercentU * aImageWidth;
    float aLastDist = aDist;
    
    for(int i=1;i<mCount;i++)
    {
        aX = mCenterX[i];
        aY = mCenterY[i];
        
        aNormX = mNormX[i];
        aNormY = mNormY[i];
        
        //aU = mU[i];
        aU = aStartU + (aSpanU * mU[i]);
        
        
        
        aX1 = mCenterX[i] + aNormX * aPushWidth;
        aY1 = mCenterY[i] + aNormY * aPushWidth;
        
        aX2 = mCenterX[i] - aNormX * aPushWidth;
        aY2 = mCenterY[i] - aNormY * aPushWidth;
        
        aDist += mDist[i];
        
        
        
        aPercent = aDist / aImageWidth;
        //mU[i] = aPercent;
        
        //mU[i] = aStartU + (aSpanU * aPercent);
        mU[i] = aU;
        
        
        
        if(aDist > aImageWidth)
        {
            
            
            
            float aDistanceDifference = (aDist - aLastDist) * 10000.0f;
            
            float aImageWidthDifference = (aImageWidth - aLastDist) * 10000.0f;
            
            if(aDistanceDifference < 0.001f)aDistanceDifference = 0.001f;
            
            if(aImageWidthDifference < 0.001f)aImageWidthDifference = 0.001f;
            
            aPercent = ((aImageWidthDifference) / (aDistanceDifference));
            
            float aInsertCenterX = aLastX + (aX - aLastX) * aPercent;
            float aInsertCenterY = aLastY + (aY - aLastY) * aPercent;
            
            
            float aInsertNormX = aLastNormX;// aLastNormX + (aNormX - aLastNormX) * aPercent;
            float aInsertNormY = aLastNormY;// aLastNormY + (aNormY - aLastNormY) * aPercent;
            
            if(aPercent > 0.5f)
            {
                aInsertNormX = aNormX;
                aInsertNormY = aNormY;
            }
            
            float aInsertX1 = aInsertCenterX + aInsertNormX * aPushWidth;
            float aInsertY1 = aInsertCenterY + aInsertNormY * aPushWidth;
            
            float aInsertX2 = aInsertCenterX - aInsertNormX * aPushWidth;
            float aInsertY2 = aInsertCenterY - aInsertNormY * aPushWidth;
            
            
            
            
            mNodeList.SetXY(aStripIndex, aLastX1, aLastY1);
            mNodeList.SetUV(aStripIndex, aLastU, aEndV);aStripIndex++;
            
            //Top Right
            mNodeList.SetXY(aStripIndex, aInsertX1, aInsertY1);
            mNodeList.SetUV(aStripIndex, aEndU, aEndV);aStripIndex++;
            
            //Bottom Left
            mNodeList.SetXY(aStripIndex, aLastX2, aLastY2);
            mNodeList.SetUV(aStripIndex, aLastU, aStartV);aStripIndex++;
            
            
            
            
            
            //Bottom Left
            mNodeList.SetXY(aStripIndex, aLastX2, aLastY2);
            mNodeList.SetUV(aStripIndex, aLastU, aStartV);aStripIndex++;
            
            //Top Right
            mNodeList.SetXY(aStripIndex, aInsertX1, aInsertY1);
            mNodeList.SetUV(aStripIndex, aEndU, aEndV);aStripIndex++;
            
            //Bottom Right
            mNodeList.SetXY(aStripIndex, aInsertX2, aInsertY2);
            mNodeList.SetUV(aStripIndex, aEndU, aStartV);aStripIndex++;
            ////////////
            //////////////////////////////////////
            
            
            //aLastU = 0.0f;
            aLastU = aStartU;
            
            
            aLastX1 = aInsertX1;
            aLastY1 = aInsertY1;
            
            aLastX2 = aInsertX2;
            aLastY2 = aInsertY2;
            
            aLastNormX = aInsertNormX;
            aLastNormY = aInsertNormY;
            
            aLastX = aInsertCenterX;
            aLastY = aInsertCenterY;
            
            aDist -= aImageWidth;
        }
        
        
        //////////// - Triangle 1 - /////////
        ////////////
        ////////////
        
        //Top Left
        mNodeList.SetXY(aStripIndex, aLastX1, aLastY1);
        mNodeList.SetUV(aStripIndex, aLastU, aEndV);aStripIndex++;
        
        //Top Right
        mNodeList.SetXY(aStripIndex, aX1, aY1);
        mNodeList.SetUV(aStripIndex, aU, aEndV);aStripIndex++;
        
        //Bottom Left
        mNodeList.SetXY(aStripIndex, aLastX2, aLastY2);
        mNodeList.SetUV(aStripIndex, aLastU, aStartV);aStripIndex++;
        
        ////////////
        //////////// - Triangle 2 - /////////
        ////////////
        
        //Bottom Left
        mNodeList.SetXY(aStripIndex, aLastX2, aLastY2);
        mNodeList.SetUV(aStripIndex, aLastU, aStartV);aStripIndex++;
        
        //Top Right
        mNodeList.SetXY(aStripIndex, aX1, aY1);
        mNodeList.SetUV(aStripIndex, aU, aEndV);aStripIndex++;
        
        //Bottom Right
        mNodeList.SetXY(aStripIndex, aX2, aY2);
        mNodeList.SetUV(aStripIndex, aU, aStartV);aStripIndex++;
        
        ////////////
        ////////////
        //////////////////////////////////////

        aLastX = aX;
        aLastY = aY;
        aLastX1 = aX1;
        aLastY1 = aY1;
        aLastX2 = aX2;
        aLastY2 = aY2;
        aLastNormX = aNormX;
        aLastNormY = aNormY;
        aLastU = aU;
        aLastDist = aDist;
        aLastPercent = aPercent;

        if(aLastU == 1.0f) {
            aLastU = 0.0f;
        }
    }
}
