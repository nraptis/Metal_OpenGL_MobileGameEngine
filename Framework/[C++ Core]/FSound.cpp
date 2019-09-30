/*
 *  FSound.cpp
 *  Drillheads
 *
 *  Created by Nick Raptis on 11/29/09.
 *  Copyright 2009 Raptisoft LLC. All rights reserved.
 *
 */

#include "FSound.hpp"
#include "FResource.hpp"
#include "core_includes.h"
#include "os_core_sound.h"

FSoundInstance::FSoundInstance() {
    mIsPaused = false;
	mIsLooping = false;
    mVolume = 1.0f;
    mPitch = 1.0f;
    mDidLoad = false;
}

FSoundInstance::~FSoundInstance() {
    
}

FSoundData::FSoundData() {
    mDidLoad = false;
    mSound = 0;
}

FSoundData::~FSoundData() {
    
}

void FSoundInstance::Play(float pVolume) {
    if (gSoundEnabled) {
        sound_instance_play(this, pVolume);
    }
}

void FSoundInstance::Loop(float pVolume) {
    if (gSoundEnabled) {
        sound_instance_loop(this, pVolume);
    }
}

void FSoundInstance::ResetPitch() {
    sound_instance_resetPitch(this);
}

void FSoundInstance::SetPitch(float pPitch) {
    sound_instance_setPitch(this, pPitch);
}

void FSoundInstance::SetVolume(float pVolume) {
    sound_instance_setVolume(this, pVolume);
}

void FSoundInstance::Pause() {
    sound_instance_pause(this);
}

void FSoundInstance::Unpause() {
    if (gSoundEnabled) {
        sound_instance_unpause(this);
    }
}

void FSoundInstance::Stop() {
    sound_instance_stop(this);
}

bool FSoundInstance::IsPlaying() {
    return sound_instance_isPlaying(this);
}

void FSoundInstance::Destroy() {
    sound_instance_destroy(this);
}

FSound::FSound() {
	mSoundData = sound_spawn_data();
    if (mSoundData) {
        mSoundData->mSound = this;
    }
    mDidLoad = false;
}

FSound::~FSound(void) {
	Clear();
    
}

void FSound::Clear() {
    sound_clear(this);
}

bool FSound::IsPlaying() {
    return sound_isPlaying(this);
}

void FSound::Play(float pVolume) {
    if (gSoundEnabled) {
        sound_play(this, pVolume);
    }
}

void FSound::PlayPitched(float pPitch, float pVolume) {
    if (gSoundEnabled) {
        sound_playPitched(this, pPitch, pVolume);
    }
}

void FSound::Loop(float pVolume) {
    if (gSoundEnabled) {
        sound_loop(this, pVolume);
    }
}

void FSound::LoopPitched(float pPitch, float pVolume) {
    if (gSoundEnabled) {
        sound_loopPitched(this, pPitch, pVolume);
    }
}

void FSound::Stop() {
    sound_stop(this);
}

void FSound::Load(const char *pFileName, int pDuplicates) {
    bool aDidLoad = false;
    
    const char *aResourcePath = gRes.GetResourcePathSound(pFileName);
    while ((aResourcePath != NULL) && (aDidLoad == false)) {
        aDidLoad = sound_load(this, aResourcePath, pDuplicates);
        if (aDidLoad) {
            mFileName = pFileName;
            mDidLoad = true;
        } else {
            aResourcePath = gRes.GetNextResourcePath();
        }
    }
    
    FString aFileNameBase = FString(pFileName);
    aFileNameBase.RemoveExtension();
    
    mFileName = aFileNameBase;
    
    FString aFileName;
    
    int aExtensionCount = 8;
    FString aExtension[8];
    aExtension[0] = ".aif";
    aExtension[1] = ".aiff";
    aExtension[2] = ".caf";
    aExtension[3] = ".m4a";
    aExtension[4] = ".ogg";
    aExtension[5] = ".wav";
    aExtension[6] = ".mp3";
    aExtension[7] = ".aac";
    
    if (aDidLoad == false) {
        for (int i=0;i<aExtensionCount;i++) {
            if (aDidLoad == false) {
                aFileName = FString(aFileNameBase) + aExtension[i];
                aDidLoad = sound_load(this, aFileName.c(), pDuplicates);
                if (aDidLoad) {
                    mFileName = aFileName;
                }
            }
        }
    }
    
    if ((aDidLoad == false) && (gDirBundle.mLength > 0)) {
        for (int i=0;i<aExtensionCount;i++) {
            if (aDidLoad == false) {
                aFileName = gDirBundle + FString(aFileNameBase) + aExtension[i];
                aDidLoad = sound_load(this, aFileName.c(), pDuplicates);
                if (aDidLoad) {
                    mFileName = aFileName;
                }
            }
        }
    }
    
    if (aDidLoad) {
        sSoundList.Add(this);
        EnumList(FSoundInstance, aInstance, mInstances) {
            aInstance->mSound = this;
            sSoundInstanceList.Add(aInstance);
        }
        mDidLoad = true;
    } else {
        mDidLoad = false;
    }
}

bool FSound::DidLoad() {
    return sound_didLoad(this);
}



