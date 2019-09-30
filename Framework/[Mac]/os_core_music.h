//
//  os_core_sound.h
//  Graveyard
//
//  Created by Nick Raptis on 2/21/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_OS_MUSIC_H
#define FRAMEWORK_OS_MUSIC_H

void music_initialize();

void music_play(const char *pFilePath, bool pLoop);
void music_crossfade(const char *pFilePath, int pDurationTicks, bool pLoop);
void music_fadeout(int pDurationTicks);
void music_stop();

void music_setVolume(float pVolume);
float music_getVolume();

bool music_isPlaying();

void music_resume();
void music_pause();

void music_update();
void music_active();
void music_inactive();

#endif


