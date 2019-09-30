//
//  PrimitiveMesh.cpp
//  2015 Gnome Launcher
//
//  Created by Nick Raptis on 11/30/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FPrimitive.hpp"
#include "FSprite.hpp"
#include "FFile.hpp"
#include "core_includes.h"

/*
 bool PolyPath::ContainsPoint(float pX, float pY)
 {
 bool aResult = false;
 
 if(mPointCount > 1)
 {
 for(int aStart=0,aEnd=mPointCount-1;aStart<mPointCount;aEnd=aStart++)
 {
 float aStartX = mX[aStart] + mCenterX;
 float aStartY = mY[aStart] + mCenterY;
 float aEndX = mX[aEnd] + mCenterX;
 float aEndY = mY[aEnd] + mCenterY;
 
 if((((aStartY<=pY) && (pY<aEndY))||
 ((aEndY<=pY) && (pY<aStartY)))&&
 (pX < (aEndX - aStartX)*(pY - aStartY)
 /(aEndY - aStartY) + aStartX))
 {
 aResult=!aResult;
 }
 }
 }
 
 return aResult;
 }
 
 float PolygonPath::Get(float pPercent, float *pArray)
 {
 if(mChanged==true)Finalize();
 
 float aResult=0;
 
 if(mCount==1)
 {
 aResult=pArray[0];
 }
 if(mCount>1)
 {
 if(pPercent<0||pPercent>1)
 {
 pPercent=fmodf(pPercent,1);
 if(pPercent<0)pPercent+=1;
 }
 
 if(pPercent<0)
 {
 aResult=pArray[0];
 }
 else if(pPercent>1)
 {
 aResult=pArray[mCount-1];
 }
 else
 {
 int i=0;
 for(i=0;i<mCount;i++)
 {
 if(mPercent[i]>=pPercent)break;
 }
 
 
 
 //if(i<1)i++;
 if(i==mCount)i--;
 
 int aStartIndex;
 int aEndIndex;
 
 float aStartPercent=0;
 float aEndPercent=0;
 
 if(i<1)
 {
 aStartIndex=mCount-1;
 aEndIndex=0;
 
 aStartPercent=0;
 aEndPercent=mPercent[0];
 }
 else
 {
 aStartIndex=i-1;
 aEndIndex=i;
 
 aStartPercent=mPercent[aStartIndex];
 aEndPercent=mPercent[aEndIndex];
 }
 
 
 
 //Log("Input P: %f (%d - %d) (%f - %f)   \n", pPercent, aStartIndex, aEndIndex, aStartPercent, aEndPercent);
 
 if(pPercent<aStartPercent)
 {
 aResult=pArray[aStartIndex];
 }
 else if(pPercent>aEndPercent)
 {
 aResult=pArray[aEndIndex];
 }
 else
 {
 float aLength=aEndPercent-aStartPercent;
 if(aLength>0.001f)
 {
 float aPercent = (pPercent-aStartPercent) / (aLength);
 
 if(aPercent>1)aPercent=1;
 if(aPercent<0)aPercent=0;
 
 aResult=pArray[aStartIndex]+(pArray[aEndIndex]-pArray[aStartIndex])*aPercent;
 }
 else
 {
 aResult=pArray[aStartIndex];
 }
 }
 }
 
 }
 return aResult;
 }
 */


FDrawNodeList::FDrawNodeList() {
    
    mIndexList.Clear();
    
    mNodeSize = 0;
    mCountNodes = 0;
    mData = 0;
    
    mEnabledTexture = true;
    mEnabledColor = true;
    
    mCountXYZ = 0;
    mCountUVW = 0;
    mCountC = 0;
    
    
}

FDrawNodeList::~FDrawNodeList() {
    Clear();
}

