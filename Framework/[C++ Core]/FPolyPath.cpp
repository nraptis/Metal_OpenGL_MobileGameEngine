//
//  FPolyPath.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/30/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "FPolyPath.hpp"
#include "FApp.hpp"
#include "core_includes.h"


FPolyPathInterp::FPolyPathInterp() {
    mValid = false;
    mIndexStart = -1;
    mIndexEnd = -1;
    mPercentInterp = 0.0f;
    mX = 0.0f;
    mY = 0.0f;
    mNormX = 0.0f;
    mNormY = -1.0f;
    //mWidth = 0.0f;
    //mRotation = 0.0f;
}

FPolyPathInterp::~FPolyPathInterp() {
    
}

FPolyPath::FPolyPath() {
    mCount=0;
    mSize=0;
    mLength = 0.0f;
    mRefresh = true;
    mClosed = false;
    mWrap = false;
    mFlipNormals = true;
    mX = 0;
    mY = 0;
    mDistance = 0;
    mPercent = 0;
    mDirX = 0;
    mDirY = 0;
    mNormX = 0;
    mNormY = 0;
    //mLerpX = 0;
    //mLerpY = 0;
    //mWidth = 0;
    //mRotation = 0;
    //mFaceCenterX = 0;
    //mFaceCenterY = 0;
    //mFaceCenterRotation = 0;
    mCenterX = 0.0f;
    mCenterY = 0.0f;
}

FPolyPath::~FPolyPath() {
    Clear();
}

void FPolyPath::Clear() {
    delete [] mX;
    mCount=0;
    mSize=0;
    mLength = 0.0f;
    mRefresh = true;
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    mX = 0;
    mY = 0;
    mDistance = 0;
    mPercent = 0;
    mDirX = 0;
    mDirY = 0;
    mNormX = 0;
    mNormY = 0;
    //mLerpX = 0;
    //mLerpY = 0;
    //mWidth = 0;
    //mRotation = 0;
    //mFaceCenterX = 0;
    //mFaceCenterY = 0;
    //mFaceCenterRotation = 0;
}

void FPolyPath::RemoveAll() {
    mCount = 0;
    mRefresh = true;
}

void FPolyPath::Add(float pX, float pY) {
    if (mCount >= mSize) {
        Size(mCount + (mCount / 2) + 1);
    }
    mX[mCount] = pX;
    mY[mCount] = pY;
    mCount++;
    mRefresh = true;
}

void FPolyPath::Add(FPointList *pList) {
    if (pList) {
        for (int i=0;i<pList->mCount;i++) {
            Add(pList->mX[i], pList->mY[i]);
        }
    }
    mRefresh = true;
}

void FPolyPath::Set(int pIndex, float pX, float pY) {
    if (pIndex >= mSize) {
        SetSize(pIndex + (pIndex / 2) + 1);
    }
    if (pIndex >= mCount) {
        mCount = (pIndex + 1);
    }
    
    if (pIndex >= 0) {
        mX[pIndex] = pX;
        mY[pIndex] = pY;
        mRefresh = true;
    }
}





