//
//  AdvertisingRoot.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

#import "RootViewController.h"

@interface AdvertisingRoot : RootViewController

- (void)setup;
- (BOOL)isLandscape;

- (void)active;
- (void)inactive;


@end

