//
//  os_core_sound.cpp
//  Graveyard
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "os_core_music.h"
#include "os_core_outlets.h"
#import "OSMusicPlayer.h"
#include "os_core_outlets.h"
#include "core_includes.h"

OSMusicPlayer *gMusicPlayer;

void music_initialize() {
    gMusicPlayer = [[OSMusicPlayer alloc] init];
}

void music_play(const char *pFilePath, bool pLoop) {
    bool aDidFind = false;
    const char *aResourcePath = gRes.GetResourcePathMusic(pFilePath);
    while ((aResourcePath != 0) && (aDidFind == false)) {
        if (os_fileExists(aResourcePath)) { aDidFind = true; }
        else { aResourcePath = gRes.GetNextResourcePath(); }
    }
    if (aDidFind == true) {
        [gMusicPlayer musicPlay: [NSString stringWithUTF8String:aResourcePath] withLoop:pLoop];
    }
}

void music_crossfade(const char *pFilePath, int pDurationTicks, bool pLoop) {
    bool aDidFind = false;
    const char *aResourcePath = gRes.GetResourcePathMusic(pFilePath);
    while ((aResourcePath != 0) && (aDidFind == false)) {
        if (os_fileExists(aResourcePath)) { aDidFind = true; }
        else { aResourcePath = gRes.GetNextResourcePath(); }
    }
    if (aDidFind == true) {
        [gMusicPlayer musicCrossFadeWithPath:[NSString stringWithUTF8String:aResourcePath] withDurationTicks:pDurationTicks withLoop:pLoop];
    }
}

void music_fadeout(int pDurationTicks) {
    [gMusicPlayer musicFadeOutWithDurationTicks: pDurationTicks];
}

void music_stop() {
    [gMusicPlayer musicStop];
}

bool music_isPlaying() {
    bool aResult = false;
    aResult = [gMusicPlayer musicIsPlaying];
    return aResult;
}

void music_setVolume(float pVolume) {
    gMusicVolume = pVolume;
}

float music_getVolume() {
    return gMusicVolume;
}

void music_resume() {
    [gMusicPlayer musicResume];
}

void music_pause() {
    [gMusicPlayer musicPause];
}

void music_update() {
    [gMusicPlayer updateFade];
    if ([gMusicPlayer musicGetVolume] != gMusicVolume) {
        [gMusicPlayer musicSetVolume: gMusicVolume];
    }
}

void music_active() {
    
}

void music_inactive() {
    
}
