//
//  OSMusicPlayer.m
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/6/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#import "OSMusicPlayer.h"

@implementation OSMusicPlayer


@synthesize musicPlayer;
@synthesize musicPlayerFading;

- (id)init {
    musicFadeOutTick = 0;
    musicFadeOutTickMax = 5;
    musicFadeOut = false;
    
    musicFadeInTick = 0;
    musicFadeInTickMax = 5;
    musicFadeIn = false;
    
    musicVolume = 1.0f;
    
    musicLoop = false;
    musicFadeLoop = false;
    
    
    self = [super init];
    
    
    
    return self;
}

- (void)updateFade
{
    if(musicFadeIn)
    {
        musicFadeInTick--;
        
        if(musicFadeInTick <= 0)
        {
            [musicPlayer setVolume:(musicVolume)];
            musicFadeIn = NO;
        }
        else
        {
            if(musicFadeInTickMax <= 0)musicFadeInTickMax = 1;
            
            float aPercent = ((float)musicFadeInTick) / ((float)musicFadeInTickMax);
            
            if(aPercent < 0.0f)aPercent = 0.0f;
            if(aPercent > 1.0f)aPercent = 1.0f;
            aPercent = 1.0f - aPercent;
            
            [musicPlayer setVolume:(aPercent * musicVolume)];
            
        }
    }
    
    if (musicFadeOut) {
        musicFadeOutTick--;
        if (musicFadeOutTick <= 0) {
            [musicPlayerFading stop];
            musicPlayerFading.delegate = nil;
            self.musicPlayerFading = nil;
            
            musicFadeOut = NO;
        } else {
            if (musicFadeOutTickMax <= 0) musicFadeOutTickMax = 1;
            
            float aPercent = ((float)musicFadeOutTick) / ((float)musicFadeOutTickMax);
            
            if(aPercent < 0.0f)aPercent = 0.0f;
            if(aPercent > 1.0f)aPercent = 1.0f;
            
            [musicPlayerFading setVolume:(aPercent * musicVolume)];
            
        }
    }
}

- (void)musicPlay:(NSString *)pFilePath withLoop:(BOOL)pLoop {
    [self musicPlay:pFilePath withVolume:1.0f withLoop:pLoop];
}

- (void)musicPlay:(NSString *)pFilePath withVolume:(float)pVolume withLoop:(BOOL)pLoop {
    
    musicLoop = NO;
    
    if (musicPlayer) {
        [musicPlayer stop];
        musicPlayer.delegate = nil;
        self.musicPlayer = nil;
    }
    
    bool aFail = true;
    
    NSURL *aURL = [[NSURL alloc] initFileURLWithPath: pFilePath];
    
    if (aURL) {
        NSError *aError;
        
        musicPlayer = [[AVAudioPlayer alloc] initWithContentsOfURL:aURL error:&aError];
        
        if (aError) {
            NSLog(@"Music Error!");
            NSLog(@"[%@]", pFilePath);
            NSLog(@"(%@)", aError);
        } else {
            //NSLog(@"Playing Music Vol [%f  x  %f]", musicVolume, pVolume);
            
            [musicPlayer prepareToPlay];
            [musicPlayer setVolume:(musicVolume * pVolume)];
            [musicPlayer setDelegate:self];
            [musicPlayer play];
            
            musicLoop = pLoop;
            aFail = NO;
        }
    }
    
}

- (void)musicCrossFadeWithPath:(NSString *)pFilePath withDurationTicks:(int)pDurationTicks withLoop:(BOOL)pLoop {
    if(pDurationTicks < 1)pDurationTicks = 1;
    
    [self musicFadeOutWithDurationTicks:pDurationTicks];
    
    if(musicPlayer)
    {
        [musicPlayer stop];
        musicPlayer.delegate = nil;
        self.musicPlayer = nil;
    }
    
    [self musicPlay:pFilePath withVolume:0.0f withLoop:pLoop];
    
    musicFadeInTick = pDurationTicks;
    musicFadeInTickMax = pDurationTicks;
    musicFadeIn = YES;
}

- (void)musicFadeOutWithDurationTicks:(int)pDurationTicks {
    if (pDurationTicks < 1) pDurationTicks = 1;
    
    if (musicPlayerFading) {
        [musicPlayerFading stop];
        musicPlayerFading.delegate = nil;
        self.musicPlayerFading = nil;
    }
    
    if (musicPlayer) {
        self.musicPlayerFading = musicPlayer;
        self.musicPlayer = nil;
        
        musicFadeLoop = musicLoop;
        musicFadeOutTick = pDurationTicks;
        musicFadeOutTickMax = pDurationTicks;
        musicFadeOut = true;
    } else {
        musicFadeLoop = false;
        musicFadeOutTick = 0;
        musicFadeOutTickMax = 0;
        musicFadeOut = false;
    }
}

- (float)musicGetVolume {
    return musicVolume;
}

- (void)musicSetVolume:(float)pVolume {
    if(pVolume < 0.0f)pVolume = 0.0f;
    if(pVolume > 1.0f)pVolume = 1.0f;
    
    musicVolume = pVolume;
    
    [musicPlayer setVolume:(musicVolume)];
}

- (void)musicStop {
    [musicPlayer stop];
}

- (void)musicPause {
    [musicPlayer pause];
}

- (void)musicResume {
    [musicPlayer play];
}

- (BOOL)musicIsPlaying {
    BOOL aResult = NO;
    if (musicPlayer) {
        if ([musicPlayer isPlaying]) {
            return YES;
        }
    }
    return aResult;
}

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag {
    if (player == musicPlayer) {
        if (musicLoop) {
            [musicPlayer play];
        } else {
            [musicPlayer stop];
            musicPlayer.delegate = nil;
            self.musicPlayer = nil;
        }
    } else if(player == musicPlayerFading) {
        if (musicFadeLoop) {
            [musicPlayerFading play];
        } else {
            [musicPlayerFading stop];
            musicPlayerFading.delegate = nil;
            self.musicPlayerFading = nil;
        }
    }
}

- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error {
    
}

- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player {
    
}

- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withFlags:(NSUInteger)flags {
    
}

@end
