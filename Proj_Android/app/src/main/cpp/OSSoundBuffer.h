//
//  OSSoundBuffer.h
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#ifndef FRAMEWORK_MUSIC_BUFFER_ANDROID_H
#define FRAMEWORK_MUSIC_BUFFER_ANDROID_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

class FSoundDataAndroid;
class FSoundInstanceAndroid;
class OSSoundBuffer {

public:
    OSSoundBuffer();
    ~OSSoundBuffer();

    bool                                IsAvailable();

    void                                SetUp();
    void                                TearDown();

    void                                Play(FSoundInstanceAndroid *pSoundInstance, FSoundDataAndroid *pSoundData, float pVolume, float pPitch, bool pLoop);
    void                                Loop();

    void                                Complete();

    void                                Stop();

    SLObjectItf                         bqPlayerObject;
    SLPlayItf                           bqPlayerPlay;
    SLAndroidSimpleBufferQueueItf       bqPlayerBufferQueue;
    SLEffectSendItf                     bqPlayerEffectSend;
    SLPlaybackRateItf                   bqPlayerPlaybackRate;
    SLVolumeItf                         bqPlayerVolume;
    SLpermille                          bqPlaybackRateMin;
    SLpermille                          bqPlaybackRateMax;

    FSoundInstanceAndroid               *mSoundInstance;
    FSoundDataAndroid                   *mSoundData;

    bool                                mDidFail;

    bool                                mIsPlaying;

    bool                                mIsLooping;
    float                               mVolume;
    float                               mPitch;

};



#endif


