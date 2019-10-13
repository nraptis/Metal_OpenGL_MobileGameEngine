//
//  FModelData.cpp
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 Nick Raptis. All rights reserved.
//

#include "core_includes.h"
#include "FModelData.h"
#include "FApp.hpp"
#include "FTexture.hpp"
#include "FList.hpp"

bool gModelDiscardNormals = false;
bool gModelDiscardUVW = false;

FModelData::FModelData()
{
    mTexture = 0;
    mXYZ=0;mUVW=0;mNormal=0;
    mXYZCount=0;mXYZSize=0;
    mUVWCount=0;mUVWSize=0;
    mNormalCount=0;mNormalSize=0;
}

FModelData::~FModelData()
{
    SetTexture(0);
    Free();
}

void FModelData::Free()
{
    DiscardXYZ();
    DiscardUVW();
    DiscardNormal();
}

void FModelData::DiscardXYZ()
{
    delete[]mXYZ;
    mXYZ=0;
    mXYZCount=0;
    mXYZSize=0;
}

void FModelData::DiscardUVW()
{
    delete[]mUVW;
    mUVW=0;
    mUVWCount=0;
    mUVWSize=0;
}

void FModelData::DiscardNormal()
{
    delete[]mNormal;
    mNormal=0;
    mNormalCount=0;
    mNormalSize=0;
}

float *FModelData::ResizeTriple(float *pData, int pCount, int pSize)
{
    int aDataSize = (pSize * 3);
    int aDataCount = (pCount * 3);
    
    float *aNew = new float[aDataSize+1];
    for(int i=0;i<aDataCount;i++)
    {
        aNew[i] = pData[i];
    }
    for(int i=aDataCount;i<aDataSize;i++)
    {
        aNew[i] = 0;
    }
    delete[]pData;
    
    return aNew;
}

void FModelData::SetTriple(unsigned int pIndex, float *pArray, float pValue1, float pValue2, float pValue3)
{
    unsigned int aIndex = pIndex * 3;
    pArray[aIndex]=pValue1;
    pArray[aIndex+1]=pValue2;
    pArray[aIndex+2]=pValue3;
}

void FModelData::AddXYZ(float pX, float pY, float pZ)
{
    if(mXYZCount >= mXYZSize)SizeXYZ(mXYZCount + mXYZCount / 2 + 1);
    SetTriple(mXYZCount, mXYZ, pX, pY, pZ);
    mXYZCount++;
}

void FModelData::SizeXYZ(int pSize)
{
    if(pSize != 0)mXYZ = ResizeTriple(mXYZ, mXYZCount, pSize);
    mXYZSize = pSize;
}

void FModelData::AddUVW(float pU, float pV, float pW)
{
    if(mUVWCount >= mUVWSize)SizeUVW(mUVWCount + mUVWCount / 2 + 1);
    SetTriple(mUVWCount, mUVW, pU, pV, pW);
    mUVWCount++;
}

void FModelData::SizeUVW(int pSize)
{
    if(pSize != 0)mUVW = ResizeTriple(mUVW, mUVWCount, pSize);
    mUVWSize = pSize;
}

void FModelData::AddNormal(float pNormX, float pNormY, float pNormZ)
{
    if(mNormalCount >= mNormalSize)SizeNormal(mNormalCount + mNormalCount / 2 + 1);
    SetTriple(mNormalCount, mNormal, pNormX, pNormY, pNormZ);
    mNormalCount++;
}

void FModelData::SizeNormal(int pSize)
{
    if(pSize != 0)mNormal = ResizeTriple(mNormal, mNormalCount, pSize);
    mNormalSize = pSize;
}

float FModelData::GetX(int pIndex)
{
    //if(pIndex>=0 && pIndex<mXYZCount)
    return mXYZ[pIndex*3];
    //Log("Error Fetching X [%d / %d]\n", pIndex, mXYZCount);
    //return 0;
}

float FModelData::GetY(int pIndex)
{
    //if(pIndex>=0 && pIndex<mXYZCount)
    return mXYZ[pIndex*3+1];
    //return 0;
}

float FModelData::GetZ(int pIndex)
{
    //if(pIndex>=0 && pIndex<mXYZCount)
    return mXYZ[pIndex*3+2];
    //return 0;
}


float FModelData::GetU(int pIndex)
{
    //if(pIndex>=0 && pIndex<mUVWCount)
    return mUVW[pIndex*3];
    //return 0;
}

float FModelData::GetV(int pIndex)
{
    //if(pIndex>=0 && pIndex<mUVWCount)
    return mUVW[pIndex*3+1];
    //return 0;
}

float FModelData::GetW(int pIndex)
{
    //if(pIndex>=0 && pIndex<mUVWCount)
    return mUVW[pIndex*3+2];
    //return 0;
}

float FModelData::GetNormX(int pIndex)
{
    //if(pIndex>=0 && pIndex<mNormalCount)
    return mNormal[pIndex*3];
    //return 0;
}

float FModelData::GetNormY(int pIndex)
{
    //if(pIndex>=0 && pIndex<mNormalCount)
    return mNormal[pIndex*3+1];
    //return 0;
}

float FModelData::GetNormZ(int pIndex) {
    //if(pIndex>=0 && pIndex<mNormalCount)
    return mNormal[pIndex*3+2];
    //return 0;
}

void FModelData::InvertU() {
    int aCount = mUVWCount * 3;
    for(int i=0;i<aCount;i+=3)mUVW[i]=(1-mUVW[i]);
}

void FModelData::InvertV() {
    int aCount = mUVWCount * 3;
    for(int i=1;i<aCount;i+=3)mUVW[i]=(1-mUVW[i]);
}

void FModelData::InvertW() {
    int aCount = mUVWCount * 3;
    for(int i=2;i<aCount;i+=3)mUVW[i]=(1-mUVW[i]);
}

void FModelData::FlipXY() {
    float aHold=0;
    int aCount = mXYZCount * 3;
    for (int i=0;i<aCount;i+=3) {
        aHold=mXYZ[i];
        mXYZ[i]=mXYZ[i+1];
        mXYZ[i+1]=aHold;
    }
    aCount = mNormalCount * 3;
    for (int i=0;i<aCount;i+=3) {
        aHold = mNormal[i];
        mNormal[i] = mNormal[i+1];
        mNormal[i+1] = aHold;
    }
}

