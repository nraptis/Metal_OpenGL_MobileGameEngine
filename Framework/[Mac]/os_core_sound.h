//
//  os_core_sound.h
//  Graveyard
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_OS_sound_H
#define FRAMEWORK_OS_sound_H


#include "FSound.hpp"

class FSoundInstanceMac : public FSoundInstance
{
public:
    FSoundInstanceMac();
    virtual ~FSoundInstanceMac();
    
    unsigned int                    mIndexOpenAL;
};


class FSoundDataMac : public FSoundData
{
public:
    FSoundDataMac();
    virtual ~FSoundDataMac();
    
    unsigned int                    *mData;
	unsigned int                    *mInstanceID;
	float                           *mSourceBuffer;
};

typedef int SLObjectItf;
typedef int SLPlayItf;
typedef int SLSeekItf;
typedef int SLMuteSoloItf;
typedef int SLVolumeItf;
typedef int SLRatePitchItf;
typedef int SLPitchItf;

class FSound;
class FSoundInstance;

//Must be called before all other sound functions. (For OpenAL at least)
void sound_initialize();

bool sound_load(FSound *pSound, const char *pFileName, int pInstanceCount);

void sound_play(FSound *pSound);
void sound_play(FSound *pSound, float pVolume = 1.0f);
void sound_playPitched(FSound *pSound, float pPitch, float pVolume = 1.0f);
void sound_loop(FSound *pSound, float pVolume = 1.0f);
void sound_loopPitched(FSound *pSound, float pPitch, float pVolume = 1.0f);


void sound_stop(FSound *pSound);
void sound_clear(FSound *pSound);
bool sound_isPlaying(FSound *pSound);
bool sound_didLoad(FSound *pSound);

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

void sound_setVolume(float pVolume);
float sound_getVolume();

void sound_stopAll();
void sound_stopAllEffects();

void sound_unloadEffects();
void sound_reloadEffects();

void sound_update();
void sound_active();
void sound_inactive();

FSoundData *sound_spawn_data();


#endif