void FDrawNodeList::Size(int pSize)
{
    if(pSize > 0)
    {
        FDrawNode *aVertex = new FDrawNode[pSize];
        
        if(mCountNodes > pSize)mCountNodes = pSize;
        
        for(int i=0;i<mCountNodes;i++)
        {
            aVertex[i].mX = mData[i].mX;
            aVertex[i].mY = mData[i].mY;
            aVertex[i].mZ = mData[i].mZ;
            
            aVertex[i].mU = mData[i].mU;
            aVertex[i].mV = mData[i].mV;
            aVertex[i].mW = mData[i].mW;
            
            aVertex[i].mR = mData[i].mR;
            aVertex[i].mG = mData[i].mG;
            aVertex[i].mB = mData[i].mB;
            aVertex[i].mA = mData[i].mA;
        }
        
        for(int i=mCountNodes;i<pSize;i++)
        {
            aVertex[i].mX = 0.0f;
            aVertex[i].mY = 0.0f;
            aVertex[i].mZ = 0.0f;
            
            aVertex[i].mU = 0.0f;
            aVertex[i].mV = 0.0f;
            aVertex[i].mW = 0.0f;
            
            //float aRedness = ((float)i) / 8.0f;
            //aRedness = fmodf(aRedness, 1.0f);
            
            aVertex[i].mR = 1.0f;
            aVertex[i].mG = 1.0f;
            aVertex[i].mB = 1.0f;
            aVertex[i].mA = 1.0f;
        }
        
        delete [] mData;
        
        mData = aVertex;
        mNodeSize = pSize;
        
        int aIndexListSize = mIndexList.mSize;
        if (aIndexListSize < pSize) {
            mIndexList.Size(pSize);
            for (int i=0;i<mIndexList.mSize;i++) {
                mIndexList.mIndex[i] = (GFX_MODEL_INDEX_TYPE)i;
            }
            mIndexList.mCount = pSize;
        }
    } else {
        delete [] mData;
        mNodeSize = 0;
        mCountNodes = 0;
        mIndexList.RemoveAll();
    }
}

void FDrawNodeList::Reset() {
    mCountNodes = 0;
}

void FDrawNodeList::Clear()
{
    delete [] mData;
    mData = 0;
    
    mNodeSize = 0;
    mCountNodes = 0;
}

void FDrawNodeList::SetX(int pIndex, float pX)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mX = pX;
    }
    else
    {
        SetXYZ(pIndex, pX, 0.0f, 0.0f);
    }
}

void FDrawNodeList::SetY(int pIndex, float pY) {
    if ((pIndex >= 0) && (pIndex < mCountNodes)) {
        mData[pIndex].mY = pY;
    } else {
        SetXYZ(pIndex, 0.0f, pY, 0.0f);
    }
}

void FDrawNodeList::SetZ(int pIndex, float pZ)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mZ = pZ;
    }
    else
    {
        SetXYZ(pIndex, 0.0f, 0.0f, pZ);
    }
}

void FDrawNodeList::SetU(int pIndex, float pU)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mU = pU;
    }
    else
    {
        SetUVW(pIndex, pU, 0.0f, 0.0f);
    }
}

void FDrawNodeList::SetV(int pIndex, float pV)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mV = pV;
    }
    else
    {
        SetUVW(pIndex, 0.0f, pV, 0.0f);
    }
}

void FDrawNodeList::SetW(int pIndex, float pW)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mW = pW;
    }
    else
    {
        SetUVW(pIndex, 0.0f, 0.0f, pW);
    }
}

void FDrawNodeList::SetR(int pIndex, float pRed)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mR = pRed;
    }
    else
    {
        SetRGBA(pIndex, pRed, 1.0f, 1.0f, 1.0f);
    }
}


void FDrawNodeList::SetG(int pIndex, float pGreen)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mG = pGreen;
    }
    else
    {
        SetRGBA(pIndex, 1.0, pGreen, 1.0f, 1.0f);
    }
}

void FDrawNodeList::SetB(int pIndex, float pBlue)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mB = pBlue;
    }
    else
    {
        SetRGBA(pIndex, 1.0f, 1.0f, pBlue, 1.0f);
    }
}

