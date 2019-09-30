//
//  main.m
//  MetalLearning
//
//  Created by Nicholas Raptis on 1/17/19.
//  Copyright © 2019 Nicholas Raptis. All rights reserved.
//

//#import <UIKit/UIKit.h>
#import "AppDelegate.h"
#import "GFXApp.hpp"

int main(int argc, char * argv[]) {
    @autoreleasepool {
        gApp = new GFXApp();
        int aResult = UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
        return aResult;
    }
}