void FModelData::FlipYZ() {
    float aHold = 0;
    int aCount = mXYZCount * 3;
    for (int i=0;i<aCount;i+=3) {
        aHold = mXYZ[i+1];
        mXYZ[i+1] = mXYZ[i+2];
        mXYZ[i+2] = aHold;
    }
    aCount = mNormalCount * 3;
    for (int i=0;i<aCount;i+=3) {
        aHold = mNormal[i];
        mNormal[i] = -mNormal[i+2];
        mNormal[i+2] = aHold;
    }
}

void FModelData::FlipZX() {
    float aHold=0;
    int aCount = mXYZCount * 3;
    for (int i=0;i<aCount;i+=3) {
        aHold=mXYZ[i];
        mXYZ[i]=mXYZ[i+2];
        mXYZ[i+2]=aHold;
    }
    
    aCount = mNormalCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        aHold= mNormal[i];
        mNormal[i]=mNormal[i+2];
        mNormal[i+2]=aHold;
    }
}


void FModelData::NegateX()
{
    int aCount = mXYZCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        mXYZ[i] = (-mXYZ[i]);
    }
}

void FModelData::NegateY()
{
    int aCount = mXYZCount * 3;
    for(int i=1;i<aCount;i+=3)
    {
        mXYZ[i] = (-mXYZ[i]);
    }
}

void FModelData::NegateZ()
{
    int aCount = mXYZCount * 3;
    for(int i=2;i<aCount;i+=3)
    {
        mXYZ[i] = (-mXYZ[i]);
    }
}

void FModelData::ShiftX(float pShiftAmount)
{
    int aCount = mXYZCount * 3;
    for(int i=0;i<aCount;i+=3)
    {
        mXYZ[i] += pShiftAmount;
    }
}

void FModelData::ShiftY(float pShiftAmount)
{
    int aCount = mXYZCount * 3;
    for(int i=1;i<aCount;i+=3)
    {
        mXYZ[i] += pShiftAmount;
    }
}

void FModelData::ShiftZ(float pShiftAmount)
{
    int aCount = mXYZCount * 3;
    for(int i=2;i<aCount;i+=3)
    {
        mXYZ[i] += pShiftAmount;
    }
}

void FModelData::ShiftCentroid()
{
    float aCentroidX = 0.0f;
    float aCentroidY = 0.0f;
    float aCentroidZ = 0.0f;
    
    GetCentroid(aCentroidX, aCentroidY, aCentroidZ);
    
    ShiftX(-aCentroidX);
    ShiftY(-aCentroidX);
    ShiftZ(-aCentroidX);
}

void FModelData::Scale(float pScale)
{
    int aCount = mXYZCount * 3;
    for(int i=0;i<aCount;i++)
    {
        mXYZ[i] *= pScale;
    }
    
}

void FModelData::SetTexture(FTexture *pTexture)
{
    SET_TEXTURE_BODY;
}

void FModelData::SetSprite(FSprite *pSprite, bool pFixUVW)
{
    if(pSprite)
    {
        SetTexture(pSprite->mTexture);
        
        if(pFixUVW)
        {
            
            
            float aStartU = pSprite->mTextureRect.GetStartU();
            float aStartV = pSprite->mTextureRect.GetStartV();
             
            float aEndU = pSprite->mTextureRect.GetEndU();
            float aEndV = pSprite->mTextureRect.GetEndV();
            
            FitUVW(aStartU, aEndU, aStartV, aEndV);
        }
    }
}


void FModelData::FitUVW(float pStartU, float pEndU, float pStartV, float pEndV) {
    if ((pStartU == 0) && (pStartV == 0) && (pEndU == 1) && (pEndV == 1)) {
        return;
    }
    
    if (mUVWCount <= 0) return;
    
    float aSpanU = pEndU - pStartU;
    float aSpanV = pEndV - pStartV;
    
    int aIndex = 0;
    float aU, aV;
    for (int i=0;i<mUVWCount;i++) {
        aIndex = i * 3;
        
        aU = mUVW[aIndex];
        aV = mUVW[aIndex+1];
        
        aU = (pStartU + aSpanU * aU);
        aV = (pStartV + aSpanV * aV);
        
        mUVW[aIndex] = aU;
        mUVW[aIndex+1] = aV;
    }
}


void FModelData::CopyXYZ(float *pXYZ, int pCount) {
    delete[]mXYZ;
    mXYZCount=0;
    mXYZSize=0;
    if((pXYZ!=0) && (pCount>0))
    {
        SizeXYZ(pCount);
        int aCount3 = (pCount * 3);
        mXYZ = new float[aCount3];
        for(int i=0;i<aCount3;i++)mXYZ[i] = pXYZ[i];
        mXYZCount = pCount;
    }
}

void FModelData::CopyUVW(float *pUVW, int pCount)
{
    delete[]mUVW;
    mUVWCount=0;
    mUVWSize=0;
    if((pUVW!=0) && (pCount>0))
    {
        SizeUVW(pCount);
        int aCount3 = (pCount * 3);
        mUVW = new float[aCount3];
        for(int i=0;i<aCount3;i++)mUVW[i] = pUVW[i];
        mUVWCount = pCount;
    }
}

void FModelData::CopyNorm(float *pNorm, int pCount)
{
    delete[]mNormal;
    mNormalCount=0;
    mNormalSize=0;
    if((pNorm!=0) && (pCount>0))
    {
        SizeNormal(pCount);
        int aCount3 = (pCount * 3);
        mNormal = new float[aCount3];
        for(int i=0;i<aCount3;i++)mNormal[i] = pNorm[i];
        mNormalCount = pCount;
    }
}

FModelData *FModelData::Clone()
{
    FModelData *aClone=new FModelData();
    aClone->CopyXYZ(mXYZ, mXYZCount);
    aClone->CopyUVW(mUVW, mUVWCount);
    aClone->CopyNorm(mNormal, mNormalCount);
    return aClone;
}

