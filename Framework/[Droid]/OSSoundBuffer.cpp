//
//  OSSoundBuffer.cpp
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


OSSoundBuffer::OSSoundBuffer() {
    mIsPlaying = false;
    mIsLooping = false;
    mDidFail = false;
    bqPlayerObject = nullptr;
    bqPlayerPlay = nullptr;
    bqPlayerBufferQueue = nullptr;
    bqPlayerEffectSend = nullptr;
    bqPlayerPlaybackRate = nullptr;
    bqPlayerVolume = nullptr;
    bqPlaybackRateMin = 1000;
    bqPlaybackRateMax = 1000;
    mSoundInstance = NULL;
    mSoundData = NULL;
    mVolume = 1.0f;
    mPitch = 1.0f;
}

OSSoundBuffer::~OSSoundBuffer() {
    TearDown();
}

void BufferCompleteCallback(SLAndroidSimpleBufferQueueItf pBufferQueue, void *pContext) {
    gSoundBufferPool.BufferComplete(pBufferQueue);
}

void OSSoundBuffer::SetUp() {
    mDidFail = false;
    mIsPlaying = false;
    mIsLooping = false;
    bqPlayerObject = nullptr;
    bqPlayerPlay = nullptr;
    bqPlayerBufferQueue = nullptr;
    bqPlayerEffectSend = nullptr;
    bqPlayerPlaybackRate = nullptr;
    bqPlayerVolume = nullptr;
    bqPlaybackRateMin = 1000;
    bqPlaybackRateMax = 1000;
    mSoundInstance = NULL;
    mSoundData = NULL;
    mVolume = 1.0f;

    Log("CREATE AUDI BUFFER SampleRate[%d]  BufferSize[%d]\n", gAudioSampleRate, gAudioBufferSize);

    if (engineEngine == NULL) {
        Log("OSSoundBuffer::SetUp() - MISSING ENGINE!!!\n\n");
        mDidFail = true;
        return;
    }

    SLresult aResult;

    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
    //SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM,              //formatType
    //                               2,                              //numChannels
    //                               SL_SAMPLINGRATE_44_1,           //samplesPerSec
    //                               SL_PCMSAMPLEFORMAT_FIXED_16,    //bitsPerSample
    //                               SL_PCMSAMPLEFORMAT_FIXED_16,    //containerSize
    //                               SL_SPEAKER_FRONT_LEFT |
    //                               SL_SPEAKER_FRONT_RIGHT,         //channelMask
    //                               SL_BYTEORDER_LITTLEENDIAN};     //endianness

//#define SL_PCMSAMPLEFORMAT_FIXED_8	((SLuint16) 0x0008)
//#define SL_PCMSAMPLEFORMAT_FIXED_16	((SLuint16) 0x0010)
//#define SL_PCMSAMPLEFORMAT_FIXED_20 	((SLuint16) 0x0014)
//#define SL_PCMSAMPLEFORMAT_FIXED_24	((SLuint16) 0x0018)
//#define SL_PCMSAMPLEFORMAT_FIXED_28 	((SLuint16) 0x001C)
//#define SL_PCMSAMPLEFORMAT_FIXED_32	((SLuint16) 0x0020)

    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM,              //formatType
                                   2,                              //numChannels
                                   SL_SAMPLINGRATE_44_1,             //samplesPerSec
                                   SL_PCMSAMPLEFORMAT_FIXED_16,    //bitsPerSample
                                   SL_PCMSAMPLEFORMAT_FIXED_16,    //containerSize
                                   SL_SPEAKER_FRONT_LEFT |
                                   SL_SPEAKER_FRONT_RIGHT,         //channelMask
                                   SL_BYTEORDER_LITTLEENDIAN};     //endianness

    //SL_PCMSAMPLEFORMAT_FIXED_16

    SLDataSource audioSrc = {&loc_bufq, &format_pcm};

    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    const SLInterfaceID aIDExtended[4] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND, SL_IID_VOLUME, SL_IID_PLAYBACKRATE};
    const SLboolean aReqExtended[4] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_FALSE};

    aResult = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk, 4, aIDExtended, aReqExtended);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To CreateAudioPlayer engineEngine\n");
        mDidFail = true;
        TearDown();
        return;
    }

    aResult = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Realize bqPlayerObject\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface (SL_IID_PLAY)\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE, &bqPlayerBufferQueue);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface (SL_IID_BUFFERQUEUE)\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAYBACKRATE, &bqPlayerPlaybackRate);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface (SL_IID_PLAYBACKRATE)\n");
    }

    if (bqPlayerPlaybackRate) {
        SLuint32 aCapa;
        SLpermille aStepSize;
        aResult = (*bqPlayerPlaybackRate)->GetRateRange(bqPlayerPlaybackRate, 0, &bqPlaybackRateMin, &bqPlaybackRateMax, &aStepSize, &aCapa);
        if (aResult != SL_RESULT_SUCCESS) {
            Log("CoreSound::Failed To GetRateRange (%d - %d)\n",
                (int)bqPlaybackRateMin,
                (int)bqPlaybackRateMax);
            bqPlaybackRateMin = 1000;
            bqPlaybackRateMax = 1000;
        } else {
            Log("CoreSound::Succeeded To GetRateRange (%d - %d)\n",
                (int)bqPlaybackRateMin,
                (int)bqPlaybackRateMax);
        }
    }

    aResult = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, BufferCompleteCallback, NULL);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To RegisterCallback\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND, &bqPlayerEffectSend);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface(SL_IID_EFFECTSEND)\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To Get Interface(SL_IID_VOLUME)\n");
        mDidFail = true;
        return;
    }

    aResult = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("CoreSound::Failed To SetPlayState(SL_PLAYSTATE_PLAYING)\n");
        mDidFail = true;
        return;
    }
}

