//
//  AppDelegate.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "AppDelegate.h"
#import "core_app_shell.hpp"
#import <AVFoundation/AVFoundation.h>

@interface AppDelegate ()

@end

@implementation AppDelegate

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    BOOL aResult = [super application: application didFinishLaunchingWithOptions: launchOptions];
    
    return aResult;
}

- (RootViewController *)getRoot {
    return [[AdvertisingRoot alloc] init];
}

@end
