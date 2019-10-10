//
//  FBufferCache.cpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/16/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#include "FBufferCache.hpp"
#include "core_includes.h"
#include "FBuffer.hpp"

FBufferCacheSlice::FBufferCacheSlice(int pSize) {
    mIndex = 0;
    mSize = pSize;
}

FBufferCacheSlice::~FBufferCacheSlice() {
    EnumList(FBuffer, aBuffer, mList) {
        delete aBuffer;
    }
    mList.RemoveAll();
}

FBuffer *FBufferCacheSlice::Get() {
    FBuffer *aResult = NULL;
    if (mIndex >= mList.mCount) {
        aResult = new FBuffer(mSize, BUFFER_TYPE_ARRAY);
        mList.Add(aResult);
    } else {
        aResult = (FBuffer *)mList.mData[mIndex];
        
    }
    mIndex++;
    return aResult;
}

void FBufferCacheSlice::Reset() {
    mIndex = 0;
}

FBufferCache::FBufferCache() {
    
}

FBufferCache::~FBufferCache() {
    
}

void FBufferCache::RegisterBuffer(FBuffer *pBuffer) {
    mBufferTable.Add(pBuffer, pBuffer);
}

void FBufferCache::UnregisterBuffer(FBuffer *pBuffer) {
    mBufferTable.Remove(pBuffer);
}

void FBufferCache::UnloadAllBuffers() {
    FHashMapNode *aNode = mBufferTable.mListHead;
    while (aNode) {
        FBuffer *aBuffer = (FBuffer *)aNode->mObject;
        aBuffer->Unload();
        aNode = aNode->mListNext;
    }
}

void FBufferCache::ReloadAllBuffers() {
    FHashMapNode *aNode = mBufferTable.mListHead;
    while (aNode) {
        FBuffer *aBuffer = (FBuffer *)aNode->mObject;
        aBuffer->Realize();
        aNode = aNode->mListNext;
    }
}

void FBufferCache::Reset() {
    FIntMapNode *aNode = mSliceTable.mListHead;
    while (aNode) {
        FBufferCacheSlice *aSlice = (FBufferCacheSlice *)aNode->mObject;
        aSlice->Reset();
        aNode = aNode->mListNext;
    }
    
}

FBuffer *FBufferCache::GetArrayBuffer(int pSize) {
    FBuffer *aResult = NULL;
    if (pSize > 0) {
        FBufferCacheSlice *aSlice = (FBufferCacheSlice *)mSliceTable.Get(pSize);
        if (aSlice == NULL) {
            aSlice = new FBufferCacheSlice(pSize);
            mSliceTable.Add(pSize, aSlice);
        }
        aResult = aSlice->Get();
    }
    
    return aResult;
}


