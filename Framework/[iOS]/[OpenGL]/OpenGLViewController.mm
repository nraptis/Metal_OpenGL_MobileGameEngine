//
//  OpenGLViewController.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "OpenGLViewController.h"
#import "AppDelegate.h"

CAEAGLLayer *gOpenGLLayer = NULL;
OpenGLView *gOpenGLView = NULL;


@interface OpenGLViewController ()
{
    
}

@end

@implementation OpenGLViewController

- (void)setup {
    [self loadViewIfNeeded];
    self.view.frame = CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight);
    [_openGLView setup];
    
    gOpenGLEngine = new OpenGLEngine();
    [_openGLView setContext];
    [_openGLView active];
    
}

- (void)loadView {
    _openGLView = [[OpenGLView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight)];
    gOpenGLView = _openGLView;
    _openGLView.backgroundColor = [UIColor blackColor];
    _openGLView.opaque = true;
    self.view = _openGLView;
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)startAnimating {
    [_openGLView active];
}

- (void)stopAnimating {
    [_openGLView inactive];
}


@end
