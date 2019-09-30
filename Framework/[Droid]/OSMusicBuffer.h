//
//  OSSoundBuffer.h
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#ifndef FRAMEWORK_SOUND_BUFFER_ANDROID_H
#define FRAMEWORK_SOUND_BUFFER_ANDROID_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#include "FString.hpp"

class OSMusicBuffer {

public:
    OSMusicBuffer();
    ~OSMusicBuffer();

    void                                SetUp(const char *pFilePath, bool pLoop);
    void                                TearDown();

    void                                Pause();
    void                                Resume();


    bool                                IsPlaying();

    //DOES NOT take gMusicVolume into account.
    void                                SetVolume(float pVolume);
    float                               mVolume;

    FString                             mFileName;

    SLObjectItf                         uriPlayerObject;
    SLPlayItf                           uriPlayerPlay;
    SLSeekItf                           uriPlayerSeek;
    SLMuteSoloItf                       uriPlayerMuteSolo;
    SLVolumeItf                         uriPlayerVolume;

    bool                                mDidFail;

};



#endif


