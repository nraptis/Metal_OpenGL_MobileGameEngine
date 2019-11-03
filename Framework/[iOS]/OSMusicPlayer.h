//
//  OSMusicPlayer.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/6/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

@interface OSMusicPlayer : NSObject <AVAudioPlayerDelegate>
{
    AVAudioPlayer                           *musicPlayer;
    AVAudioPlayer                           *musicPlayerFading;
    
    int                                     musicFadeOutTick;
    int                                     musicFadeOutTickMax;
    bool                                    musicFadeOut;
    
    int                                     musicFadeInTick;
    int                                     musicFadeInTickMax;
    bool                                    musicFadeIn;
    
    
    float                                   musicVolume;
    
    bool                                    musicLoop;
    bool                                    musicFadeLoop;
}

@property (nonatomic, strong) AVAudioPlayer *musicPlayer;
@property (nonatomic, strong) AVAudioPlayer *musicPlayerFading;

- (id)init;

- (void)updateFade;

- (void)musicPlay:(NSString *)pFilePath withLoop:(BOOL)pLoop;
- (void)musicPlay:(NSString *)pFilePath withVolume:(float)pVolume withLoop:(BOOL)pLoop;

- (void)musicCrossFadeWithPath:(NSString *)pFilePath withDurationTicks:(int)pDurationTicks withLoop:(BOOL)pLoop;
- (void)musicFadeOutWithDurationTicks:(int)pDurationTicks;

- (float)musicGetVolume;
- (void)musicSetVolume:(float)pVolume;

- (void)musicStop;

- (void)musicPause;
- (void)musicResume;


- (BOOL)musicIsPlaying;

- (void)audioPlayerDidFinishPlaying:(AVAudioPlayer *)player successfully:(BOOL)flag;

- (void)audioPlayerDecodeErrorDidOccur:(AVAudioPlayer *)player error:(NSError *)error;
- (void)audioPlayerBeginInterruption:(AVAudioPlayer *)player;
- (void)audioPlayerEndInterruption:(AVAudioPlayer *)player withFlags:(NSUInteger)flags;

@end
