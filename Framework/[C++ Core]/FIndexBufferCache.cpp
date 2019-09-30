//
//  FIndexBufferCache.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/6/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FIndexBufferCache.hpp"

//
//  FIndexBufferCache.cpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/3/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#include "FIndexBufferCache.hpp"
#include "os_core_graphics.h"

FIndexBufferCacheResult::FIndexBufferCacheResult() {
    mBuffer = NULL;
    mBufferOffset = 0;
    mSuccess = false;
}

FIndexBufferCacheResult::~FIndexBufferCacheResult() {
    
}

FIndexBufferCacheSlice::FIndexBufferCacheSlice() {
    mFetchBuffer = new FBuffer(INDEX_CACHE_SLICE_SIZE, BUFFER_TYPE_ELEMENT);
    mFetchBufferOffset = 0;
    mFetchSuccess = false;
    mInternalBufferOffset = 0;
}

FIndexBufferCacheSlice::~FIndexBufferCacheSlice() {
    delete mFetchBuffer;
    mFetchBuffer = NULL;
    mFetchBufferOffset = 0;
    mFetchSuccess = false;
}

void FIndexBufferCacheSlice::Reset() {
    mFetchBufferOffset = 0;
    mInternalBufferOffset = 0;
    mFetchSuccess = false;
}

bool FIndexBufferCacheSlice::AttemptFetch(int pBytes) {
    bool aResult = false;
    if ((mInternalBufferOffset + pBytes) > INDEX_CACHE_SLICE_SIZE) {
        mFetchSuccess = false;
    } else {
        mFetchSuccess = true;
        mFetchBufferOffset = mInternalBufferOffset;
        mInternalBufferOffset += pBytes;
    }
    return aResult;
}

FIndexBufferCache::FIndexBufferCache() {
    mCurrentSlice = NULL;
}

FIndexBufferCache::~FIndexBufferCache() {
    Purge();
}

void FIndexBufferCache::Purge() {
    if (mCurrentSlice) {
        delete mCurrentSlice;
        mCurrentSlice = NULL;
    }
    FreeList(FIndexBufferCacheSlice, mConsumedSlices);
    FreeList(FIndexBufferCacheSlice, mAvailableSlices);
}

void FIndexBufferCache::Reset() {
    mAvailableSlices.Add(mConsumedSlices);
    mConsumedSlices.RemoveAll();
    if (mCurrentSlice) {
        mCurrentSlice->Reset();
    }
    EnumList(FIndexBufferCacheSlice, aSlice, mAvailableSlices) {
        aSlice->Reset();
    }
}

void FIndexBufferCache::Get(int pSize) {
    if (mCurrentSlice == NULL) {
        if (mAvailableSlices.IsEmpty()) {
            mCurrentSlice = new FIndexBufferCacheSlice();
        } else {
            mCurrentSlice = (FIndexBufferCacheSlice *)mAvailableSlices.PopLast();
        }
        
        //At this point, we must be able to assign the space, otherwise
        //the buffer we are requesting is too large for this module...
        mCurrentSlice->AttemptFetch(pSize);
        if (mCurrentSlice->mFetchSuccess) {
            mResult.mSuccess = true;
            mResult.mBuffer = mCurrentSlice->mFetchBuffer;
            mResult.mBufferOffset = mCurrentSlice->mFetchBufferOffset;
        } else {
            //There is no chance at success with this module...
            mResult.mSuccess = false;
        }
        return;
    }
    
    mCurrentSlice->AttemptFetch(pSize);
    if (mCurrentSlice->mFetchSuccess) {
        mResult.mSuccess = true;
        mResult.mBuffer = mCurrentSlice->mFetchBuffer;
        mResult.mBufferOffset = mCurrentSlice->mFetchBufferOffset;
    } else {
        if (mCurrentSlice->mInternalBufferOffset == 0) {
            //Hard-Failure case, we are requesting too many bytes...
            mResult.mSuccess = false;
        } else {
            
            //We MAY POSSIBLY be able to allocate this memory on another slice...
            mConsumedSlices.Add(mCurrentSlice);
            if (mAvailableSlices.IsEmpty()) {
                mCurrentSlice = new FIndexBufferCacheSlice();
            } else {
                mCurrentSlice = (FIndexBufferCacheSlice *)mAvailableSlices.PopLast();
                mCurrentSlice->Reset();
            }
            
            mCurrentSlice->AttemptFetch(pSize);
            if (mCurrentSlice->mFetchSuccess) {
                mResult.mSuccess = true;
                mResult.mBuffer = mCurrentSlice->mFetchBuffer;
                mResult.mBufferOffset = mCurrentSlice->mFetchBufferOffset;
            } else {
                //There is no chance at success with this module...
                mResult.mSuccess = false;
            }
        }
    }
}
