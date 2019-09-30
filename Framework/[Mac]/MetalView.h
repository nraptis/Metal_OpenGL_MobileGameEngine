//
//  MetalView.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#import "ShaderTypes.h"



@interface MetalView : NSView

@property (nonatomic, assign) CAMetalLayer * _Nonnull metalLayer;
@property (nonatomic) CVDisplayLinkRef _Nonnull displayLink;

@property (nonatomic, assign) int screenScale;

- (void)setup;
- (void)teardown;

- (void)resize: (NSSize)pSize;

- (int)convertKey:(unichar)keycode;

- (CGPoint)correctMousePos: (CGPoint)pos;

@end

