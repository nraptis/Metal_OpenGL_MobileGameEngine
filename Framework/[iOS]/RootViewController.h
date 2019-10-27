//
//  RootViewController.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

//#import <Metal/Metal.h>
//#import "MetalViewController.h"

NS_ASSUME_NONNULL_BEGIN

@interface RootViewController : UIViewController

- (void)setup;
- (BOOL)isLandscape;

- (void) active;
- (void) inactive;

- (float) getScreenScale;

@end

NS_ASSUME_NONNULL_END

extern RootViewController * _Nullable gRootBase;


