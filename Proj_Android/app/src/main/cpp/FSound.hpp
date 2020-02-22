//
//  FFSound.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/17/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef __CoreDemo__FFSound__
#define __CoreDemo__FFSound__

#include "FList.hpp"
#include "FString.hpp"

class FSound;

class FSoundInstance {
public:
    
    FSoundInstance();
    virtual ~FSoundInstance();
	//FSoundInstance(unsigned int pIndex);
	
    void                            Play(float pVolume);
    void                            Loop(float pVolume);
    
    void                            ResetPitch();
    
    void                            SetPitch(float pPitch);
    void                            SetVolume(float pVolume);
    
    void                            Pause();
    void                            Unpause();
    
    void                            Stop();
    
    bool                            IsPlaying();
    
    void                            Destroy();
    
	bool                            mIsPaused;
	bool                            mIsLooping;
    
    float                           mVolume;
    float                           mPitch;
    
    bool                            mDidLoad;
    
    FSound                          *mSound;
    
    //unsigned int                    mIndexOpenAL;
	
    //SLObjectItf                     mPlayerObject;
    //SLPlayItf                       mPlayerPlay;
    //SLMuteSoloItf                   mPlayerMuteSolo;
    //SLVolumeItf                     mPlayerVolume;
    //SLPitchItf                      mPlayerPitch;
};

//OS Specific
class FSoundData {
public:
    FSoundData();
    virtual ~FSoundData();
    
    bool                            mDidLoad;
    FSound                          *mSound;
};

class FSound {
public:
	FSound();
	virtual ~FSound();
    
	void                            Load(const char *pFileName, int pDuplicates = 1);
    
    bool                            IsPlaying();
    
    void                            Play(float pVolume = 1.0f);
    void                            PlayPitched(float pPitch, float pVolume = 1.0f);
    
    void                            Loop(float pVolume = 1.0f);
    void                            LoopPitched(float pPitch, float pVolume = 1.0f);
    
	void                            Stop();
	void                            Clear();
	
    
    bool                            DidLoad();
    bool                            mDidLoad;
    
    FSoundData                      *mSoundData;
    
    
	//unsigned int                    *mSoundData;
	//unsigned int                    *mInstanceID;
	//float                           *mSourceBuffer;
    
    
	FList                           mInstances;

    FString                         mFileName;
};

#endif
