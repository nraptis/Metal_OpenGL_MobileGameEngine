//
//  OSSoundBufferPool.cpp
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#include <assert.h>

#include "OSSoundBuffer.h"
#include "OSSoundBufferPool.h"
#include "os_core_sound.h"
#include "os_core_includes.h"
#include "core_includes.h"
#include "FApp.hpp"

OSSoundBufferPool gSoundBufferPool;

OSSoundBufferPool::OSSoundBufferPool() {
    for (int i=0;i<SOUND_BUFFER_COUNT;i++) {
        mBufferList[i] = NULL;
    }
    mBufferCount = 0;
}

OSSoundBufferPool::~OSSoundBufferPool() {

}

OSSoundBuffer *OSSoundBufferPool::DequeueBuffer() {
    for (int i=0;i<mBufferCount;i++) {
        OSSoundBuffer *aSoundBuffer = mBufferList[i];
        if (aSoundBuffer->IsAvailable()) {
            return aSoundBuffer;
        }
    }
    if (mBufferCount < SOUND_BUFFER_COUNT) {
        OSSoundBuffer *aSoundBuffer = new OSSoundBuffer();
        aSoundBuffer->SetUp();
        mBufferList[mBufferCount] = aSoundBuffer;
        ++mBufferCount;
        return aSoundBuffer;
    }

    return NULL;
}

void OSSoundBufferPool::BufferComplete(SLAndroidSimpleBufferQueueItf pBufferQueue) {
    for (int i=0;i<mBufferCount;i++) {
        OSSoundBuffer *aSoundBuffer = mBufferList[i];
        if (aSoundBuffer->bqPlayerBufferQueue == pBufferQueue) {
            if (aSoundBuffer->mIsLooping && gAppBase->mActive == true) {
                aSoundBuffer->Loop();
            } else {
                aSoundBuffer->Complete();
            }
            return;
        }
    }
}