void FDrawNodeList::SetA(int pIndex, float pAlpha)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mA = pAlpha;
    }
    else
    {
        SetRGBA(pIndex, 1.0f, 1.0f, 1.0f, pAlpha);
    }
}

void FDrawNodeList::SetXY(int pIndex, float pX, float pY)
{
    if((pIndex >= 0) && (pIndex < mCountNodes))
    {
        mData[pIndex].mX = pX;
        mData[pIndex].mY = pY;
    }
    else
    {
        SetXYZ(pIndex, pX, pY, 0.0f);
    }
}

void FDrawNodeList::SetUV(int pIndex, float pU, float pV)
{
    SetUVW(pIndex, pU, pV, 0.0f);
}


void FDrawNodeList::Add(FDrawNode *pNode)
{
    if(pNode)
    {
        Add(pNode->mX, pNode->mY, pNode->mZ, pNode->mU, pNode->mV, pNode->mW, pNode->mR, pNode->mG, pNode->mB, pNode->mA);
    }
}

void FDrawNodeList::Add(float pX, float pY, float pZ, float pU, float pV, float pW, float pRed, float pGreen, float pBlue, float pAlpha)
{
    
    Set(mCountNodes, pX, pY, pZ, pU, pV, pW, pRed, pGreen, pBlue, pAlpha);
}

void FDrawNodeList::Set(int pIndex, float pX, float pY, float pZ, float pU, float pV, float pW, float pRed, float pGreen, float pBlue, float pAlpha)
{
    if(pIndex >= 0)
    {
        if(pIndex >= mNodeSize)
        {
            int aSize = (pIndex + (pIndex / 2) + 2);
            Size(aSize);
        }
        
        mData[pIndex].mX = pX;
        mData[pIndex].mY = pY;
        mData[pIndex].mZ = pZ;
        
        mData[pIndex].mU = pW;
        mData[pIndex].mV = pV;
        mData[pIndex].mW = pW;
        
        mData[pIndex].mR = pRed;
        mData[pIndex].mG = pGreen;
        mData[pIndex].mB = pBlue;
        mData[pIndex].mA = pAlpha;
        
        if(pIndex >= mCountNodes)
        {
            mCountNodes = pIndex + 1;
            mIndexList.mCount = mCountNodes;
        }
    }
}

void FDrawNodeList::SetXYZ(int pIndex, float pX, float pY, float pZ) {
    if (pIndex >= 0) {
        if (pIndex >= mNodeSize) {
            int aSize = (pIndex + (pIndex / 2) + 2);
            Size(aSize);
        }
        
        mData[pIndex].mX = pX;
        mData[pIndex].mY = pY;
        mData[pIndex].mZ = pZ;
        
        if (pIndex >= mCountNodes) {
            mCountNodes = pIndex + 1;
        }
    }
}

void FDrawNodeList::SetUVW(int pIndex, float pU, float pV, float pW) {
    if (pIndex >= 0) {
        if (pIndex >= mNodeSize) {
            int aSize = (pIndex + (pIndex / 2) + 2);
            Size(aSize);
        }
        
        mData[pIndex].mU = pU;
        mData[pIndex].mV = pV;
        mData[pIndex].mW = pW;
        
        if (pIndex >= mCountNodes) {
            mCountNodes = pIndex + 1;
            mIndexList.mCount = mCountNodes;
        }
    }
}

void FDrawNodeList::SetRGBA(int pIndex, float pRed, float pGreen, float pBlue, float pAlpha)
{
    if (pIndex >= 0) {
        
        if (pIndex >= mNodeSize) {
            int aSize = (pIndex + (pIndex / 2) + 2);
            Size(aSize);
        }
        
        mData[pIndex].mR = pRed;
        mData[pIndex].mG = pGreen;
        mData[pIndex].mB = pBlue;
        mData[pIndex].mA = pAlpha;
        
        if (pIndex >= mCountNodes) {
            mCountNodes = pIndex + 1;
            mIndexList.mCount = mCountNodes;
        }
    }
}

