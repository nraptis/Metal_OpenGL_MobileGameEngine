//
//  os_core_sound.cpp
//  Ghibli
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Union AdWorks LLC. All rights reserved.
//

#include <assert.h>
#include <jni.h>
#include "os_core_sound.h"
#include "os_core_includes.h"
#include "core_includes.h"
#include "FSound.hpp"
#include "FFile.hpp"

#include "OSSoundBuffer.h"
#include "OSSoundBufferPool.h"

#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>


FSoundInstanceAndroid::FSoundInstanceAndroid() {
    mSoundBuffer = NULL;
}

FSoundInstanceAndroid::~FSoundInstanceAndroid() {
    
}

FSoundDataAndroid::FSoundDataAndroid() {
    mData = NULL;
    mDataLength = 0;
}

FSoundDataAndroid::~FSoundDataAndroid() {
    
}

int gAudioSampleRate = 0;
int gAudioBufferSize = 0;

SLObjectItf engineObject = NULL;
SLEngineItf engineEngine = NULL;
SLObjectItf outputMixObject = NULL;
SLEnvironmentalReverbItf outputMixEnvironmentalReverb = NULL;

// aux effect on the output mix, used by the buffer queue player
//static const SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;
static const SLEnvironmentalReverbSettings reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_DEFAULT;

void sound_initialize() {
    SLresult aResult;
    
    // create engine
    aResult = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
    if (SL_RESULT_SUCCESS != aResult) {
        if (engineObject != NULL) {
            (*engineObject)->Destroy(engineObject);
            engineObject = NULL;
        }
        return;
    }
    
    // realize the engine
    aResult = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    if (SL_RESULT_SUCCESS != aResult) {
        if (engineObject != NULL) {
            (*engineObject)->Destroy(engineObject);
            engineObject = NULL;
        }
        return;
    }
    
    // get the engine interface, which is needed in order to create other objects
    aResult = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    if (SL_RESULT_SUCCESS != aResult) {
        if (engineObject != NULL) {
            (*engineObject)->Destroy(engineObject);
            engineObject = NULL;
        }
        return;
    }
    
    // create output mix, with environmental reverb specified as a non-required interface
    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req[1] = {SL_BOOLEAN_FALSE};
    aResult = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
    if (SL_RESULT_SUCCESS != aResult) {
        if (engineObject != NULL) {
            (*engineObject)->Destroy(engineObject);
            engineObject = NULL;
        }
        return;
    }
    
    // realize the output mix
    aResult = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    if (SL_RESULT_SUCCESS != aResult) {
        if (engineObject != NULL) {
            (*engineObject)->Destroy(engineObject);
            engineObject = NULL;
        }
        return;
    }
    
    // get the environmental reverb interface
    // this could fail if the environmental reverb effect is not available,
    // either because the feature is not present, excessive CPU load, or
    // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
    aResult = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB,
                                              &outputMixEnvironmentalReverb);
    if (SL_RESULT_SUCCESS == aResult) {
        aResult = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(outputMixEnvironmentalReverb, &reverbSettings);
        (void)aResult;
    }
    // ignore unsuccessful aResult codes for environmental reverb, as it is optional for this example

}

bool sound_load(FSound *pSound, const char *pFileName, int pInstanceCount) {
    if (pInstanceCount <= 0) pInstanceCount = 1;
    if (pInstanceCount > 10) pInstanceCount = 10;
    int aLoadedInstanceCount = 0;
    if (pSound != 0) {
        FSoundDataAndroid *aSoundData = (FSoundDataAndroid *)pSound->mSoundData;
        if (aSoundData) {
            FFile aFile;
            aFile.Load(pFileName);

            //There are 44 byte and 46 byte wav files. We always include a "ramp up"
            //on our sound effects, but the eventual plan is to decompress sound files.
            int aHeaderSize = 46 * 2;
            if (aFile.mLength > (aHeaderSize + 2)) {
                aSoundData->mData = new unsigned char[aFile.mLength - aHeaderSize];
                //memset(aSoundData->mData, 0, aFile.mLength * 2);
                memcpy(aSoundData->mData, &(aFile.mData[aHeaderSize]), aFile.mLength - aHeaderSize);

                aSoundData->mDataLength = aFile.mLength - aHeaderSize;
                pSound->mDidLoad = true;

                //Log("SOUND [%s] LENGTH = [%d] INST[%d]\n", pFileName, aSoundData->mDataLength, pInstanceCount);

                for (int i=0;i<pInstanceCount;i++) {
                    FSoundInstanceAndroid *aInstance = new FSoundInstanceAndroid();
                    aInstance->mDidLoad = true;
                    aInstance->mSound = pSound;
                    pSound->mInstances += aInstance;

                }
                return true;
            }
        }
    }
    return false;
}

