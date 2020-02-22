//
//  FIndexList.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "FIndexList.hpp"


FIndexList::FIndexList()
{
    mCount = 0;
    mSize = 0;
    
    mIndex = 0;
}

FIndexList::~FIndexList()
{
    Clear();
}

void FIndexList::Clear()
{
    delete[] mIndex;
    
    mCount = 0;
    mSize = 0;
    
    mIndex = 0;
    //mY = 0;
}

void FIndexList::Add(GFX_MODEL_INDEX_TYPE pIndex)
{
    if(mCount >= mSize)
    {
        Size(mCount + (mCount / 2) + 1);
    }
    
    mIndex[mCount] = pIndex;
    mCount++;
}

void FIndexList::Add(FIndexList *pList) {
    if (pList) {
        if ((pList->mCount + mCount) > mSize) {
            Size(pList->mCount + mCount);
        }
        for (int i = 0; i<pList->mCount; i++) {
            Add(pList->mIndex[i]);
        }
        
    }
}

GFX_MODEL_INDEX_TYPE FIndexList::Get(int pIndex)
{
    GFX_MODEL_INDEX_TYPE aResult = 0;
    if((pIndex >= 0) && (pIndex < mCount))
    {
        aResult = mIndex[pIndex];
    }
    
    return aResult;
}

void FIndexList::RemoveAll()
{
    mCount = 0;
}

void FIndexList::Size(int pSize)
{
    if(pSize != mSize)
    {
        if(pSize <= 0)
        {
            Clear();
        }
        else
        {
            if(mCount >= pSize)mCount=pSize;
            GFX_MODEL_INDEX_TYPE *aNew = new GFX_MODEL_INDEX_TYPE[pSize];
            for(int i = 0; i<mCount; i++)aNew[i] = mIndex[i];
            for(int i = mCount; i<pSize; i++)aNew[i] = 0;
            
            delete[] mIndex;
            mIndex = aNew;
            mSize = pSize;
        }
    }
}

void FIndexList::Save(FFile *pFile)
{
    if(pFile)
    {
        pFile->WriteInt(mCount);
        
        for(int i = 0; i<mCount; i++)
        {
            pFile->WriteShort(mIndex[i]);
            
            //pFile->WriteFloat(mX[i]);
            //pFile->WriteFloat(mY[i]);
        }
    }
}

void FIndexList::Load(FFile *pFile)
{
    Clear();
    
    if(pFile)
    {
        int aCount = pFile->ReadInt();
        
        Size(aCount);
        for(int i = 0; i<aCount; i++)
        {
            mIndex[i] = pFile->ReadShort();
        }
        mCount = aCount;
    }
}

void FIndexList::Reverse()
{
    if(mCount > 1)
    {
        int aStartIndex = 0;
        int aEndIndex = (mCount - 1);
        
        GFX_MODEL_INDEX_TYPE aHold = 0;
        
        while (aStartIndex < aEndIndex)
        {
            aHold = mIndex[aEndIndex];
            
            mIndex[aEndIndex] = mIndex[aStartIndex];
            
            mIndex[aStartIndex] = aHold;
            
            aStartIndex++;
            aEndIndex--;
        }
    }
}