void FDrawNodeList::DrawSetup(FSprite *pSprite)
{
    /*
     //if(mCountNodes <= 0)return;
     
     float *aPtr = (float *)(&(mData[0]));
     
     Graphics::EnableVertexArray();
     Graphics::ArrayVertices(aPtr, sizeof(FDrawNode), 3);
     
     bool aUseTexture = false;
     
     if((mEnabledTexture == true) && (pSprite != 0))
     {
     if(pSprite->mTexture != 0)
     {
     aUseTexture = true;
     }
     }
     
     
     
     if(aUseTexture)
     {
     Graphics::EnableTextureCoordinateArray();
     Graphics::ArrayCoords(aPtr + 3, sizeof(FDrawNode), 3);
     
     Graphics::TextureEnable();
     Graphics::TextureBind(pSprite->mTexture);
     
     if(pStrips)Graphics::DrawTriangleStrips(mCountNodes);
     else Graphics::DrawTriangles(mCountNodes);
     
     //Graphics::DisableColorArray();
     
     }
     else
     {
     Graphics::DisableTextureCoordinateArray();
     Graphics::TextureDisable();
     
     if(pStrips)Graphics::DrawTriangleStrips(mCountNodes);
     else Graphics::DrawTriangles(mCountNodes);
     
     
     }
     */
    
    
    
    
}

void FDrawNodeList::Draw(FSprite *pSprite, bool pStrips)
{
    if(mCountNodes <= 0)return;
    
    float *aPtr = (float *)(&(mData[0]));
    
    //Graphics::EnableVertexArray();
    //Graphics::ArrayVertices(aPtr, sizeof(FDrawNode), 3);
    
    bool aUseTexture = false;
    
    if ((mEnabledTexture == true) && (pSprite != 0)) {
        if (pSprite->mTexture != 0) {
            aUseTexture = true;
        }
    }
    
    //FString aStr = mIndexList.GetPrintString("asdf");
    //Log("%s\n\n", aStr.c());
    
    if (Graphics::ArrayWriteData(aPtr, mCountNodes * sizeof(FDrawNode))) {
        
        if (aUseTexture) {
            Graphics::TextureBind(pSprite->mTexture);
        }
        
        Graphics::ArrayBufferPositions(NULL, 0);
        Graphics::ArrayBufferTextureCoords(NULL, sizeof(float) * 3);
        Graphics::ArrayBufferColors(NULL, sizeof(float) * 6);
        
        Graphics::UniformBind();
        
        //TODO: Smurf?
        //Graphics::DrawTriangleStripsIndexed(mIndexList.mIndex, mCountNodes);
        if (pStrips) {
            Graphics::DrawTriangleStripsIndexed(mIndexList.mIndex, mCountNodes);
        } else {
            Graphics::DrawTrianglesIndexed(mIndexList.mIndex, mCountNodes);
        }
        
    }
}

