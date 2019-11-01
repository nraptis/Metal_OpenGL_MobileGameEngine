//
//  FBufferCache.hpp
//  Crazy Darts 2 Mac
//
//  Created by Nicholas Raptis on 3/16/19.
//  Copyright © 2019 Froggy Studios. All rights reserved.
//

#ifndef FBufferCache_hpp
#define FBufferCache_hpp

#include "FHashMap.hpp"

class FBuffer;

class FBufferCacheSlice {
public:
    FBufferCacheSlice(int pSize);
    ~FBufferCacheSlice();
    
    void                                        Reset();
    
    int                                         mSize;
    
    FList                                       mList;
    int                                         mIndex;
    
    FBuffer                                     *Get();
};

class FBufferCache {
public:
    
    FBufferCache();
    virtual ~FBufferCache();
    
    //When buffers are created and destroyed, we must register and unregister them...
    //This allows older graphics languages to huck and returb the buffz more easy.
    void                                        RegisterBuffer(FBuffer *pBuffer);
    void                                        UnregisterBuffer(FBuffer *pBuffer);
    
    void                                        UnloadAllBuffers();
    void                                        ReloadAllBuffers();
    
    FHashMap                                    mBufferTable;
    
    FIntMap                                     mSliceTable;
    
    void                                        Reset();
    FBuffer                                     *GetArrayBuffer(int pSize);
};



#endif /* FBufferCache_hpp */
