//
//  AppDelegate.h
//  MacMetal
//
//  Created by Nicholas Raptis on 1/25/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "RootViewController.h"

@interface AppDelegate : NSObject <NSApplicationDelegate, NSWindowDelegate>

@property (strong, nonatomic) IBOutlet NSWindow *window;
@property (strong, nonatomic) RootViewController *rootViewController;

@end

extern int kDeviceWidth;
extern int kDeviceHeight;