void FDrawNodeList::DrawNodes(int pHighlightIndex)
{
    for(int i=0;i<mCountNodes;i++)
    {
        float aX = mData[i].mX;
        float aY = mData[i].mY;
        
        float aWidth = 8.0f;
        float aHeight = 8.0f;
        
        if (i != pHighlightIndex) {
            Graphics::SetColor(0.7f, 0.9f, 0.7f);
            Graphics::OutlineRect(aX - (aWidth / 2.0f), aY - (aHeight / 2.0f), aWidth, aHeight, 3.0f);
        } else {
            aWidth = 14.0f;
            aHeight = 14.0f;
            
            Graphics::SetColor(0.7f * 0.65f, 0.9f * 0.65f, 0.7f * 0.65f);
            Graphics::OutlineRect(aX - (aWidth / 2.0f), aY - (aHeight / 2.0f), aWidth, aHeight, 5.0f);
        }
    }
    
    if (true) {
        float aBarWidth = 42.0f;
        float aBarHeight = 13.0f;
        
        float aShiftX = -5;
        float aShiftY = -19;
        
        FRect aRect[4];
        
        for(int i=3;i>=0;i--)
        {
            aRect[i].mX = aShiftX;
            aRect[i].mY = aShiftY;
            aRect[i].mWidth = aBarWidth;
            aRect[i].mHeight = aBarHeight;
            
            
            aShiftY -= 15.0f;
        }
        
        FColor aColor[4];
        aColor[0] = FColor(1.0f,0.0f,0.0f);
        aColor[1] = FColor(0.0f,1.0f,0.0f);
        aColor[2] = FColor(0.0f,0.0f,1.0f);
        aColor[3] = FColor(1.0f,1.0f,1.0f);
        
        
        
        for (int i=0;i<mCountNodes;i++) {
            
            if (i == pHighlightIndex) {
                float aX = mData[i].mX;
                float aY = mData[i].mY;
                
                float aP[4];
                aP[0] = mData[i].mR;
                aP[1] = mData[i].mG;
                aP[2] = mData[i].mB;
                aP[3] = mData[i].mA;
                
                
                for (int c=0;c<4;c++) {
                    Graphics::SetColor(0.25f, 0.45f, 0.25f);
                    Graphics::OutlineRect(aX + aRect[c].mX, aRect[c].mY, aRect[c].mWidth, aRect[c].mHeight, 4.0f);
                    
                    Graphics::SetColor(0.25f, 0.45f, 0.25f);
                    Graphics::OutlineRect(aX + aRect[c].mX, aRect[c].mY, aRect[c].mWidth, aRect[c].mHeight, 2.0f);
                    
                    
                    Graphics::SetColor(0.4f, 0.4f, 0.4f);
                    Graphics::DrawRect(aX + aRect[c].mX, aY + aRect[c].mY, aRect[c].mWidth, aRect[c].mHeight);
                    
                    
                    
                    Graphics::SetColor(aColor[c]);
                    Graphics::DrawRect(aX + aRect[c].mX, aY + aRect[c].mY, aRect[c].mWidth * aP[c], aRect[c].mHeight);
                    
                }
                
                
                
            }
            
        }
        
        
        
    }
    
    Graphics::SetColor();
    
}

int FDrawNodeList::GetClosestNode(float pX, float pY, float &pDist)
{
    pDist = 0.0f;
    
    int aResult = -1;
    
    if(mCountNodes > 0)
    {
        aResult = 0;
        
        float aDiffX = mData[0].mX - pX;
        float aDiffY = mData[0].mY - pY;
        
        pDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        float aDist = 0.0f;
        for(int i=1;i<mCountNodes;i++)
        {
            aDiffX = mData[i].mX - pX;
            aDiffY = mData[i].mY - pY;
            
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            
            if(aDist < pDist)
            {
                pDist = aDist;
                aResult = i;
            }
        }
    }
    
    return aResult;
}

int FDrawNodeList::GetClosestNode(float pX, float pY)
{
    float aDist = 200.0f;
    
    int aResult = GetClosestNode(pX, pY, aDist);
    
    return aResult;
}


void FDrawNodeList::AdjustTextureCoordinates(float pStartU, float pStartV, float pEndU, float pEndV)
{
    float aRangeU = (pEndU - pStartU);
    float aRangeV = (pEndV - pStartV);
    
    for(int i=0;i<mCountNodes;i++)
    {
        mData[i].mU = pStartU + mData[i].mU * aRangeU;
        mData[i].mV = pStartV + mData[i].mV * aRangeV;
    }
}

void FDrawNodeList::AdjustTextureCoordinates(FSprite *pSprite)
{
    if(pSprite)
    {
        AdjustTextureCoordinates(pSprite->mTextureRect.GetStartU(), pSprite->mTextureRect.GetStartV(), pSprite->mTextureRect.GetEndU(), pSprite->mTextureRect.GetEndV());
    }
}