void FPolyPath::Size(int pSize) {
    if (pSize != mSize) {
        if (pSize <= 0) {
            Clear();
        } else {
            if (mCount >= pSize) {
                mCount = pSize;
            }
            
            int aSize = pSize + 1;
            
            float *aNewX = new float[aSize * 8 + 8];
            float *aNewY = aNewX + aSize;
            float *aNewDistance = aNewY + aSize;
            float *aNewPercent = aNewDistance + aSize;
            float *aNewDirX = aNewPercent + aSize;
            float *aNewDirY = aNewDirX + aSize;
            float *aNewNormX = aNewDirY + aSize;
            float *aNewNormY = aNewNormX + aSize;
            //float *aNewLerpX = aNewNormY + aSize;
            //float *aNewLerpY = aNewLerpX + aSize;
            //float *aNewWidth = aNewLerpY + aSize;
            //float *aNewRotation = aNewNormY + aSize;
            
            //float *aNewFaceCenterX = aNewRotation + aSize;
            //float *aNewFaceCenterY = aNewFaceCenterX + aSize;
            //float *aNewFaceCenterRotation = aNewRotation + aSize;
            
            for(int i=0;i<mCount;i++)aNewX[i] = mX[i];
            for(int i=0;i<mCount;i++)aNewY[i] = mY[i];
            
            for(int i=0;i<mCount;i++)aNewDistance[i] = mDistance[i];
            for(int i=0;i<mCount;i++)aNewPercent[i] = mPercent[i];
            
            for(int i=0;i<mCount;i++)aNewDirX[i] = mDirX[i];
            for(int i=0;i<mCount;i++)aNewDirY[i] = mDirY[i];
            
            for(int i=0;i<mCount;i++)aNewNormX[i] = mNormX[i];
            for(int i=0;i<mCount;i++)aNewNormY[i] = mNormY[i];
            
            //for(int i=0;i<mCount;i++)aNewLerpX[i] = mLerpX[i];
            //for(int i=0;i<mCount;i++)aNewLerpY[i] = mLerpY[i];
            //for(int i=0;i<mCount;i++)aNewWidth[i] = mWidth[i];
            //for(int i=0;i<mCount;i++)aNewRotation[i] = mRotation[i];
            
            //for(int i=0;i<mCount;i++)aNewFaceCenterX[i] = mFaceCenterX[i];
            //for(int i=0;i<mCount;i++)aNewFaceCenterY[i] = mFaceCenterY[i];
            //for(int i=0;i<mCount;i++)aNewFaceCenterRotation[i] = mFaceCenterRotation[i];
            
            for(int i=mCount;i<aSize;i++)aNewX[i] = 0.0f;
            for(int i=mCount;i<aSize;i++)aNewY[i] = 0.0f;
            
            for(int i=mCount;i<aSize;i++)aNewDistance[i] = 0.0f;
            for(int i=mCount;i<aSize;i++)aNewPercent[i] = 0.0f;
            
            for(int i=mCount;i<aSize;i++)aNewDirX[i] = 0.0f;
            for(int i=mCount;i<aSize;i++)aNewDirY[i] = -1.0f;
            for(int i=mCount;i<aSize;i++)aNewNormX[i] = 1.0f;
            for(int i=mCount;i<aSize;i++)aNewNormY[i] = 0.0f;
            //for(int i=mCount;i<aSize;i++)aNewLerpX[i] = 1.0f;
            //for(int i=mCount;i<aSize;i++)aNewLerpY[i] = 0.0f;
            //for(int i=mCount;i<aSize;i++)aNewWidth[i] = 1.0f;
            //for(int i=mCount;i<aSize;i++)aNewRotation[i] = 0.0f;
            //for(int i=mCount;i<aSize;i++)aNewFaceCenterX[i] = -1.0f;
            //for(int i=mCount;i<aSize;i++)aNewFaceCenterY[i] = 0.0f;
            //for(int i=mCount;i<aSize;i++)aNewFaceCenterRotation[i] = 0.0f;

            delete [] mX;
            
            mX = aNewX;
            mY = aNewY;
            mDistance = aNewDistance;
            mPercent = aNewPercent;
            mDirX = aNewDirX;
            mDirY = aNewDirY;
            mNormX = aNewNormX;
            mNormY = aNewNormY;
            //mLerpX = aNewLerpX;
            //mLerpY = aNewLerpY;
            //mWidth = aNewWidth;
            //mRotation = aNewRotation;
            //mFaceCenterX = aNewFaceCenterX;
            //mFaceCenterY = aNewFaceCenterY;
            //mFaceCenterRotation = aNewFaceCenterRotation;
            
            mSize = pSize;
            mRefresh = true;
        }
    }
}

void FPolyPath::Draw()
{
    if(mRefresh)
    {
        Generate();
    }
    
    DrawPoints();
    DrawEdges();
    DrawNormals();
    
    Graphics::SetColor();
}

void FPolyPath::DrawPoints()
{
    float aX = 0.0f;
    float aY = 0.0f;
    
    float aSize = 8.0f;
    float aSize2 = aSize * 0.5f;
    
    for(int i=0;i<mCount;i++)
    {
        aX = mX[i];
        aY = mY[i];
        Graphics::DrawRect(aX - aSize2, aY - aSize2, aSize, aSize);
        //gAppBase->mSysFont.Center(FString(i).c(), aX, aY - 30.0f);
        
    }
    
    
}

