//
//  AdvertisingRoot.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

//HOOK:
#define METAL_MODE 1
#undef METAL_MODE

#import "AdvertisingRoot.h"
#import "AppDelegate.h"
#import "FApp.hpp"

@interface AdvertisingRoot()

@end

@implementation AdvertisingRoot

- (void)viewDidLoad {
    
    [super viewDidLoad];
}

- (void)setup {
    [super setup];
}

- (BOOL)isLandscape {
    return false;
}

- (BOOL)prefersStatusBarHidden {
    return true;
}

- (void) active {
    [super active];
}

- (void) inactive {
    [super inactive];
}

@end
