//
//  OSSoundBuffer.cpp
//  Space Whore
//
//  Created by Nick Raptis on 03/27/2019.
//  Copyright (c) 2019
//

#include "OSMusicPlayer.h"
#include "os_core_sound.h"
#include "os_core_includes.h"
#include "core_includes.h"
#include "FApp.hpp"

OSMusicPlayer gMusicPlayer;

OSMusicPlayer::OSMusicPlayer() {
    mPlayingBuffer = NULL;
    mPlayingFadeinTick = 0;
    mPlayingFadeinTime = 0;

    mFadingBuffer = NULL;
    mFadingFadeoutTick = 0;
    mFadingFadeoutTime = 0;

    mVolume = gMusicVolume;
    mPaused = false;
}

OSMusicPlayer::~OSMusicPlayer() {

}

void OSMusicPlayer::Play(const char *pFilePath, bool pLoop) {
    if (mPlayingBuffer != NULL) {
        delete mPlayingBuffer;
        mPlayingBuffer = NULL;
    }

    mPaused = false;

    mPlayingFadeinTick = 0;
    mPlayingFadeinTime = 0;

    mPlayingBuffer = new OSMusicBuffer();
    mPlayingBuffer->SetUp(pFilePath, pLoop);
    if (mPlayingBuffer->mDidFail) {
        delete mPlayingBuffer;
        mPlayingBuffer = NULL;
    }
}

void OSMusicPlayer::Crossfade(const char *pFilePath, int pDurationTicks, bool pLoop) {
    Fadeout(pDurationTicks);

    Play(pFilePath, pLoop);

    if (mPlayingBuffer != NULL) {
        mPlayingBuffer->SetVolume(0.0f);
        mPlayingFadeinTick = 0;
        mPlayingFadeinTime = pDurationTicks;
    } else {
        mPlayingFadeinTick = 0;
        mPlayingFadeinTime = 0;
    }
}

void OSMusicPlayer::Fadeout(int pDurationTicks) {
    if (mFadingBuffer != NULL) {
        delete mFadingBuffer;
        mFadingBuffer = NULL;
    }
    if (mPlayingBuffer != NULL) {
        mFadingBuffer = mPlayingBuffer;
        mPlayingBuffer = NULL;
        mFadingFadeoutTick = 0;
        mFadingFadeoutTime = pDurationTicks;
    } else {
        mFadingFadeoutTick = 0;
        mFadingFadeoutTime = 0;
    }
}

void OSMusicPlayer::Stop() {
    if (mPlayingBuffer != NULL) {
        delete mPlayingBuffer;
        mPlayingBuffer = NULL;
    }
    if (mFadingBuffer != NULL) {
        delete mFadingBuffer;
        mFadingBuffer = NULL;
    }
}

bool OSMusicPlayer::IsPlaying() {
    if (mPlayingBuffer != NULL) {
        mPlayingBuffer->IsPlaying();
    }
}

void OSMusicPlayer::Resume() {
    mPaused = false;
    if (mPlayingBuffer != NULL) {
        mPlayingBuffer->Resume();
    }
}

void OSMusicPlayer::Pause() {
    mPaused = true;
    if (mPlayingBuffer != NULL) {
        mPlayingBuffer->Pause();
    }
    if (mFadingBuffer != NULL) {
        delete mFadingBuffer;
        mFadingBuffer = NULL;
    }
}

void OSMusicPlayer::Update() {
    float aVolumeMain = gMusicVolume;
    float aVolumeFading = gMusicVolume;
    if (gAppBase->mActive == true && mPaused == false) {
        if (mPlayingFadeinTime > 0) {
            mPlayingFadeinTick++;
            float aPercentFI = ((float)mPlayingFadeinTick / (float)mPlayingFadeinTime);
            if (aPercentFI < 0.0f) { aPercentFI = 0.0f; }
            if (aPercentFI > 1.0f) { aPercentFI = 1.0f; }
            aVolumeMain *= aPercentFI;

            //Log("Percent Main: %f\n", aPercentFI);

            if (mPlayingFadeinTick >= mPlayingFadeinTime) {
                mPlayingFadeinTime = 0;
                mPlayingFadeinTick = 0;
            }
        }
        if (mFadingFadeoutTime > 0) {
            mFadingFadeoutTick++;
            float aPercentFO = ((float)mFadingFadeoutTick / (float)mFadingFadeoutTime);
            aPercentFO= (1.0f - aPercentFO);
            if (aPercentFO < 0.0f) { aPercentFO = 0.0f; }
            if (aPercentFO > 1.0f) { aPercentFO = 1.0f; }
            aVolumeFading *= aPercentFO;

            //Log("Percent Fading: %f\n", aPercentFO);

            if (mFadingFadeoutTick >= mFadingFadeoutTime) {
                mFadingFadeoutTime = 0;
                mFadingFadeoutTick = 0;
                if (mFadingBuffer != NULL) {
                    delete mFadingBuffer;
                    mFadingBuffer = NULL;
                }
            }
        }
    } else {
        mFadingFadeoutTick = 0;
        mFadingFadeoutTime = 0;
        mPlayingFadeinTick = 0;
        mPlayingFadeinTime = 0;
        if (mFadingBuffer != NULL) {
            delete mFadingBuffer;
            mFadingBuffer = NULL;
        }
    }

    if (mPlayingBuffer != NULL) {
        mPlayingBuffer->SetVolume(aVolumeMain);
    }

    if (mFadingBuffer != NULL) {
        mFadingBuffer->SetVolume(aVolumeFading);
    }
}

void OSMusicPlayer::Active() {
    if (mPlayingBuffer != NULL && mPaused == false) {
        mPlayingBuffer->Resume();
    }
}

void OSMusicPlayer::Inactive() {
    if (mFadingBuffer != NULL) {
        delete mFadingBuffer;
        mFadingBuffer = NULL;
    }
    if (mPlayingBuffer != NULL) {
        mPlayingBuffer->Pause();
    }
}


