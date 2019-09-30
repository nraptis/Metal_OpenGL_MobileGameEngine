//
//  OSSoundBufferPool.h
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#ifndef FRAMEWORK_SOUND_BUFFER_POOL_ANDROID_H
#define FRAMEWORK_SOUND_BUFFER_POOL_ANDROID_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#define SOUND_BUFFER_COUNT 16

class FSoundDataAndroid;
class OSSoundBuffer;
class OSSoundBufferPool {
public:
    OSSoundBufferPool();
    ~OSSoundBufferPool();

    OSSoundBuffer                   *DequeueBuffer();

    void                            BufferComplete(SLAndroidSimpleBufferQueueItf pBufferQueue);

    OSSoundBuffer                   *mBufferList[SOUND_BUFFER_COUNT];
    int                             mBufferCount;
};

extern OSSoundBufferPool gSoundBufferPool;

#endif