void OSSoundBuffer::TearDown() {
    if (bqPlayerObject != NULL) {
        (*bqPlayerObject)->Destroy(bqPlayerObject);
        bqPlayerObject = nullptr;
        bqPlayerPlay = nullptr;
        bqPlayerBufferQueue = nullptr;
        bqPlayerEffectSend = nullptr;
        bqPlayerPlaybackRate = nullptr;
        bqPlayerVolume = nullptr;
    }
}

void OSSoundBuffer::Play(FSoundInstanceAndroid *pSoundInstance,
            FSoundDataAndroid *pSoundData, float pVolume, float pPitch, bool pLoop) {

    mPitch = pPitch;
    mVolume = pVolume;

    pVolume *= gSoundVolume;

    if (pSoundInstance == NULL || pSoundData == NULL || bqPlayerPlay == NULL) {
        mSoundInstance = NULL;
        mSoundData = NULL;
        mIsPlaying = false;
        mIsLooping = false;
    }

    if (pSoundData->mData == NULL || pSoundData->mDataLength <= 0) {
        mSoundInstance = NULL;
        mSoundData = NULL;
        mIsPlaying = false;
        mIsLooping = false;
    }

    pSoundInstance->mSoundBuffer = this;

    mSoundInstance = pSoundInstance;
    mSoundData = pSoundData;

    SLresult aResult;

    if (bqPlayerVolume!= NULL) {
        SLmillibel aMillibel = GetMillibels(pVolume);
        SLboolean aMute = 0;
        if (aMillibel <= GetMinMillibels()) {
            aMute = 1;
        }

        aResult = (*(bqPlayerVolume))->SetMute((bqPlayerVolume), aMute);
        if (aResult != SL_RESULT_SUCCESS) {
            Log("SBB - SetMute FAILED =  [%d]\n", (int)aMillibel);
        }

        aResult = (*(bqPlayerVolume))->SetVolumeLevel((bqPlayerVolume), aMillibel );
        if (aResult != SL_RESULT_SUCCESS) {
            Log("SBB - SetVolumeLevel FAILED =  [%d]\n", (int)aMillibel);
        }
    }

    if (bqPlayerPlaybackRate != NULL) {
        SLpermille aRate = SLpermille(1000.0f * pPitch);

        Log("Rate [PRE] = %d\n", (int)aRate);

        if (aRate < bqPlaybackRateMin) { aRate = bqPlaybackRateMin; }
        if (aRate > bqPlaybackRateMax) { aRate = bqPlaybackRateMax; }

        //Tell me why, using the real max rate of 2K
        //makes a wicked hiss noise on old device?
        if (bqPlaybackRateMax <= 2000) {
            if (aRate > 1990) { aRate = 1990; }
        }

        Log("Rate [FIN] = %d\n", (int)aRate);

        aResult = (*(bqPlayerPlaybackRate))->SetRate((bqPlayerPlaybackRate), aRate);

        int aPitchInt = aRate;
        if (aResult != SL_RESULT_SUCCESS) {
            Log("SBB - SetRate FAILED = [%d] (%f)  [%d to %d]\n", aPitchInt, pPitch, bqPlaybackRateMin, bqPlaybackRateMax);
        } else {
            Log("SBB - SetRate SUCCEEDED = [%d] (%f)  [%d to %d]\n", aPitchInt, pPitch, bqPlaybackRateMin, bqPlaybackRateMax);
        }
    }


    aResult = (*bqPlayerBufferQueue)->Clear(bqPlayerBufferQueue);
    if (SL_RESULT_SUCCESS != aResult) {
        Log("SBB - Clear Failed LOL! X_X\n\n\n");
        gSoundBufferPool.BufferComplete(bqPlayerBufferQueue);
        return;
    }

    aResult = (*bqPlayerBufferQueue)->Enqueue(bqPlayerBufferQueue, pSoundData->mData, pSoundData->mDataLength);
    if (aResult != SL_RESULT_SUCCESS) {
        Log("SBB - Enqueue Failed LOL! X_X\n\n\n");
        gSoundBufferPool.BufferComplete(bqPlayerBufferQueue);
        return;
    }

    mIsPlaying = true;
    mIsLooping = pLoop;
}

void OSSoundBuffer::Loop() {
    Play(mSoundInstance, mSoundData, mVolume, mPitch, true);
}

void OSSoundBuffer::Complete() {
    mIsPlaying = false;
    mIsLooping = false;
    if (mSoundInstance) {
        mSoundInstance->mSoundBuffer = NULL;
    }
}

void OSSoundBuffer::Stop() {
    Complete();
    if (bqPlayerBufferQueue) {
        SLresult aResult;
        aResult = (*bqPlayerBufferQueue)->Clear(bqPlayerBufferQueue);
        if (SL_RESULT_SUCCESS != aResult) {
            Log("SBB - Failed \"Clear\"()\n");
            return;
        }
    }
}

bool OSSoundBuffer::IsAvailable() {
    if (mDidFail == false && mIsPlaying == false ) {
        return true;
    }
    return false;
}