void FDrawNodeList::SwapUV()
{
    float aHold = 0.0f;
    for(int i=0;i<mCountNodes;i++)
    {
        aHold = mData[i].mU;
        mData[i].mU = mData[i].mV;
        mData[i].mV = aHold;
    }
}


FDrawNodeMesh::FDrawNodeMesh()
{
    mConLink1 = 0;
    mConLink2 = 0;
    
    mConLinkSize = 0;
    mConLinkCount = 0;
    
    
    mTriList1 = 0;
    mTriList2 = 0;
    mTriList3 = 0;
    
    mTriListSize = 0;
    mTriListCount = 0;
    
}

FDrawNodeMesh::~FDrawNodeMesh()
{
    Clear();
}

void FDrawNodeMesh::Reset()
{
    FDrawNodeList::Reset();
    
    mConLinkCount = 0;
}

void FDrawNodeMesh::Clear()
{
    FDrawNodeList::Clear();
    
    delete [] mConLink1;
    
    mConLink1 = 0;
    mConLink2 = 0;
    
    mConLinkSize = 0;
    mConLinkCount = 0;
    
    
    delete [] mTriList1;
    mTriList1 = 0;
    mTriList2 = 0;
    mTriList3 = 0;
    
    mTriListSize = 0;
    mTriListCount = 0;
    
}

void FDrawNodeMesh::AddConnection(int pStartIndex, int pEndIndex)
{
    if((pStartIndex != pEndIndex) && (pStartIndex >= 0) && (pStartIndex < mCountNodes) && (pEndIndex >= 0) && (pEndIndex < mCountNodes))
    {
        bool aExists = false;
        if(aExists == false)
        {
            if(mConLinkCount >= mConLinkSize)
            {
                mConLinkSize = (mConLinkCount + (mConLinkCount / 2) + 1);
                
                short *aNewCon1 = new short[mConLinkSize * 2];
                short *aNewCon2 = &(aNewCon1[mConLinkSize]);
                
                for(int i=0;i<mConLinkCount;i++)
                {
                    aNewCon1[i]=mConLink1[i];
                    aNewCon2[i]=mConLink2[i];
                }
                
                delete [] mConLink1;
                
                mConLink1 = aNewCon1;
                mConLink2 = aNewCon2;
            }
            
            mConLink1[mConLinkCount] = pStartIndex;
            mConLink2[mConLinkCount] = pEndIndex;
            
            mConLinkCount++;
        }
    }
}

void FDrawNodeMesh::DrawConnections()
{
    //Graphics::SetColor(1.0f, 0.0f, 1.0f, 1.0f);
    Graphics::SetColor(0.25f, 0.25f, 0.25f, 1.0f);
    
    for(int i=0;i<mConLinkCount;i++)
    {
        float aX1 = mData[mConLink1[i]].mX;
        float aY1 = mData[mConLink1[i]].mY;
        
        float aX2 = mData[mConLink2[i]].mX;
        float aY2 = mData[mConLink2[i]].mY;
        
        Graphics::DrawLine(aX1, aY1, aX2, aY2, 1.0f);
    }
    
    Graphics::SetColor();
}

