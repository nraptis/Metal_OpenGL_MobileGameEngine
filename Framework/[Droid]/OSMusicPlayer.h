//
//  OSSoundBuffer.h
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#ifndef FRAMEWORK_MUSIC_PLAYER_ANDROID_H
#define FRAMEWORK_MUSIC_PLAYER_ANDROID_H

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "OSMusicBuffer.h"


class OSMusicPlayer {

public:
    OSMusicPlayer();
    ~OSMusicPlayer();


    void                                Play(const char *pFilePath, bool pLoop);
    void                                Crossfade(const char *pFilePath, int pDurationTicks, bool pLoop);
    void                                Fadeout(int pDurationTicks);
    void                                Stop();

    bool                                IsPlaying();

    void                                Resume();
    void                                Pause();

    void                                Update();
    void                                Active();
    void                                Inactive();

    OSMusicBuffer                       *mPlayingBuffer;
    int                                 mPlayingFadeinTick;
    int                                 mPlayingFadeinTime;

    OSMusicBuffer                       *mFadingBuffer;
    int                                 mFadingFadeoutTick;
    int                                 mFadingFadeoutTime;

    //If it's different from gMusicVolume, update...
    float                               mVolume;
    bool                                mPaused;


};

extern OSMusicPlayer gMusicPlayer;

#endif