void sound_play(FSound *pSound) {
    sound_playPitched(pSound, 1.0f, 1.0f);
}

void sound_play(FSound *pSound, float pVolume) {
    sound_playPitched(pSound, pVolume, 1.0f);
}

void sound_playPitched(FSound *pSound, float pPitch, float pVolume) {
    if (pSound != NULL) {
        FSoundDataAndroid *aSoundData = (FSoundDataAndroid *)(pSound->mSoundData);
        if ((pSound->mDidLoad == true) && (aSoundData != 0)) {
            FSoundInstanceAndroid *aInstanceCheck = (FSoundInstanceAndroid *)(pSound->mInstances.Fetch(0));
            if (aInstanceCheck) {
                FSoundInstanceAndroid *aInstancePlay = 0;
                if (sound_instance_isPlaying((FSoundInstanceAndroid *)aInstanceCheck) == false) {
                    aInstancePlay = aInstanceCheck;
                    pSound->mInstances.RotateFrontToBack();
                } else {
                    EnumList (FSoundInstanceAndroid, aInstance, pSound->mInstances) {
                        if (sound_instance_isPlaying((FSoundInstanceAndroid *)aInstance) == false) {
                            aInstancePlay = aInstance;
                        }
                    }
                }
                if (aInstancePlay != NULL) {
                    OSSoundBuffer *aSoundBuffer = gSoundBufferPool.DequeueBuffer();
                    if (aSoundBuffer != NULL) {
                        aSoundBuffer->Play(aInstancePlay, aSoundData, pVolume, pPitch, false);
                    } else {
                        Log("OSSoundBuffer => IS NULL!!\n\n");
                    }
                }
            }
        }
    }
}

void sound_loop(FSound *pSound, float pVolume) {
    sound_loopPitched(pSound, pVolume, 1.0f);
}

void sound_loopPitched(FSound *pSound, float pPitch, float pVolume) {
    if (pSound != NULL) {
        FSoundDataAndroid *aSoundData = (FSoundDataAndroid *)(pSound->mSoundData);
        if ((pSound->mDidLoad == true) && (aSoundData != 0)) {
            FSoundInstanceAndroid *aInstanceCheck = (FSoundInstanceAndroid *)(pSound->mInstances.Fetch(0));
            if (aInstanceCheck) {
                FSoundInstanceAndroid *aInstancePlay = 0;
                if (sound_instance_isPlaying((FSoundInstanceAndroid *)aInstanceCheck) == false) {
                    aInstancePlay = aInstanceCheck;
                    pSound->mInstances.RotateFrontToBack();
                } else {
                    EnumList (FSoundInstanceAndroid, aInstance, pSound->mInstances) {
                        if (sound_instance_isPlaying((FSoundInstanceAndroid *)aInstance) == false) {
                            aInstancePlay = aInstance;
                        }
                    }
                }
                if (aInstancePlay != NULL) {
                    OSSoundBuffer *aSoundBuffer = gSoundBufferPool.DequeueBuffer();
                    if (aSoundBuffer != NULL) {
                        aSoundBuffer->Play(aInstancePlay, aSoundData, pVolume, pPitch, true);
                    } else {
                        Log("OSSoundBuffer => IS NULL!!\n\n");
                    }
                }
            }
        }
    }
}