void FDrawNodeMesh::AddTriangle(short pIndex1, short pIndex2, short pIndex3)
{
    bool aExists = false;
    
    int aT1 = 0;
    int aT2 = 0;
    int aT3 = 0;
    
    for(int i=0;i<mTriListCount;i++)
    {
        aT1 = mTriList1[i];
        aT2 = mTriList2[i];
        aT3 = mTriList3[i];
        
        if(pIndex1 == aT1)
        {
            if((pIndex2 == aT2) && (pIndex3 == aT3))aExists = true;
            if((pIndex3 == aT2) && (pIndex2 == aT3))aExists = true;
        }
        else if(pIndex1 == aT2)
        {
            if((pIndex2 == aT1) && (pIndex3 == aT3))aExists = true;
            if((pIndex3 == aT1) && (pIndex2 == aT3))aExists = true;
        }
        else if(pIndex1 == aT3)
        {
            if((pIndex2 == aT1) && (pIndex3 == aT2))aExists = true;
            if((pIndex3 == aT1) && (pIndex2 == aT2))aExists = true;
        }
    }
    
    if(aExists == false)
    {
        if(mTriListCount >= mTriListSize)
        {
            mTriListSize = (mTriListCount + (mTriListCount / 2) + 1);
            
            short *aTriList1 = new short[mTriListSize * 3];
            short *aTriList2 = &(aTriList1[mTriListSize]);
            short *aTriList3 = &(aTriList2[mTriListSize]);
            
            for(int i=0;i<mTriListCount;i++)
            {
                aTriList1[i] = mTriList1[i];
                aTriList2[i] = mTriList2[i];
                aTriList3[i] = mTriList3[i];
            }
            
            delete [] mTriList1;
            
            mTriList1 = aTriList1;
            mTriList2 = aTriList2;
            mTriList3 = aTriList3;
        }
        
        mTriList1[mTriListCount] = pIndex1;
        mTriList2[mTriListCount] = pIndex2;
        mTriList3[mTriListCount] = pIndex3;
        
        mTriListCount++;
    }
}

void FDrawNodeMesh::Generate()
{
    if(mCountNodes < 1)
    {
        return;
    }
    
    int *aConCount = new int[mCountNodes];
    int **aCon = new int*[mCountNodes];
    
    for(int i=0;i<mCountNodes;i++)
    {
        
        aConCount[i] = 0;
        aCon[i] = new int[mCountNodes];
        
        for(int k=0;k<mCountNodes;k++)
        {
            aCon[i][k] = 0;
        }
    }
    
    
    
    
    for(int i=0;i<mConLinkCount;i++)
    {
        aCon[mConLink1[i]][mConLink2[i]] = 1;
        aCon[mConLink2[i]][mConLink1[i]] = 1;
    }
    
    
    mTriListCount = 0;
    for(int i=0;i<mCountNodes;i++)
    {
        for(int n=0;n<mCountNodes;n++)
        {
            if(i != n)
            {
                if(aCon[i][n])
                {
                    for(int k=0;k<mCountNodes;k++)
                    {
                        if((k != i) && (k != n))
                        {
                            if((aCon[i][k] == true) && (aCon[k][n] == true))
                            {
                                AddTriangle(i, n, k);
                            }
                        }
                    }
                }
            }
        }
    }
    
    mRenderNodes.Clear();
    for(int i=0;i<mTriListCount;i++)
    {
        mRenderNodes.Add(&(mData[mTriList1[i]]));
        mRenderNodes.Add(&(mData[mTriList2[i]]));
        mRenderNodes.Add(&(mData[mTriList3[i]]));
    }
}

void FDrawNodeMesh::Print(float pCenterX, float pCenterY)
{
    FString aMeshName = "mMesh";
    
    Log("%s.Size(%d);\n", aMeshName.c(), mCountNodes);
    
    for(int i=0;i<mCountNodes;i++)
    {
        Log("%s.Set(%d, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f);\n", aMeshName.c(), i, (mData[i].mX - pCenterX), (mData[i].mY - pCenterY), mData[i].mZ, mData[i].mU, mData[i].mV, mData[i].mW, mData[i].mR, mData[i].mG, mData[i].mB, mData[i].mA);
    }
    
    Log("\n");
    
    int aBreak = 0;
    for(int i=0;i<mConLinkCount;i++)
    {
        Log("%s.AddConnection(%d, %d);", aMeshName.c(), mConLink1[i], mConLink2[i]);
        
        aBreak++;
        if(aBreak == 3)
        {
            Log("\n");
            aBreak = 0;
        }
    }
    Log("\n");
}






































