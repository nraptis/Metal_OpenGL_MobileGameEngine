//
//  PlatformGraphicsInterface.cpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "PlatformGraphicsInterface.hpp"
#include "FApp.hpp"
#include "MetalViewController.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>

PlatformGraphicsInterface::PlatformGraphicsInterface() {
    mMetalView = NULL;
    mLastTime = 0.0f;
}

PlatformGraphicsInterface::~PlatformGraphicsInterface() {
    //CCEAGLView *glview = (CCEAGLView*) _eaglview;
    //[glview release];
}

void PlatformGraphicsInterface::Initialize() {
    CVTimeStamp aTimeStamp;
    CVDisplayLinkGetCurrentTime( gMetalView.displayLink, &aTimeStamp);
    mLastTime = aTimeStamp.videoTime;
}

float PlatformGraphicsInterface::GetScale() {
    return mScale;
}


bool PlatformGraphicsInterface::IsReady() {
    if (gMetalEngine != nil) {
        return gMetalEngine.ready;
    }
    return false;
}


void PlatformGraphicsInterface::Kill() {
    
}

void PlatformGraphicsInterface::Prerender() {
    [gMetalEngine prerender];
    [gMetalPipeline prerender];
}

void PlatformGraphicsInterface::Postrender() {
    [gMetalPipeline postrender];
    [gMetalEngine postrender];
}

void PlatformGraphicsInterface::SetContext() {
    
}

void PlatformGraphicsInterface::Commit() {
    [gMetalEngine commit];
}

