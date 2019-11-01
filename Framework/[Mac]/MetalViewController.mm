//
//  MetalViewController.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "MetalViewController.h"
#import "AppDelegate.h"

CAMetalLayer *gMetalLayer = NULL;
MetalView *gMetalView = NULL;
MetalEngine *gMetalEngine = NULL;
MetalPipeline *gMetalPipeline = NULL;

@interface MetalViewController () {
    
}

@end

@implementation MetalViewController

- (void)setup {
    self.view.frame = CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight);
    [_metalView setup];
    
    _metalEngine = [[MetalEngine alloc] init];
    gMetalEngine = _metalEngine;
    _metalEngine.screenScale = _metalView.screenScale;
    
    _metalPipeline = [[MetalPipeline alloc] init];
    gMetalPipeline = _metalPipeline;
    _metalPipeline.screenScale = _metalView.screenScale;
    
    [_metalEngine setup];
    [_metalPipeline setup];
}

- (void)teardown {
    [_metalView teardown];
}

- (void)loadView {
    _metalView = [[MetalView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight)];
    gMetalView = _metalView;
    
    //_metalView.layer = [[CALayer alloc] init];
    self.view = _metalView;
}


- (void)resize: (NSSize)pSize {
    self.view.frame = CGRectMake(0.0f, 0.0f, pSize.width, pSize.height);
    [_metalView resize: pSize];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
}

@end
