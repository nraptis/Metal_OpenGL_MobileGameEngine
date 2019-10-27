//
//  AppDelegate.m
//  MacMetal
//
//  Created by Nicholas Raptis on 1/25/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "AppDelegate.h"
#import "core_app_shell.hpp"
#include "FApp.hpp"

//int kDeviceWidth = 480;
//int kDeviceHeight = 320;

int kDeviceWidth = 1420;
int kDeviceHeight = 760;


//int kDeviceWidth = 256;
//int kDeviceHeight = 256;

@interface AppDelegate ()

@end

@implementation AppDelegate

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    
    
    float aMonitorWidth = [NSScreen mainScreen].frame.size.width;
    float aMonitorHeight = [NSScreen mainScreen].frame.size.height;
    
    //Pick the smallest screen?
    for (NSScreen *aScreen in [NSScreen screens]) {
        if (aScreen.frame.size.width < aMonitorWidth) { aMonitorWidth = aScreen.frame.size.width; }
        if (aScreen.frame.size.height < aMonitorHeight) { aMonitorHeight = aScreen.frame.size.height; }
    }
    
    kDeviceWidth = aMonitorWidth - 64;
    kDeviceHeight = aMonitorHeight - 180; // Account for the DOC...
    
    NSLog(@"Monitor Size: %d x %d\n", (int)aMonitorWidth, (int)aMonitorHeight);
    
    char aBundlePath[2048];
    getcwd(aBundlePath, sizeof(aBundlePath));
    strcat(aBundlePath, "/Assets/");
    AppShellSetDirectoryBundle(aBundlePath);
    Log("Bundle Path: %s\n", aBundlePath);
    
    char aDocPath[2048];
    getcwd(aDocPath, sizeof(aDocPath));
    strcat(aDocPath, "/Documents/");
    AppShellSetDirectoryDocuments(aDocPath);
    Log("Document Path: %s\n", aDocPath);
    
    char aExportPath[2048];
    getcwd(aExportPath, sizeof(aExportPath));
    strcat(aExportPath, "/Exports/");
    AppShellSetDirectoryExport(aExportPath);
    Log("Export Path: %s\n", aExportPath);
    
    
    AppShellInitialize(ENV_MAC);
    AppShellSetDeviceSize(kDeviceWidth, kDeviceHeight);
    AppShellSetVirtualFrame(0, 0, kDeviceWidth, kDeviceHeight);
    
    _rootViewController = [[RootViewController alloc] init];
    
    NSWindowStyleMask aWindowStyle = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;
    NSRect aWindowFrame = NSMakeRect(32.0, aMonitorHeight / 2.0 - kDeviceHeight / 2.0, kDeviceWidth, kDeviceHeight);
    
    _window = [[NSWindow alloc] initWithContentRect: aWindowFrame styleMask: aWindowStyle backing: NSBackingStoreBuffered defer: NO];
    [_window setTitle:@"App Window"];
    [_window setOpaque: YES];
    [_window setHasShadow: YES];
    [_window setDelegate: self];
    _window.contentViewController = self.rootViewController;
    
    NSColor *aColor = [NSColor colorWithCalibratedRed: 0.0f green: 0.0f blue: 0.0f alpha: 1.0];
    [_window setBackgroundColor: aColor];
    
    [_window makeKeyAndOrderFront: NSApp];
    
    if ([_rootViewController isViewLoaded] == false) {
        [_rootViewController loadView];
    };
    
    [_rootViewController setup];
    
    AppShellGraphicsSetUp();
    AppShellLoad();
}

- (void)applicationWillTerminate: (NSNotification *)aNotification {
    // Insert code here to tear down your application
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender {
    return YES;
}

- (BOOL)windowShouldClose:(NSWindow *)sender {
    
    if (gAppBase != NULL) {
        gAppBase->BaseQuit();
    }
    
    [_rootViewController.metalViewController teardown];
    
    os_sleep(220);
    return YES;
}

//- (nullable id)windowWillReturnFieldEditor:(NSWindow *)sender toObject:(nullable id)client;
- (NSSize)windowWillResize:(NSWindow *)sender toSize:(NSSize)frameSize {
    
    NSLog(@"App Resize (%f x %f)\n", frameSize.width, frameSize.height);
    
    //Bad thing to do. All textures and render pass need resize.
    
    //gAppBase->ThrottleLock();
    //[_rootViewController resize: frameSize];
    //gAppBase->ThrottleUnlock();
    
    return frameSize;
}


@end
