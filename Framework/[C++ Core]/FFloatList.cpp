//
//  FFloatList.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "FFloatList.hpp"
#include "core_includes.h"

FFloatList::FFloatList() {
    mCount = 0;
    mSize = 0;
    mData = 0;
}

FFloatList::~FFloatList() {
    Clear();
}

void FFloatList::Clear() {
    delete[] mData;
    mCount = 0;
    mSize = 0;
    mData = NULL;
}

void FFloatList::Add(float pFloat) {
    if (mCount >= mSize) {
        Size(mCount + (mCount / 2) + 1);
    }
    
    mData[mCount] = pFloat;
    mCount++;
}

void FFloatList::Add(FFloatList *pList) {
    if (pList) {
        if ((pList->mCount + mCount) > mSize) {
            Size(pList->mCount + mCount);
        }
        for (int i = 0; i<pList->mCount; i++) {
            Add(pList->mData[i]);
        }
    }
}

float FFloatList::Get(int pSlot) {
    float aResult = 0;
    if ((pSlot >= 0) && (pSlot < mCount)) {
        aResult = mData[pSlot];
    }
    return aResult;
}

void FFloatList::Set(int pSlot, float pFloat) {
    if (pSlot >= mSize) {
        SetSize(pSlot + 1);
    }
    if (pSlot >= mCount) {
        mCount = (pSlot + 1);
    }
    
    if (pSlot >= 0) {
        mData[pSlot] = pFloat;
    }
}

void FFloatList::RemoveAll() {
    mCount = 0;
}

void FFloatList::Reset() {
    mCount = 0;
}

void FFloatList::Size(int pSize) {
    if (pSize != mSize) {
        if (pSize <= 0) {
            Clear();
        } else {
            if (mCount >= pSize) { mCount = pSize; }
            float *aNew = new float[pSize];
            for (int i = 0; i<mCount; i++) { aNew[i] = mData[i]; }
            for (int i = mCount; i<pSize; i++) { aNew[i] = NULL; }
            
            delete[] mData;
            mData = aNew;
            mSize = pSize;
        }
    }
}

void FFloatList::Save(FFile *pFile) {
    if (pFile != NULL) {
        pFile->WriteInt(mCount);
        for (int i=0;i<mCount;i++) {
            pFile->WriteFloat(mData[i]);
        }
    }
}

void FFloatList::Load(FFile *pFile) {
    Clear();
    if (pFile != NULL) {
        int aCount = pFile->ReadInt();
        Size(aCount);
        for (int i=0;i<aCount;i++) {
            mData[i] = pFile->ReadFloat();
        }
        mCount = aCount;
    }
}

void FFloatList::Reverse() {
    if (mCount > 1) {
        int aStartIndex = 0;
        int aEndIndex = (mCount - 1);
        float aHold = 0;
        while (aStartIndex < aEndIndex) {
            aHold = mData[aEndIndex];
            mData[aEndIndex] = mData[aStartIndex];
            mData[aStartIndex] = aHold;
            aStartIndex++;
            aEndIndex--;
        }
    }
}

void FFloatList::Clone(FFloatList *pPointList) {
    if (pPointList != NULL) {
        if (pPointList->mCount > mSize) {
            Size(pPointList->mCount);
        }
        Reset();
        int aCount = pPointList->mCount;
        for (int i=0;i<aCount;i++) {
            Add(pPointList->mData[i]);
        }
    }
}

void FFloatList::Shuffle() {
    float aHold = 0;
    int aRand = 0;
    for (int i=0;i<mCount;i++) {
        aHold = mData[i];
        aRand = gRand.Get(mCount);
        mData[i] = mData[aRand];
        mData[aRand] = aHold;
    }
}
