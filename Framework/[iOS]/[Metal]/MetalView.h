//
//  MetalView.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Metal/Metal.h>
#import "ShaderTypes.h"

//#import <QuartzCore/QuartzCore.h>

@interface MetalView : UIView

@property (nonatomic, assign) CAMetalLayer * _Nonnull metalLayer;
@property (nonatomic, strong) CADisplayLink * _Nonnull displayLink;

@property (nonatomic, assign) int screenScale;

- (void)setup;

- (void)startAnimating;
- (void)stopAnimating;


@end

