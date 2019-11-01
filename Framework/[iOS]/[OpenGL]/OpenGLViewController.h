//
//  OpenGLViewController.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Metal/Metal.h>
#import "OpenGLView.h"
#import "OpenGLEngine.hpp"

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

@interface OpenGLViewController : UIViewController

@property (nonatomic, strong) OpenGLView *openGLView;

- (void)setup;

- (void)startAnimating;
- (void)stopAnimating;

@end

extern CAEAGLLayer *gOpenGLLayer;
extern OpenGLView *gOpenGLView;

