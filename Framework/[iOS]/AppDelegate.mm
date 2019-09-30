//
//  AppDelegate.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

#import "AppDelegate.h"
#import "core_app_shell.hpp"


//Needed for metal:

//1.) MTLDevice
//2.) CAMetalLayer
//3.) Vertex Buffer
//4.) Vertex Shader
//5.) Fragment Shader
//6.) Render Pipeline
//7.) Command Queue ?

int kDeviceWidth = 320;
int kDeviceHeight = 320;

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    
    
    float aOSVersion = [[[UIDevice currentDevice] systemVersion] floatValue];
    //bool aIsTablet = false;
    
    kDeviceWidth = [UIScreen mainScreen].bounds.size.width + 0.5f;
    kDeviceHeight = [UIScreen mainScreen].bounds.size.height + 0.5f;
    //
    //
    AppShellSetDeviceSize(kDeviceWidth, kDeviceHeight);
    
    
    if (kDeviceWidth > 700) {
        //AppShellSetVirtualFrame(70, 70, kDeviceWidth - 140, kDeviceHeight - 140);
        //AppShellSetVirtualFrame(0, 0, kDeviceWidth, kDeviceHeight);
        
    } else {
        //AppShellSetVirtualFrame(20, 40, kDeviceWidth - 50, kDeviceHeight - 110);
        //AppShellSetVirtualFrame(0, 0, kDeviceWidth, kDeviceHeight);
    }
    
    //
    ///////////////
    //
    
    char aBundlePath[2048];
    memset(aBundlePath, 0, sizeof(aBundlePath));
    CFURLRef aResourceURL = CFBundleCopyBundleURL(CFBundleGetMainBundle());
    CFStringRef aStringRef = CFURLCopyFileSystemPath(aResourceURL, kCFURLPOSIXPathStyle);
    CFRelease(aResourceURL);
    CFStringGetCString(aStringRef, aBundlePath, 2048, kCFStringEncodingASCII);
    CFRelease(aStringRef);
    strcat(aBundlePath, "/");
    AppShellSetDirectoryBundle(aBundlePath);
    //
    //
    //
    NSArray *aPathArray = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask,YES);
    NSString *aDocumentDirectory = [aPathArray objectAtIndex:0];
    char aDocPath[2048];
    memset(aDocPath, 0, sizeof(aDocPath));
    const char *aDocPtr = [aDocumentDirectory UTF8String];
    int i=0;
    while (*aDocPtr != 0) {
        aDocPath[i] = *aDocPtr;
        ++aDocPtr;
        i++;
    }
    aDocPath[i] = '/';
    AppShellSetDirectoryDocuments(aDocPath);
    
    
    if ([_rootViewController isLandscape]) {
        int aHold = kDeviceWidth;
        kDeviceWidth = kDeviceHeight;
        kDeviceHeight = aHold;
    }
    
    _window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    
    if (@available(iOS 11.0, *)) {
        AppShellSetSafeAreaInsets(_window.safeAreaInsets.top, _window.safeAreaInsets.right, _window.safeAreaInsets.bottom, _window.safeAreaInsets.left);
    } else {
        // Fallback on earlier versions
        AppShellSetSafeAreaInsets(0.0f, 0.0f, 0.0f, 0.0f);
    }
    
    
    
    AppShellInitialize(ENV_IOS);
    
    
    
    //AppShellSetImageFileScale(2);
    
    _rootViewController = [[RootViewController alloc] init];
    _window.rootViewController = _rootViewController;
    [_window makeKeyAndVisible];
    
    
    //
    
    //
    //AppShellSetDeviceSize(aAppWidth, aAppHeight);
    //AppShellSetVirtualFrame(0, 0, aAppWidth, aAppHeight);
    
    //AppShellSetDirectoryBundle(aPathBundle.c());
    //AppShellSetDirectoryDocuments(aPathDocuments.c());
    //AppShellSetOSVersion(gOSVersion);
    //AppShellSetAdBannerHeight(0.0f);
    
    
    
    // ...
    
    [_rootViewController loadViewIfNeeded];
    
    // ...
    
    [_rootViewController setup];
    
    AppShellLoad();
    
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
    [_rootViewController inactive];
    AppShellPause();
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    [_rootViewController inactive];
    AppShellPause();
}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
    AppShellResume();
    
    [_rootViewController active];
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
    AppShellResume();
    
    [_rootViewController active];
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    [_rootViewController inactive];
    AppShellPause();
    AppShellExit();
    
}

@end
