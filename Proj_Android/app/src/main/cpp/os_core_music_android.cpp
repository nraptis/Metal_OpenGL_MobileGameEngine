//
//  os_core_sound.cpp
//  Graveyard
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "os_core_music.h"
#include "os_core_outlets.h"
#include "os_core_outlets.h"
#include "core_includes.h"
#include "OSMusicPlayer.h"
#include "OSMusicBuffer.h"

void music_initialize() {

}

void music_play(const char *pFilePath, bool pLoop) {
    gMusicPlayer.Play(pFilePath, pLoop);
}

void music_crossfade(const char *pFilePath, int pDurationTicks, bool pLoop) {


    gMusicPlayer.Crossfade(pFilePath, pDurationTicks, pLoop);
}

void music_fadeout(int pDurationTicks) {
    gMusicPlayer.Fadeout(pDurationTicks);
}

void music_stop() {
    gMusicPlayer.Stop();
}

bool music_isPlaying() {
    return gMusicPlayer.IsPlaying();
}

void music_setVolume(float pVolume) {
    gMusicVolume = pVolume;
}

float music_getVolume() {
    return gMusicVolume;
}

void music_resume() {
    gMusicPlayer.Resume();
}

void music_pause() {
    gMusicPlayer.Pause();
}

void music_update() {
    gMusicPlayer.Update();
}

void music_active() {
    gMusicPlayer.Active();
}

void music_inactive() {
    gMusicPlayer.Inactive();
}

int MUSIC_GetFileDescriptor(const char *pFileName, off_t &pStartIndex, off_t &pLength) {
    int aReturn = -1;
    jmethodID aMethodID = 0;
    if ((gJVM != NULL) && (pFileName != NULL)) {
        bool aDetach = false;
        JNIEnv *aEnv = os_getJNIEnv(&aDetach);
        jclass aClass = os_getClassID(aEnv);
        if ((aEnv != NULL) && (aClass != NULL)) {
            aMethodID = aEnv->GetMethodID(aClass, "getAssetManager", "()Landroid/content/res/AssetManager;");
            if (aMethodID) {
                jobject aAssetManagerObject = aEnv->CallObjectMethod(_objJNIHelper, aMethodID);
                if (aAssetManagerObject != 0) {
                    AAssetManager *aAssetManager = AAssetManager_fromJava(aEnv, aAssetManagerObject);
                    if (aAssetManager != 0) {
                        //AAsset *aAsset = AAssetManager_open(aAssetManager, pFileName, AASSET_MODE_UNKNOWN);
                        AAsset *aAsset = AAssetManager_open(aAssetManager, pFileName, AASSET_MODE_BUFFER);
                        if (aAsset != 0) {
                            int aFileDescriptor = AAsset_openFileDescriptor(aAsset, &pStartIndex, &pLength);
                            AAsset_close(aAsset);
                            if (aFileDescriptor != -1) {
                                aReturn = aFileDescriptor;
                            } else {
                                pLength = 0;
                                pStartIndex = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return aReturn;
}