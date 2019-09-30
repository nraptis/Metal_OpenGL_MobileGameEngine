//
//  FFloatBufferCache.hpp
//  MetalLearning
//
//  Created by Nicholas Raptis on 2/3/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#ifndef FFloatBufferCache_hpp
#define FFloatBufferCache_hpp

#include "FList.hpp"
#include "FBuffer.hpp"

//... In BYTES (should be multiple of 4...)
//524288
//#define FLOAT_CACHE_SLICE_SIZE 32768
//#define FLOAT_CACHE_SLICE_SIZE 262144
//#define FLOAT_CACHE_SLICE_SIZE 65536
#define FLOAT_CACHE_SLICE_SIZE 65536

class FFloatBufferCacheResult {
public:
    FFloatBufferCacheResult();
    ~FFloatBufferCacheResult();
    
    FBuffer                         *mBuffer;
    int                             mBufferOffset;
    bool                            mSuccess;
};

class FFloatBufferCacheSlice {
public:
    
    FFloatBufferCacheSlice();
    ~FFloatBufferCacheSlice();
    
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


class FFloatBufferCacheByteAligned256 {
public:
    FFloatBufferCacheByteAligned256();
    ~FFloatBufferCacheByteAligned256();
    
    //Delete all memory from video card... Will need to respawn...
    void                            Purge();
    
    //Important... Reset this cache on every draw...
    void                            Reset();
    
    void                            Get(int pSize);
    
    FFloatBufferCacheResult         mResult;
    
    FFloatBufferCacheSlice          *mCurrentSlice;
    
    FList                           mAvailableSlices;
    FList                           mConsumedSlices;
};

#endif
