//
//  RootViewController.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

//HOOK:
#define METAL_MODE 1
//#undef METAL_MODE

#import "RootViewController.h"
#import "AppDelegate.h"

#ifdef METAL_MODE
#import "MetalViewController.h"
#else
#import "OpenGLViewController.h"
#endif

#import "FApp.hpp"

RootViewController *gRootBase = NULL;

@interface RootViewController ()

#ifdef METAL_MODE
@property (nonatomic, strong) MetalViewController *metalViewController;
#else
@property (nonatomic, strong) OpenGLViewController *openGLViewController;
#endif

@property (nonatomic, assign) float screenScale;

@end

@implementation RootViewController

- (void)viewDidLoad {
    
    gRootBase = self;
    
    [super viewDidLoad];
    
    self.view.opaque = true;
    self.view.backgroundColor = [UIColor blackColor];
    
    self.screenScale = [UIScreen mainScreen].scale;
}


- (void)setup {
    
    self.view.frame = CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight);
    
#ifdef METAL_MODE
    _metalViewController = [[MetalViewController alloc] init];
    [self.view addSubview:_metalViewController.view];
    [_metalViewController loadViewIfNeeded];
    [_metalViewController setup];
#else
    _openGLViewController = [[OpenGLViewController alloc] init];
    [self.view addSubview:_openGLViewController.view];
    [_openGLViewController loadViewIfNeeded];
    [_openGLViewController setup];
#endif
    
}

- (BOOL)isLandscape {
    return false;
}

- (BOOL)prefersStatusBarHidden {
    return true;
}

- (void) active {
#ifdef METAL_MODE
    [gMetalView startAnimating];
#else
    //[gOpenGLView active];
    [_openGLViewController startAnimating];
#endif
}

- (void) inactive {
#ifdef METAL_MODE
    [gMetalView stopAnimating];
#else
    //[gOpenGLView inactive];
    [_openGLViewController stopAnimating];
#endif
}

- (float) getScreenScale {
    
    float aScale = self.screenScale;
    
    if (gDeviceWidth > 1023.0f || gDeviceHeight > 1023.0f) {
        //For iPad, we scale by 2...
        aScale *= 2.0f;
    }
    
    if (aScale < 1.0f) { aScale = 1.0f; }
    if (aScale > 4.0f) { aScale = 4.0f; }
    
    return aScale;
}

@end
