//
//  OpenGLView.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <UIKit/UIKit.h>

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

@interface OpenGLView : UIView

@property (nonatomic, strong) CAEAGLLayer * _Nonnull eaglLayer;
//@property (nonatomic, strong) EAGLContext * _Nonnull context;

//@property (nonatomic, assign) CAMetalLayer * _Nonnull metalLayer;
@property (nonatomic, strong) CADisplayLink * _Nonnull displayLink;

@property (nonatomic, assign) int screenScale;

- (void)setup;
- (void)setContext;
- (void)commit;

- (void)setFramebuffer;
- (BOOL)presentFramebuffer;

- (void)active;
- (void)inactive;



@end

