//
//  AppDelegate.h
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "RootViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;
@property (strong, nonatomic) RootViewController *rootViewController;

@end

extern int kDeviceWidth;
extern int kDeviceHeight;