void FModelData::Print()
{
    
}

void FModelData::Save(const char *pFile)
{
    FFile aFile;
    Save(&aFile);
    aFile.Save(pFile);
}

void FModelData::Save(FFile *pFile)
{
    if(!pFile)return;
    
    pFile->WriteInt(mXYZCount);
    pFile->WriteInt(mUVWCount);
    pFile->WriteInt(mNormalCount);
    
    int aXYZCount = mXYZCount * 3;
    int aUVWCount = mUVWCount * 3;
    int aNormalCount = mNormalCount * 3;
    
    for(int i=0;i<aXYZCount;i++)pFile->WriteFloat(mXYZ[i]);
    for(int i=0;i<aUVWCount;i++)pFile->WriteFloat(mUVW[i]);
    for(int i=0;i<aNormalCount;i++)pFile->WriteFloat(mNormal[i]);
}

void FModelData::LoadData(FFile *pFile)
{
    if(!pFile)return;
    
    int aXYZCount=pFile->ReadInt();
    int aUVWCount=pFile->ReadInt();
    int aNormalCount=pFile->ReadInt();
    
    DiscardXYZ();
    DiscardUVW();
    DiscardNormal();
    
    //mXYZCount=0;
    //mUVWCount=0;
    //mNormalCount=0;
    
    SizeXYZ(aXYZCount);
    SizeUVW(aUVWCount);
    SizeNormal(aNormalCount);
    
    mXYZCount=aXYZCount;
    mUVWCount=aUVWCount;
    mNormalCount=aNormalCount;
    
    aXYZCount *= 3;
    aUVWCount *= 3;
    aNormalCount *= 3;
    
    for(int i=0;i<aXYZCount;i++)mXYZ[i] = pFile->ReadFloat();
    for(int i=0;i<aUVWCount;i++)mUVW[i] = pFile->ReadFloat();
    for(int i=0;i<aNormalCount;i++)mNormal[i] = pFile->ReadFloat();
}

void FModelData::LoadData(const char *pFile)
{
    Log("LoadDataingFModelData[%s]\n", pFile);
    FFile aFile;
    aFile.Load(pFile);
    LoadData(&aFile);
}


