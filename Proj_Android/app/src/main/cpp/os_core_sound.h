//
//  os_core_sound.h
//  Ghibli
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#ifndef FRAMEWORK_OS_sound_H
#define FRAMEWORK_OS_sound_H

#include "os_core_includes.h"
#include "FSound.hpp"



#define SOUND_VOLUME_MILLIBEL_MIN (-4000)
#define SOUND_VOLUME_MILLIBEL_MAX (0)

class FSoundInstanceAndroid;
class OSSoundBuffer;
class FSoundInstanceAndroid : public FSoundInstance {
public:
    FSoundInstanceAndroid();
    virtual ~FSoundInstanceAndroid();

    OSSoundBuffer                               *mSoundBuffer;
};


class FSoundDataAndroid : public FSoundData {
public:
    FSoundDataAndroid();
    virtual ~FSoundDataAndroid();

    unsigned char                               *mData;
    int                                         mDataLength;
};

void sound_initialize();

bool sound_load(FSound *pSound, const char *pFileName, int pInstanceCount);

void sound_play(FSound *pSound);
void sound_play(FSound *pSound, float pVolume=1.0f);
void sound_playPitched(FSound *pSound, float pPitch, float pVolume=1.0f);
void sound_loop(FSound *pSound, float pVolume = 1.0f);
void sound_loopPitched(FSound *pSound, float pPitch, float pVolume = 1.0f);

void sound_stop(FSound *pSound);
void sound_clear(FSound *pSound);
bool sound_isPlaying(FSound *pSound);
bool sound_didLoad(FSound *pSound);
void sound_setVolume(float pVolume);
float sound_getVolume();


void sound_instance_play(FSoundInstance *pInstance, float pVolume);
void sound_instance_resetPitch(FSoundInstance *pInstance);
void sound_instance_setPitch(FSoundInstance *pInstance, float pPitch);
void sound_instance_setVolume(FSoundInstance *pInstance, float pVolume);
void sound_instance_pause(FSoundInstance *pInstance);
void sound_instance_unpause(FSoundInstance *pInstance);
void sound_instance_loop(FSoundInstance *pInstance, float pVolume);
void sound_instance_stop(FSoundInstance *pInstance);
bool sound_instance_isPlaying(FSoundInstance *pInstance);
void sound_instance_destroy(FSoundInstance *pInstance);

void sound_stopAll();
void sound_stopAllEffects();

void sound_unloadEffects();
void sound_reloadEffects();

void sound_update();
void sound_active();
void sound_inactive();

FSoundData *sound_spawn_data();

SLmillibel GetMinMillibels();
SLmillibel GetMillibels(float pVolume);

void sound_setAudioAttributes(int pSampleRate, int pBufferSize);

// engine interfaces
extern SLObjectItf engineObject;
extern SLEngineItf engineEngine;
extern SLObjectItf outputMixObject;
extern SLEnvironmentalReverbItf outputMixEnvironmentalReverb;

extern int gAudioSampleRate;
extern int gAudioBufferSize;


#endif


