//
//  FIntList.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/3/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FIntList.hpp"

FIntList::FIntList() {
    mCount = 0;
    mSize = 0;
    mData = 0;
}

FIntList::~FIntList() {
    Clear();
}

void FIntList::Clear() {
    delete[] mData;
    mCount = 0;
    mSize = 0;
    mData = 0;
}

void FIntList::Add(int pIndex) {
    if (mCount >= mSize) {
        Size(mCount + (mCount / 2) + 1);
    }
    mData[mCount] = pIndex;
    mCount++;
}

void FIntList::Add(FIntList *pList) {
    if (pList) {
        if((pList->mCount + mCount) > mSize) {
            Size(pList->mCount + mCount);
        }
        for (int i = 0; i<pList->mCount; i++) {
            Add(pList->mData[i]);
        }
    }
}

int FIntList::Get(int pIndex) {
    int aResult = 0;
    if ((pIndex >= 0) && (pIndex < mCount)) {
        aResult = mData[pIndex];
    }
    return aResult;
}

void FIntList::RemoveAll() {
    mCount = 0;
}

void FIntList::Size(int pSize) {
    if (pSize != mSize) {
        if (pSize <= 0) {
            Clear();
        } else {
            if(mCount >= pSize)mCount=pSize;
            int *aNew = new int[pSize];
            for(int i = 0; i<mCount; i++)aNew[i] = mData[i];
            for(int i = mCount; i<pSize; i++)aNew[i] = 0;
            delete[] mData;
            mData = aNew;
            mSize = pSize;
        }
    }
}

void FIntList::Save(FFile *pFile) {
    if (pFile) {
        pFile->WriteInt(mCount);
        for (int i = 0; i<mCount; i++) {
            pFile->WriteInt(mData[i]);
        }
    }
}

void FIntList::Load(FFile *pFile) {
    Clear();
    if (pFile) {
        int aCount = pFile->ReadInt();
        Size(aCount);
        for (int i = 0; i<aCount; i++) {
            mData[i] = pFile->ReadInt();
        }
        mCount = aCount;
    }
}

void FIntList::Reverse() {
    if (mCount > 1) {
        int aStartIndex = 0;
        int aEndIndex = (mCount - 1);
        int aHold = 0;
        while (aStartIndex < aEndIndex) {
            aHold = mData[aEndIndex];
            mData[aEndIndex] = mData[aStartIndex];
            mData[aStartIndex] = aHold;
            aStartIndex++;
            aEndIndex--;
        }
    }
}

int FIntList::PopFirst() {
    int aResult = 0;
    if (mCount > 0) {
        aResult = mData[0];
        for (int i=1;i<mCount;i++) {
            mData[i-1]=mData[i];
        }
        mCount--;
    }
    return aResult;
}

int FIntList::PopLast() {
    int aResult = 0;
    if (mCount > 0) {
        aResult = mData[mCount - 1];
        mCount--;
    }
    return aResult;
}