void FModelData::LoadOBJ(FFile *pFile)
{
    Free();
    
    if(pFile == 0)return;
    if(pFile->mLength <= 0)return;
    
    //FModelData *aResult = new FModelData();
    
    FModelDataIndexed *aTemp = new FModelDataIndexed();
    
    //int aPreviousIndexStart = 0;
    int aError=0;
    
    float aX, aY, aZ,
    aU, aV, aW,
    aNX, aNY, aNZ;
    
    int aXYZIndex = 0;
    int aUVWIndex = 0;
    int aNormalIndex = 0;
    
	char *aData=(char*)pFile->mData;
	int aLength=pFile->mLength;
	
	char *aEnd=&aData[aLength];
	char *aLineStart=aData;
	char *aLineEnd=aData;
    
    int aLineLength;
    int aWriteIndex;
    int aNumberCount;
    
    char *aSeek;
    char aNumberString[128];
    float aFloat[32];
    int aFace[4][3];
    int aFaceIndex;
    int aFaceCol;
    
    bool aContinue;
    int aLine=1;
    
	while((aLineStart<aEnd)&&(aError==0)) {
		while((aLineStart < aEnd) && (*aLineStart <= 32)) {
			aLineStart++;
		}
        
		aLineEnd=aLineStart;
        
		while ((aLineEnd < aEnd) && (*aLineEnd >= 32)) {
			aLineEnd++;
		}
        
		if ((aLineEnd > aLineStart) && (aError == 0)) {
            aLineLength = (int)(aLineEnd - aLineStart);
            if(aLineLength > 1)
            {
                if(aLineStart[0] == 'g')
                {
                    /*
                    if(pList != 0)
                    {
                        if(aTemp->mIndexCount != aPreviousIndexStart)
                        {
                            FModelData *aModel = new FModelData();
                            
                            for(int i=aPreviousIndexStart;i<aTemp->mIndexCount;i+=3)
                            {
                                aXYZIndex = aTemp->mIndex[i];
                                aUVWIndex = aTemp->mIndex[i+1];
                                aNormalIndex = aTemp->mIndex[i+2];
                                
                                aX = aTemp->GetX(aXYZIndex);
                                aY = aTemp->GetY(aXYZIndex);
                                aZ = aTemp->GetZ(aXYZIndex);
                                
                                aU = aTemp->GetU(aUVWIndex);
                                aV = aTemp->GetV(aUVWIndex);
                                aW = aTemp->GetW(aUVWIndex);
                                
                                aNX = aTemp->GetNormX(aNormalIndex);
                                aNY = aTemp->GetNormY(aNormalIndex);
                                aNZ = aTemp->GetNormZ(aNormalIndex);
                                
                                aModel->AddXYZ(aX, aY, aZ);
                                aModel->AddUVW(aU, aV, aW);
                                aModel->AddNormal(aNX, aNY, aNZ);
                            }
                            
                            aModel->InvertV();
                            pList->Add(aModel);
                            aPreviousIndexStart = aTemp->mIndexCount;
                        }
                    }
                    */
                }
            }
            
            if(aLineLength > 5)
            {
                if(aLineStart[0] == 'v')
                {
                    aNumberCount=0;
                    aSeek=aLineStart;
                    while((aNumberCount < 3) && (aSeek < aLineEnd))
                    {
                        while(aSeek < aLineEnd)
                        {
                            if((*aSeek >= '0' && *aSeek <= '9') || (*aSeek == '.'))
                            {
                                aWriteIndex=0;
                                if(aSeek > aLineStart)
                                {
                                    if(*(aSeek-1)=='-')
                                    {
                                        aNumberString[aWriteIndex++]='-';
                                    }
                                }
                                while(((*aSeek >= '0' && *aSeek <= '9') || (*aSeek == '.')) && (aSeek < aEnd))
                                {
                                    aNumberString[aWriteIndex++]=*aSeek;
                                    aSeek++;
                                }
                                aNumberString[aWriteIndex]=0;
                                aFloat[aNumberCount] = atof(aNumberString);
                                aNumberCount++;
                                break;
                            }
                            else
                            {
                                aSeek++;
                            }
                        }
                    }
                    
                    if(aLineStart[1] <= ' ')
                    {
                        if(aNumberCount < 3)aError=2;
                        else aTemp->AddXYZ(aFloat[0], aFloat[1], aFloat[2]);
                    }
                    
                    if(aLineStart[1] == 't')
                    {
                        if(aNumberCount < 2)aError=3;
                        else if(aNumberCount == 2)aTemp->AddUVW(aFloat[0], aFloat[1], 0);
                        else aTemp->AddUVW(aFloat[0], aFloat[1], aFloat[2]);
                    }
                    
                    if(aLineStart[1] == 'n')
                    {
                        if(aNumberCount < 3)aError=4;
                        else aTemp->AddNormal(aFloat[0], aFloat[1], aFloat[2]);
                    }
                }
                
                if(aLineStart[0] == 'f' && aLineStart[1] <= ' ')
                {
                    
                    for(int i=0;i<4;i++)
                    {
                        for(int n=0;n<3;n++)
                        {
                            aFace[i][n]=-1;
                        }
                    }
                    
                    aFaceCol=0;
                    aFaceIndex=0;
                    aContinue=false;
                    aSeek=aLineStart;
                    
                    while((aSeek < aLineEnd) && (aError == 0))
                    {
                        if(aFaceCol > 4)
                        {
                            aError=9;
                            break;
                        }
                        else if(*aSeek >= '0' && *aSeek <= '9')
                        {
                            if(aFaceIndex > 3)
                            {
                                aError=10;
                            }
                            
                            aWriteIndex=0;
                            
                            while(*aSeek >= '0' && *aSeek <= '9')
                            {
                                aNumberString[aWriteIndex++]=*aSeek;
                                aSeek++;
                            }
                            
                            aNumberString[aWriteIndex]=0;
                            aFace[aFaceCol][aFaceIndex]=(atoi(aNumberString) - 1);
                            
                            if(*aSeek=='/')
                            {
                                if(*(aSeek+1)=='/')
                                {
                                    aSeek++;
                                    aFaceIndex++;
                                }
                                aFaceIndex++;
                            }
                            else
                            {
                                aFaceIndex=0;
                                aFaceCol++;
                            }
                        }
                        else
                        {
                            aSeek++;
                        }
                    }
                    
                    if(aFaceCol == 3)
                    {
                        aTemp->AddIndex(aFace[0][0]);
                        aTemp->AddIndex(aFace[0][1]);
                        aTemp->AddIndex(aFace[0][2]);
                        
                        aTemp->AddIndex(aFace[1][0]);
                        aTemp->AddIndex(aFace[1][1]);
                        aTemp->AddIndex(aFace[1][2]);
                        
                        aTemp->AddIndex(aFace[2][0]);
                        aTemp->AddIndex(aFace[2][1]);
                        aTemp->AddIndex(aFace[2][2]);
                    }
                }
                aSeek=aLineStart;
            }
		}
        aLine++;
		aLineStart = aLineEnd + 1;
	}
    
    /*
    if(pList != 0)
    {
        if(aTemp->mIndexCount != aPreviousIndexStart)
        {
            FModelData *aModel = new FModelData();
            
            for(int i=aPreviousIndexStart;i<aTemp->mIndexCount;i+=3)
            {
                aXYZIndex = aTemp->mIndex[i];
                aUVWIndex = aTemp->mIndex[i+1];
                aNormalIndex = aTemp->mIndex[i+2];
                
                aX = aTemp->GetX(aXYZIndex);
                aY = aTemp->GetY(aXYZIndex);
                aZ = aTemp->GetZ(aXYZIndex);
                
                aU = aTemp->GetU(aUVWIndex);
                aV = aTemp->GetV(aUVWIndex);
                aW = aTemp->GetW(aUVWIndex);
                
                aNX = aTemp->GetNormX(aNormalIndex);
                aNY = aTemp->GetNormY(aNormalIndex);
                aNZ = aTemp->GetNormZ(aNormalIndex);
                
                aModel->AddXYZ(aX, aY, aZ);
                aModel->AddUVW(aU, aV, aW);
                aModel->AddNormal(aNX, aNY, aNZ);
            }
            
            aModel->InvertV();
            
            pList->Add(aModel);
            
            aPreviousIndexStart = aTemp->mIndexCount;
            
        }
    }
    */
    
    int aIndexCount = aTemp->mIndexCount;
    for(int i=0;i<aIndexCount;i+=3)
    {
        aXYZIndex = aTemp->mIndex[i];
        aUVWIndex = aTemp->mIndex[i+1];
        aNormalIndex = aTemp->mIndex[i+2];
        
        aX = aTemp->GetX(aXYZIndex);
        aY = aTemp->GetY(aXYZIndex);
        aZ = aTemp->GetZ(aXYZIndex);
        
        aU = aTemp->GetU(aUVWIndex);
        aV = aTemp->GetV(aUVWIndex);
        aW = aTemp->GetW(aUVWIndex);
        
        aNX = aTemp->GetNormX(aNormalIndex);
        aNY = aTemp->GetNormY(aNormalIndex);
        aNZ = aTemp->GetNormZ(aNormalIndex);
        
        AddXYZ(aX, aY, aZ);
        AddUVW(aU, aV, aW);
        AddNormal(aNX, aNY, aNZ);
    }
    delete aTemp;
    
    if(gModelDiscardNormals)DiscardNormal();
    if(gModelDiscardUVW)DiscardUVW();
    
    //TODO: Why was this? Is this right?
    //TODO: Now why is this?
    InvertV();
    
}

void FModelData::LoadOBJ(const char *pFile)
{
    FFile aFile;
    aFile.Load(pFile);
    LoadOBJ(&aFile);
}

void FModelData::SetImage(FImage *pImage)
{
    if(pImage)
    {
        SetTexture(pImage->GetTexture());
    }
    else
    {
        SetTexture(0);
    }
}