void FPolyPath::DrawEdges()
{
    if(mCount > 1)
    {
    
    int aIndex = 0;
    
    float aX = 0.0f;
    float aY = 0.0f;
    
    float aLastX = aX;
    float aLastY = aY;
    
    if(mClosed)
    {
        aIndex = 0;
        aLastX = mX[mCount - 1];
        aLastY = mY[mCount - 1];
    }
    else
    {
        aIndex = 1;
        aLastX = mX[0];
        aLastY = mY[0];
    }
    
    while(aIndex < mCount)
    {
        aX = mX[aIndex];
        aY = mY[aIndex];
        
        Graphics::DrawLine(aLastX, aLastY, aX, aY, 1.0f);
        
        aLastX = aX;
        aLastY = aY;
        
        aIndex++;
    }
    }
}

void FPolyPath::DrawNormals()
{
    float aX = 0.0f;
    float aY = 0.0f;
    
    float aDrawX = 0.0f;
    float aDrawY = 0.0f;
    
    float aLength = 10.0f;
    
    int aCount = mCount;
    
    if(aCount > 0)
    {
        if(mClosed)aCount++;
        
    }
    
    
    for(int aIndex = 0;aIndex < aCount; aIndex++)
    {
        aX = mX[aIndex];
        aY = mY[aIndex];
        
        aDrawX = mNormX[aIndex] * aLength;
        aDrawY = mNormY[aIndex] * aLength;
        
        aDrawX += aX;
        aDrawY += aY;
        
        
        Graphics::DrawLine(aX, aY, aDrawX, aDrawY);
        
        Graphics::DrawPoint(aDrawX, aDrawY, 3.0f);
        
        
        
    }
    
}

bool FPolyPath::Interpolate(float pLength)
{
    return Interpolate(&mInterpolater, pLength);
}

bool FPolyPath::Interpolate(FPolyPathInterp *pInterp, float pLength) {
    bool aResult = false;
    
    if (mRefresh) {
        Generate();
    }
    
    if (pInterp) {
        pInterp->mValid = false;
        pInterp->mIndexStart = -1;
        pInterp->mIndexEnd = -1;
        
        
        if ((mLength > 0.025f) && (mCount > 1)) {
            if (mWrap) {
                if (pLength > mLength) {
                    int aLoops = 32;
                    while ((aLoops > 0) && (pLength > mLength)) {
                        pLength -= mLength;
                        aLoops--;
                    }
                }
                
                if (pLength < 0.0f) {
                    int aLoops = 32;
                    while ((aLoops > 0) && (pLength < 0.0f)) {
                        pLength += mLength;
                        aLoops--;
                    }
                }
            } else {
                if (pLength > mLength) {
                    pLength = mLength;
                }
            }
            
            int aInd1 = 0;
            int aInd2 = 0;
            
            int aCount = mCount;
            if (mClosed) { aCount++; }
            
            int aMid = 0;
            int aHigh = mCount;
            while (aInd2 != aHigh) {
                aMid = (aInd2 + aHigh) / 2;
                
                if (mDistance[aMid] <= pLength) {
                    aInd2 = aMid + 1;
                } else {
                    aHigh = aMid;
                }
            }
            
            bool aLoopStart = false;
            aInd1 = (aInd2 - 1);
            if (aInd1 < 0) {
                aLoopStart = true;
                aInd1 = (aCount - 1);
            }
            
            float aLengthStart = mDistance[aInd1];
            float aLengthEnd = mDistance[aInd2];
            
            if (aLoopStart == true) {
                aLengthEnd += mLength;
            }
            
            float aRange = aLengthEnd - aLengthStart;
            float aPercent = 0.0f;
            
            if (aRange > SQRT_EPSILON) {
                aPercent = (float)(((pLength - aLengthStart)) / aRange);
            }
            
            pInterp->mValid = true;
            aResult = true;
            
            pInterp->mPercentInterp = aPercent;
            
            pInterp->mIndexStart = aInd1;
            pInterp->mIndexEnd = aInd2;
            
            
            pInterp->mLineX1 = mX[aInd1];
            pInterp->mLineY1 = mY[aInd1];
            pInterp->mLineX2 = mX[aInd2];
            pInterp->mLineY2 = mY[aInd2];
            
            //pInterp->mLineRotation = mRotation[aInd1];
            
            pInterp->mX = mX[aInd1] + (mX[aInd2] - mX[aInd1]) * aPercent;
            pInterp->mY = mY[aInd1] + (mY[aInd2] - mY[aInd1]) * aPercent;
            
            

        }
    }
    
    return aResult;
}


void FPolyPath::GetWithDist(float pDistance, float &pX, float &pY) {
    Interpolate(pDistance);
    pX = mInterpolater.mX;
    pY = mInterpolater.mY;
}

