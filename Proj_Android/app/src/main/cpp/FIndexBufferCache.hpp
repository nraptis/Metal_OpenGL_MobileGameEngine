//
//  FIndexBufferCache.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/6/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FIndexBufferCache_hpp
#define FIndexBufferCache_hpp

#include "FList.hpp"
#include "FIndexList.hpp"
#include "FBuffer.hpp"

#define INDEX_CACHE_SLICE_SIZE 32768
//8192   16384   32768   65536
//131072   262144   524288

class FIndexBufferCacheResult {
public:
    FIndexBufferCacheResult();
    ~FIndexBufferCacheResult();
    
    FBuffer                         *mBuffer;
    int                             mBufferOffset;
    bool                            mSuccess;
};

class FIndexBufferCacheSlice {
public:
    FIndexBufferCacheSlice();
    ~FIndexBufferCacheSlice();
    
    void                            Reset();
    
    //We just want to see if we can fetch this number of bytes from
    //the slice... If unable, use a different slice (the slices should
    //be larger than the largest buffer required by the program...)
    bool                            AttemptFetch(int pBytes);
    
    //After we attempt a fetch, look and see if we were able to spare
    //the requested number of bytes...
    bool                            mFetchSuccess;
    
    FBuffer                         *mFetchBuffer;
    int                             mFetchBufferOffset;
    
    int                             mInternalBufferOffset;
};

class FIndexBufferCache {
public:
    FIndexBufferCache();
    ~FIndexBufferCache();
    
    //Delete all memory from video card... Will need to respawn...
    void                            Purge();
    
    //Important... Reset this cache on every draw...
    void                            Reset();
    
    void                            Get(int pSize);
    
    FIndexBufferCacheResult         mResult;
    FIndexBufferCacheSlice          *mCurrentSlice;
    
    FList                           mAvailableSlices;
    FList                           mConsumedSlices;
};

#endif /* FIndexBufferCache_hpp */