void FModelData::SetImage(const char *pImagePath)
{
    FImage aImage;
    aImage.Load(pImagePath);
    SetImage(&aImage);
}

void FModelData::GetCentroid(float &pCentroidX, float &pCentroidY, float &pCentroidZ)
{
    pCentroidX=0.0f;
    pCentroidY=0.0f;
    pCentroidZ=0.0f;
    
    int aCap = mXYZCount * 3;
    
    for(int i=0;i<aCap;)
    {
        pCentroidX += mXYZ[i++];
        pCentroidY += mXYZ[i++];
        pCentroidZ += mXYZ[i++];
    }
    
    if(mXYZCount > 1)
    {
        pCentroidX /= (float)mXYZCount;
        pCentroidY /= (float)mXYZCount;
        pCentroidZ /= (float)mXYZCount;
    }
}

void FModelData::PrintOverview()
{
    Log("FModelDataOverview: XYZ(%d/%d) UVW(%d/%d) NORM(%d/%d)\n", mXYZCount, mXYZSize, mUVWCount, mUVWSize, mNormalCount, mNormalSize);
}

void FModelData::Draw() {
    Graphics::DrawModel(mXYZ, mUVW, mNormal, mXYZCount, mTexture);
}

//////////////////////////////////////////
//////////////////////////////////////////
////                                  ////
////                                  ////
////         Indexed Version          ////
////                                  ////
////                                  ////
//////////////////////////////////////////
//////////////////////////////////////////

FModelDataIndexed::FModelDataIndexed() {
    mIndex = 0;
    mIndexCount = 0;
    mIndexSize = 0;
}

FModelDataIndexed::~FModelDataIndexed() {
    Free();
}

void FModelDataIndexed::Free() {
    FModelData::Free();
    
    delete[]mIndex;
    mIndex=0;
    mIndexCount=0;
    mIndexSize=0;
}

void FModelDataIndexed::AddIndex(GFX_MODEL_INDEX_TYPE pIndex) {
    if(mIndexCount >= mIndexSize)SizeIndex(mIndexCount + (mIndexCount / 2) + 1);
    mIndex[mIndexCount]=pIndex;
    mIndexCount++;
}

void FModelDataIndexed::SizeIndex(int pSize) {
    mIndexSize = pSize;
    
    GFX_MODEL_INDEX_TYPE *aNew = new GFX_MODEL_INDEX_TYPE[mIndexSize + 1];
    
    for(int i=0;i<mIndexCount;i++)aNew[i] = mIndex[i];
    for(int i=mIndexCount;i<mIndexSize;i++)aNew[i] = 0;
    
    delete [] mIndex;
    mIndex = aNew;
}

void FModelDataIndexed::CopyIndex(GFX_MODEL_INDEX_TYPE *pIndex, int pCount) {
    delete [] mIndex;
    mIndex = NULL;
    mIndexCount = 0;
    mIndexSize = 0;
    
    if ((pIndex == NULL) || (pCount <= 0)) {
        return;
    }
    
    SizeIndex(pCount);
    for (int i=0;i<pCount;i++) {
        mIndex[i]=pIndex[i];
    }
    mIndexCount=pCount;
}

void FModelDataIndexed::GetCentroid(float &pCentroidX, float &pCentroidY, float &pCentroidZ)
{
    pCentroidX=0.0f;
    pCentroidY=0.0f;
    pCentroidZ=0.0f;
    
    int aIndex;
    
    for(int i=0;i<mIndexCount;i++)
    {            
        aIndex = mIndex[i] * 3;
        pCentroidX += mXYZ[aIndex + 0];
        pCentroidY += mXYZ[aIndex + 1];
        pCentroidZ += mXYZ[aIndex + 2];
    }
    
    if(mIndexCount > 1)
    {
        pCentroidX /= (float)mIndexCount;
        pCentroidY /= (float)mIndexCount;
        pCentroidZ /= (float)mIndexCount;
    }
}



FModelData *FModelDataIndexed::GetData()
{
    FModelData *aResult = new FModelData();
    
    if(mIndexCount > 0)
    {
        int aIndex;
        
        if(mXYZCount)
        {
            for(int i=0;i<mIndexCount;i++)
            {            
                aIndex = mIndex[i] * 3;
                float aX = mXYZ[aIndex + 0];
                float aY = mXYZ[aIndex + 1];
                float aZ = mXYZ[aIndex + 2];
                aResult->AddXYZ(aX, aY, aZ);
            }
        }
        
        if(mUVWCount)
        {
            for(int i=0;i<mIndexCount;i++)
            {            
                aIndex = mIndex[i] * 3;
                float aU = mUVW[aIndex + 0];
                float aV = mUVW[aIndex + 1];
                float aW = mUVW[aIndex + 2];
                aResult->AddUVW(aU, aV, aW);
            }
        }
        
        if(mNormalCount)
        {
            for(int i=0;i<mIndexCount;i++)
            {            
                aIndex = mIndex[i] * 3;
                float aNormX = mNormal[aIndex + 0];
                float aNormY = mNormal[aIndex + 1];
                float aNormZ = mNormal[aIndex + 2];
                aResult->AddNormal(aNormX, aNormY, aNormZ);
            }
        }
        
    }
    else
    {
        aResult->CopyXYZ(mXYZ, mXYZCount);
        aResult->CopyXYZ(mUVW, mUVWCount);
        aResult->CopyXYZ(mNormal, mNormalCount);
        
        
    }
    
    return aResult;
}

void FModelDataIndexed::DiscardIndices() {
    if (mIndexCount > 0) {
        delete [] mIndex;
        mIndexCount = 0;
        mIndexSize = 0;
    }
    mIndex = NULL;
}

FModelDataIndexed *FModelDataIndexed::Clone() {
    FModelDataIndexed *aClone=new FModelDataIndexed();
    aClone->CopyXYZ(mXYZ, mXYZCount);
    aClone->CopyUVW(mUVW, mUVWCount);
    aClone->CopyNorm(mNormal, mNormalCount);
    aClone->CopyIndex(mIndex, mIndexCount);
    return aClone;
}