void FPolyPath::GetWithPercent(float pPercent, float &pX, float &pY) {
    GetWithDist(pPercent * mLength, pX, pY);
}

void FPolyPath::GetRandom(float &pX, float &pY) {
    GetWithDist(gRand.GetFloat(mLength), pX, pY);
}

void FPolyPath::Save(FFile *pFile) {
    if (pFile) {
        pFile->WriteInt(mCount);
        for (int i=0;i<mCount;i++) {
            pFile->WriteFloat(mX[i]);
            pFile->WriteFloat(mY[i]);
        }
    }
}

void FPolyPath::Load(FFile *pFile) {
    Clear();
    if (pFile) {
        int aCount = pFile->ReadInt();
        Size(aCount);
        float aReadX = 0.0f;
        float aReadY = 0.0f;
        for (int i=0;i<aCount;i++) {
            aReadX = pFile->ReadFloat();
            aReadY = pFile->ReadFloat();
            Add(aReadX, aReadY);
        }
    }
}


void FPolyPath::Generate() {
    mRefresh = false;
    mLength = 0;
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    
    if (mCount > 1) {
        float aDiffX = 0.0f;
        float aDiffY = 0.0f;
        float aDist = 0.0f;
        
        int aIndex = 1;
        
        float aX = 0.0f;
        float aY = 0.0f;
        
        float aLastX = mX[0];
        float aLastY = mY[0];
        
        mDistance[0] = 0.0f;
        mPercent[0] = 0.0f;
        
        int aCount = mCount;
        if (mClosed) {
            aCount++;
            mX[mCount] = mX[0];
            mY[mCount] = mY[0];
        }
        
        while (aIndex < aCount) {
            aX = mX[aIndex];
            aY = mY[aIndex];
            
            aDiffX = (aX - aLastX);
            aDiffY = (aY - aLastY);
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            
            if (aDist > SQRT_EPSILON) {
                aDist = sqrtf(aDist);
                aDiffX /= aDist;
                aDiffY /= aDist;
            } else {
                aDist = 0.025f;
                aDiffX = 0.0f;
                aDiffY = -1.0f;
            }
            
            mDirX[aIndex] = aDiffX;
            mDirY[aIndex] = aDiffY;
            
            mNormX[aIndex] = -aDiffY;
            mNormY[aIndex] = aDiffX;
            
            mLength += aDist;
            mDistance[aIndex] = mLength;
            
            aLastX = aX;
            aLastY = aY;
            aIndex++;
        }
        
        mDistance[mCount] = mLength;
        mX[mCount] = mX[0];
        mY[mCount] = mY[0];
        
        /*
         mDirX[mCount] = mDirX[0];
         mDirY[mCount] = mDirY[0];
         mNormX[mCount] = mNormX[0];
         mNormY[mCount] = mNormY[0];
         mWidth[mCount] = mWidth[0];
        */
        mDirX[0] = mDirX[mCount];
        mDirY[0] = mDirY[mCount];
        mNormX[0] = mNormX[mCount];
        mNormY[0] = mNormY[mCount];
        
        
        
        if(mFlipNormals)
        {
            aIndex = 0;
            while(aIndex < aCount)
            {
                mNormX[aIndex] = -(mNormX[aIndex]);
                mNormY[aIndex] = -(mNormY[aIndex]);
                aIndex++;
            }
        }
        
        aIndex = 0;
        while(aIndex < mCount)
        {
            mCenterX += mX[aIndex];
            mCenterY += mY[aIndex];
            aIndex++;
        }
        
        mCenterX /= ((float)mCount);
        mCenterY /= ((float)mCount);
        
        
        
        aIndex = 0;
        while(aIndex < mCount)
        {
            aDiffX = mX[aIndex] - mCenterX;
            aDiffY = mY[aIndex] - mCenterY;
            
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            
            if (aDist > SQRT_EPSILON) {
                aDist = sqrtf(aDist);
                aDiffX /= aDist;
                aDiffY /= aDist;
            } else {
                aDist = 0.025f;
                aDiffX = 0.0f;
                aDiffY = -1.0f;
            }
            
            aIndex++;
        }
        
        //mCenterX /= ((float)mCount);
        
        
        
        
        if (mLength > SQRT_EPSILON) {
            aIndex = 0;
            while (aIndex < aCount) {
                mPercent[aIndex] = mDistance[aIndex] / mLength;
                aIndex++;
            }
        }
    }
}
