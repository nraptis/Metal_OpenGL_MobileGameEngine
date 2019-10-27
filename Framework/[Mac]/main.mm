//
//  main.m
//  MacMetal
//
//  Created by Nicholas Raptis on 1/25/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "AppDelegate.h"
#import "GFXApp.hpp"
//#include "core_app_shell.hpp"

int main(int argc, const char * argv[]) {
    gApp = new GFXApp();
    [NSApplication sharedApplication];
    AppDelegate *appDelegate = [[AppDelegate alloc] init];
    [NSApp setDelegate: appDelegate];
    [NSApp run];
    return 0;
}