void FModelDataIndexed::Clone(FModelDataIndexed *pTarget)
{
    Free();
    if(pTarget)
    {
        CopyXYZ(pTarget->mXYZ, pTarget->mXYZCount);
        CopyUVW(pTarget->mUVW, pTarget->mUVWCount);
        CopyNorm(pTarget->mNormal, pTarget->mNormalCount);
        CopyIndex(pTarget->mIndex, pTarget->mIndexCount);
    }
}



void FModelDataIndexed::Save(const char *pFile)
{
    FFile aFile;
    Save(&aFile);
    aFile.Save(pFile);
}

void FModelDataIndexed::Save(FFile *pFile)
{
    if(!pFile)return;
    
    FModelData::Save(pFile);
    
    pFile->WriteInt(mIndexCount);
    
    for(int i=0;i<mIndexCount;i++)
    {
        pFile->WriteShort(mIndex[i]);
    }
}

void FModelDataIndexed::LoadData(FFile *pFile)
{
    if(!pFile)return;
    
    FModelData::LoadData(pFile);
    
    int aIndexCount = pFile->ReadInt();

    DiscardIndices();
    
    if(aIndexCount > 0)
    {
        SizeIndex(aIndexCount);
        
        mIndexCount = aIndexCount;
        
        for(int i=0;i<mIndexCount;i++)
        {
            mIndex[i] = pFile->ReadShort();
        }
    }
}

void FModelDataIndexed::LoadData(const char *pFile)
{
    FFile aFile;
    aFile.Load(pFile);
    LoadData(&aFile);
}



void FModelDataIndexed::PrintCode()
{
    //float aXYZ[5] = {5.0f, 1.25f, 0.5f, 0.5f, 1.0f};
    
    int aCount;
    
    aCount = mXYZCount * 3;
    Log("static float aXYZ[%d]={", aCount);
    for(int i=0;i<aCount;i++)
    {
        Log("%.1f", mXYZ[i]);
        if(i != (aCount - 1))
        {
            Log(",");
        }
        else
        {
            Log("};\n");
        }
    }
    
    aCount = mUVWCount * 3;
    Log("static float aUVW[%d]={", aCount);
    for(int i=0;i<aCount;i++)
    {
        Log("%.2f", mUVW[i]);
        if(i != (aCount - 1))
        {
            Log(",");
        }
        else
        {
            Log("};\n");
        }
    }
    
    aCount = mNormalCount * 3;
    Log("static float aNormal[%d]={", aCount);
    for(int i=0;i<aCount;i++)
    {
        Log("%f", mNormal[i]);
        if(i != (aCount - 1))
        {
            Log(",");
        }
        else
        {
            Log("};\n");
        }
    }
    
    Log("static unsigned short aIndex[%d]={", mIndexCount);
    for(int i=0;i<mIndexCount;i++)
    {
        Log("%d", mIndex[i]);
        if(i != (mIndexCount - 1))
        {
            Log(",");
        }
        else
        {
            Log("};\n");
        }
    }
}

void FModelDataIndexed::Load(const char *pFile)
{
    
    FString aBasePath = pFile;
    aBasePath.RemoveExtension();
    
    FString aPath = aBasePath + FString(".3di");
    
    LoadData(aPath.c());
    
    if(mXYZCount <= 0)
    {
        aPath = aBasePath + FString(".3DI");
        LoadData(aPath.c());
    }
    
    if(mXYZCount <= 0)
    {
        aPath = aBasePath + FString(".obj");
        LoadOBJ(aPath.c());
    }
    
    if(mXYZCount <= 0)
    {
        aPath = aBasePath + FString(".OBJ");
        LoadOBJ(aPath.c());
    }
    
}

/*
void FModelDataIndexed::Load(const char *pFileStart, int pIndex, const char *pFileEnd)
{
    FString aPath = FString(pFileStart) + FString(pIndex) + FString(pFileEnd);
    Load(aPath.c());
}
*/


void FModelDataIndexed::LoadOBJ(FFile *pFile) {
    Free();
    FModelData aTemp;// = LoadOBJ(pFile);
    aTemp.LoadOBJ(pFile);
    FModelDataOptimizer *aOptimizer = new FModelDataOptimizer();
    aOptimizer->Convert(&aTemp, this);
    delete aOptimizer;
}

void FModelDataIndexed::LoadOBJ(const char *pFile) {
    FFile aFile;
    aFile.Load(pFile);
    LoadOBJ(&aFile);
}

void FModelDataIndexed::Draw() {
    Graphics::DrawModelIndexed(mXYZ, mXYZCount, mUVW, mUVWCount, mNormal, mNormalCount, mIndex, mIndexCount, mTexture);
}

void FModelDataIndexed::Draw(FTexture *pTexture) {
    Graphics::DrawModelIndexed(mXYZ, mXYZCount, mUVW, mUVWCount, mNormal, mNormalCount, mIndex, mIndexCount, pTexture);
}





FModelDataOptimizer::FModelDataOptimizer() {
    mUVW = 0;
    
    mIndex = 0;
    mIndexCount = 0;
    mIndexSize = 0;
    
    mCypher = 0;
    mCypherCount = 0;
    
    mHashTable = 0;
    mHashTableSize = 0;
    
    mIgnoreXYZ = false;
    mIgnoreUVW = false;
    mIgnoreNormal = false;
    
}

FModelDataOptimizer::~FModelDataOptimizer() {
    delete [] mIndex;
    mIndex = NULL;
    
    delete [] mCypher;
    mCypher = NULL;
    
    mIndexCount = 0;
    
    //ClearHashTable();
    delete [] mHashTable;
    mHashTable = NULL;
    mHashTableSize = 0;
}

void FModelDataOptimizer::ClearHashTable() {
    for (int i=0;i<mHashTableSize;i++) {
        FModelDataOptimizerNode *aNode = mHashTable[i];
        while (aNode != NULL) {
            FModelDataOptimizerNode *aNext = aNode->mNextNode;
            delete aNode;
            aNode = aNext;
        }
    }
}

