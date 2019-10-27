//
//  RootViewController.m
//  MacMetal
//
//  Created by Nicholas Raptis on 1/25/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "RootViewController.h"
#import "AppDelegate.h"
#import "MetalViewController.h"
#import "FApp.hpp"

RootViewController *gRootBase = NULL;

@interface RootViewController ()

@end

@implementation RootViewController

- (void)viewDidLoad {
    gRootBase = self;
    [super viewDidLoad];
}

- (void)setup {
    
    //self.view.frame = CGRectMake(0.0f, 0.0f, kDeviceWidth, kDeviceHeight);
    
    _metalViewController = [[MetalViewController alloc] init];
    if (_metalViewController.view == NULL) {
        [_metalViewController loadView];
    }
    
    [self.view addSubview:_metalViewController.view];
    
    //[_metalViewController loadViewIfNeeded];
    //[self.view addSubview:_metalViewController.view];
    
    //
    //...
    //
    [_metalViewController setup];
    
}

- (void)resize: (NSSize)pSize {
    self.view.frame = CGRectMake(0.0f, 0.0f, pSize.width, pSize.height);
    [_metalViewController resize: pSize];
    AppShellSetDeviceSize(round(pSize.width), round(pSize.height));
}


/*
 #pragma mark - Navigation
 
 // In a storyboard-based application, you will often want to do a little preparation before navigation
 - (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
 // Get the new view controller using [segue destinationViewController].
 // Pass the selected object to the new view controller.
 }
 */

- (void)loadView {
    self.view = [[NSView alloc] initWithFrame:NSMakeRect(0.0, 0.0, gDeviceWidth, gDeviceHeight)];
    self.view.layer = [[CALayer alloc] init];
    NSColor *aColor = [NSColor colorWithCalibratedRed: 0.0f
                                                green: 0.0f
                                                 blue: 0.0f
                                                alpha: 1.0];
    [self.view.layer setBackgroundColor: [aColor CGColor]];
}

- (BOOL)isLandscape {
    return false;
}

- (BOOL)prefersStatusBarHidden {
    return true;
}

@end