void sound_stop(FSound *pSound) {
    if (pSound) {
        EnumList(FSoundInstance, aInstance, pSound->mInstances) {
            sound_instance_stop(aInstance);
        }
    }
}

void sound_clear(FSound *pSound) {

}

bool sound_isPlaying(FSound *pSound) {
    bool aReturn = false;
    if (pSound) {
        EnumList(FSoundInstance, aInstance, pSound->mInstances) {
            if (sound_instance_isPlaying(aInstance)) {
                aReturn = true;
                break;
            }
        }
    }
    return aReturn;
}

bool sound_didLoad(FSound *pSound) {
    bool aReturn = false;
    if (pSound) {
        EnumList(FSoundInstance, aInstance, pSound->mInstances) {
            if (aInstance->mDidLoad == true) {
                aReturn = true;
            }
        }
    }
    return aReturn;
}

void sound_setVolume(float pVolume) {
    gSoundVolume = pVolume;
}

float sound_getVolume() {
    return gSoundVolume;
}

void sound_instance_play(FSoundInstance *pInstance, float pVolume) {

}

void sound_instance_resetPitch(FSoundInstance *pInstance) {
    
}

void sound_instance_setPitch(FSoundInstance *pInstance, float pPitch) {
    
}

void sound_instance_setVolume(FSoundInstance *pInstance, float pVolume) {
    
}

void sound_instance_pause(FSoundInstance *pInstance) {
    
}

void sound_instance_unpause(FSoundInstance *pInstance) {
    
}

void sound_instance_loop(FSoundInstance *pInstance, float pVolume) {
    
}

void sound_instance_stop(FSoundInstance *pInstance) {
    Log("sound_instance_stop(%x)\n", pInstance);
    FSoundInstanceAndroid *aInstance = (FSoundInstanceAndroid  *)pInstance;
    if (aInstance != NULL && aInstance->mSoundBuffer != NULL) {
        Log("sound_instance_stop BUFFRR(%x)\n", aInstance->mSoundBuffer);
        aInstance->mSoundBuffer->Stop();
    }
}

bool sound_instance_isPlaying(FSoundInstance *pInstance) {
    bool aReturn = false;
    FSoundInstanceAndroid *aInstance = (FSoundInstanceAndroid  *)pInstance;
    if (aInstance != NULL && aInstance->mSoundBuffer != NULL) {
        if (aInstance->mSoundBuffer->mIsPlaying) {
            return true;
        }
    }
    return aReturn;
}

void sound_instance_destroy(FSoundInstance *pInstance) {
    
}

void sound_stopAll() {
    
}

void sound_stopAllEffects()  {
    
}

FSoundData *sound_spawn_data()  {
    return new FSoundDataAndroid();
}

void sound_unloadEffects()  {
    
}

void sound_reloadEffects()  {
    
}

void sound_update() {
    
}

void sound_active()  {
    music_resume();
}

void sound_inactive()  {
    music_pause();
}

void sound_setAudioAttributes(int pSampleRate, int pBufferSize) {
    gAudioSampleRate = pSampleRate;
    gAudioBufferSize = pBufferSize;

}

SLmillibel GetMinMillibels() {
    return -4000;
}

SLmillibel GetMillibels(float pVolume) {
    SLmillibel aResult = 0;
    if (pVolume <= 0.0f) {
        aResult = GetMinMillibels();
    } else if (pVolume >= 1.0) {
        aResult = 0;
    } else {
        float aInterp = 0.0f;
        aInterp = (float)log2(pVolume + 0.05f);
        float aValueMin = -4.322f;
        float aValueMax = 0.1374;
        aInterp = (aInterp - aValueMin) / (aValueMax - aValueMin);
        float aMin = GetMinMillibels();
        float aMax = 0.0f;
        int aResultInt = (int)(aMin + (aMax - aMin) * aInterp);
        aResult = aResultInt;
    }
    if (aResult < GetMinMillibels()) { aResult = GetMinMillibels(); }
    if (aResult > 0) { aResult = 0; }
    return aResult;
}