unsigned int FModelDataOptimizer::HashFloat(unsigned int pRunningSum, float pFloat) {
    unsigned int aResult = pRunningSum;
    float aFloat = pFloat;
    char *aChar = ((char*)(&aFloat));
    for (int i=0;i<4;i++) {
        aResult=((aResult << 5) + aResult) ^ ((int)(aChar[i]));
    }
    return aResult;
}

int FModelDataOptimizer::Hash(float pX, float pY, float pZ,
                              float pU, float pV, float pW,
                              float pNormX, float pNormY, float pNormZ)
{
    unsigned int aHash = 5381;
    
    if(mIgnoreXYZ==false)
    {
        aHash = HashFloat(aHash, pX);
        aHash = HashFloat(aHash, pY);
        aHash = HashFloat(aHash, pZ);
    }
    
    if(mIgnoreUVW==false)
    {
        aHash = HashFloat(aHash, pU);
        aHash = HashFloat(aHash, pV);
        aHash = HashFloat(aHash, pW);
    }
    
    if(mIgnoreNormal==false)
    {
        aHash = HashFloat(aHash, pNormX);
        aHash = HashFloat(aHash, pNormY);
        aHash = HashFloat(aHash, pNormZ);
    }
    
    return (int)(aHash % mHashTableSize);
}

int FModelDataOptimizer::PushNode(int pMapToIndex, float pX, float pY, float pZ,
                                  float pU, float pV, float pW,
                                  float pNormX, float pNormY, float pNormZ, FList *pList)
{
    int aResult = 0;
    
    int aCount = pList->mCount;
    
    if(aCount >= mHashTableSize)
    {
        SizeHashTable(aCount + aCount / 1 + 256, pList);
    }
    
    unsigned int aHash = Hash(pX,pY,pZ,
                              pU,pV,pW,
                              pNormX,pNormY,pNormZ);
    
    
    
    FModelDataOptimizerNode *aNode = mHashTable[aHash];
    
    bool aFound = false;
    
    if(aNode)
    {
        while((aNode != 0) && (aFound == false))
        {
            aFound = true;
            
            if(mIgnoreXYZ==false)
            {
                if((aNode->mX != pX) ||
                   (aNode->mY != pY) ||
                   (aNode->mZ != pZ))
                {
                    aFound=false;
                }
            }
            
            if(mIgnoreUVW==false)
            {
                if((aNode->mU != pU) ||
                   (aNode->mV != pV) ||
                   (aNode->mW != pW))
                {
                    aFound=false;
                }
            }
            
            if(mIgnoreNormal==false)
            {
                if((aNode->mNormX != pNormX) ||
                   (aNode->mNormY != pNormY) ||
                   (aNode->mNormZ != pNormZ))
                {
                    aFound=false;
                }
            }
            
            if(aFound)
            {
                aNode->mCount++;
                aResult = aNode->mIndex;
            }
            else
            {
                aNode=aNode->mNextNode;
            }
            
        }
    }
    
    if (aFound == false)
    {
        FModelDataOptimizerNode *aNode=new FModelDataOptimizerNode();
        
        aNode->mCount = 0;
        
        aResult = pList->mCount;
        aNode->mIndex = aResult;
        
        aNode->mX=pX;
        aNode->mY=pY;
        aNode->mZ=pZ;
        
        aNode->mU=pU;
        aNode->mV=pV;
        aNode->mW=pW;
        
        aNode->mNormX=pNormX;
        aNode->mNormY=pNormY;
        aNode->mNormZ=pNormZ;
        
        aNode->mMapIndex=pMapToIndex;
        
        pList->Add(aNode);
        
        if(mHashTable[aHash] == 0)
        {
            mHashTable[aHash] = aNode;
            aNode->mNextNode = 0;
        }
        else
        {
            aNode->mNextNode = mHashTable[aHash];
            mHashTable[aHash] = aNode;
        }
    }
    
    return aResult;
}


void FModelDataOptimizer::Push(FModelData *pData, FList *pList) {
    if(pData) {
        int aCount = pData->mXYZCount;
        float aX, aY, aZ, aU, aV, aW, aNormX, aNormY, aNormZ;
        for(int i=0;i<aCount;i++) {
            aX = pData->GetX(i);
            aY = pData->GetY(i);
            aZ = pData->GetZ(i);
            aU = pData->GetU(i);
            aV = pData->GetV(i);
            aW = pData->GetW(i);
            aNormX = pData->GetNormX(i);
            aNormY = pData->GetNormY(i);
            aNormZ = pData->GetNormZ(i);
            PushNode(-1, aX, aY, aZ, aU, aV, aW, aNormX, aNormY, aNormZ, pList);
        }
    }
}

void FModelDataOptimizer::SizeHashTable(int pSize, FList *pList) {
    delete [] mHashTable;
    mHashTable = NULL;
    
    mHashTableSize = pSize;
    mHashTable = new FModelDataOptimizerNode*[pSize];
    
    for (int i=0;i<pSize;i++)
    {
        mHashTable[i] = 0;
    }
    
    EnumList(FModelDataOptimizerNode, aNode, (*pList))
    {
        aNode->mNextNode = 0;
    }
    
    EnumList(FModelDataOptimizerNode, aNode, (*pList))
    {
        int aHash = Hash(aNode->mX, aNode->mY, aNode->mZ, aNode->mU, aNode->mV, aNode->mW, aNode->mNormX, aNode->mNormY, aNode->mNormZ);
        
        
        if(mHashTable[aHash] == 0)
        {
            mHashTable[aHash] = aNode;
            aNode->mNextNode = 0;
        }
        else
        {
            aNode->mNextNode = mHashTable[aHash];
            mHashTable[aHash] = aNode;
        }
    }
}

void FModelDataOptimizer::PrintOverview()
{
    int aMaximumIndex=0;
    
    for(int i=0;i<mIndexCount;i++)
    {
        if(mIndex[i] > aMaximumIndex)
        {
            aMaximumIndex = mIndex[i];
        }
    }
    
    Log("\n\nDataOptimizer: [Max Ind %d (%f%% Short Max) [%d Indices] [%d Cyphers]\n\n", aMaximumIndex, (((float)aMaximumIndex) / 65535.0f), mIndexCount, mCypherCount);
    
    
}

void FModelDataOptimizer::Print()
{
    Log("Model Codex!\n\n");
    Log("Hash Count[%d] Size[%d]\n", mCypherCount, mHashTableSize);
    
    for(int i=0;i<mHashTableSize;i++)
    {
        FModelDataOptimizerNode *aNode = mHashTable[i];
        
        int aCount=0;
        int aTotal=0;
        
        while(aNode)
        {
            aTotal+=aNode->mCount;
            aCount++;
            aNode = aNode->mNextNode;
        }
        
        if(aCount > 0)
        {
            Log("Index[%d] Has (%d) Codex Nodes! (%d Model Nodes) \n", i, aCount, aTotal);
        }
    }
}

void FModelDataOptimizer::Generate(FModelData *pData)
{
    if(!pData)return;
    
    
    FList aNodeList;
    
    mIndexCount = pData->mXYZCount;
    mIndex = new unsigned int[mIndexCount+1];
    
    float aX, aY, aZ, aU, aV, aW, aNormX, aNormY, aNormZ;
    
    int aCodexIndex;
    
    for(int i=0;i<mIndexCount;i++)
    {
        aX = pData->GetX(i);
        aY = pData->GetY(i);
        aZ = pData->GetZ(i);
        
        if(pData->mUVWCount > 0)
        {
            aU = pData->GetU(i);
            aV = pData->GetV(i);
            aW = pData->GetW(i);
        }
        else
        {
            aU = 0.0f;
            aV = 0.0f;
            aW = 0.0f;
        }
        
        
        if(pData->mNormalCount > 0)
        {
            aNormX = pData->GetNormX(i);
            aNormY = pData->GetNormY(i);
            aNormZ = pData->GetNormZ(i);
        }
        else
        {
            aNormX = 0;
            aNormY = 0;
            aNormZ = 0;
        }
        
        aCodexIndex = PushNode(i, aX, aY, aZ, aU, aV, aW, aNormX, aNormY, aNormZ, &aNodeList);
        
        mIndex[i]=aCodexIndex;
    }
    
    int aHashListCount = aNodeList.mCount;
    mCypherCount = aHashListCount;
    
    mCypher=new unsigned int[aHashListCount + 1];
    
    int aCodexNodeIndex=0;
    
    EnumList(FModelDataOptimizerNode, aNode, aNodeList)
    {
        mCypher[aCodexNodeIndex]=aNode->mMapIndex;
        aCodexNodeIndex++;
    }
    FreeList(FModelDataOptimizerNode, aNodeList)
}

void FModelDataOptimizer::SolveXYZ(FModelData *pReference, FModelData *pTarget) {
    pTarget->SizeXYZ(mCypherCount);
    int aWrapIndex;
    for (int i=0;i<mCypherCount;i++) {
        aWrapIndex = mCypher[i];
        pTarget->AddXYZ(pReference->GetX(aWrapIndex), pReference->GetY(aWrapIndex), pReference->GetZ(aWrapIndex));
    }
}

void FModelDataOptimizer::SolveUVW(FModelData *pReference, FModelData *pTarget) {
    pTarget->SizeUVW(mCypherCount);
    int aWrapIndex;
    for (int i=0;i<mCypherCount;i++) {
        aWrapIndex = mCypher[i];
        pTarget->AddUVW(pReference->GetU(aWrapIndex), pReference->GetV(aWrapIndex), pReference->GetW(aWrapIndex));
    }
}

void FModelDataOptimizer::SolveNormal(FModelData *pReference, FModelData *pTarget) {
    pTarget->SizeNormal(mCypherCount);
    int aWrapIndex;
    for (int i=0;i<mCypherCount;i++) {
        aWrapIndex = mCypher[i];
        pTarget->AddNormal(pReference->GetNormX(aWrapIndex),pReference->GetNormY(aWrapIndex),pReference->GetNormZ(aWrapIndex));
    }
}

void FModelDataOptimizer::Convert(FModelData *pData, FModelDataIndexed *pTarget) {
    if (pTarget != 0) {
        pTarget->Free();
    }
    if ((pData != 0) && (pTarget != 0)) {
        if (mCypherCount <= 0) {
            Generate(pData);
        }
        for (int i=0;i<mCypherCount;i++) {
            int aWrapIndex = mCypher[i];
            pTarget->AddXYZ(pData->GetX(aWrapIndex), pData->GetY(aWrapIndex), pData->GetZ(aWrapIndex));
            
            if (pData->mUVWCount > 0) {
                pTarget->AddUVW(pData->GetU(aWrapIndex), pData->GetV(aWrapIndex), pData->GetW(aWrapIndex));
            }
            if (pData->mNormalCount > 0) {
                pTarget->AddNormal(pData->GetNormX(aWrapIndex),pData->GetNormY(aWrapIndex),pData->GetNormZ(aWrapIndex));
            }
        }
        for (int i=0;i<mIndexCount;i++) {
            pTarget->AddIndex(mIndex[i]);
        }
    }
}

FModelDataIndexed *FModelDataOptimizer::Convert(FModelData *pData) {
    FModelDataIndexed *aResult = new FModelDataIndexed();
    
    Convert(pData, aResult);
    
    /*
     
     if(mCypherCount <= 0)Generate(pData);
     
     for(int i=0;i<mCypherCount;i++)
     {
     int aWrapIndex = mCypher[i];
     
     aResult->AddXYZ(pData->GetX(aWrapIndex), pData->GetY(aWrapIndex), pData->GetZ(aWrapIndex));
     aResult->AddUVW(pData->GetU(aWrapIndex), pData->GetV(aWrapIndex), pData->GetW(aWrapIndex));
     aResult->AddNormal(pData->GetNormX(aWrapIndex),pData->GetNormY(aWrapIndex),pData->GetNormZ(aWrapIndex));
     }
     
     for(int i=0;i<mIndexCount;i++)
     {
     aResult->AddIndex(mIndex[i]);
     }
     
     aResult->PrintOverview();
     */
    
    return aResult;
}




