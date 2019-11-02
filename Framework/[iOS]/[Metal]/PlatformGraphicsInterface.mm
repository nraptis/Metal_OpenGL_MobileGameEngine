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
#import <UIKit/UIKit.h>

PlatformGraphicsInterface::PlatformGraphicsInterface() {
    mLastTime = 0.0f;
}

PlatformGraphicsInterface::~PlatformGraphicsInterface()
{
    //CCEAGLView *glview = (CCEAGLView*) _eaglview;
    //[glview release];
}

void PlatformGraphicsInterface::Initialize() {
    mLastTime = gMetalView.displayLink.timestamp;
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
    //[CCDirectorCaller destroy];
    // destroy EAGLView
    //CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    //[eaglview removeFromSuperview];
    //[eaglview release];
    //release();
}

void PlatformGraphicsInterface::Prerender() {
    
    [gMetalEngine prerender];
}


void PlatformGraphicsInterface::Postrender() {
    //[glView presentFramebuffer];
    
    [gMetalEngine postrender];
}
/*
bool PlatformGraphicsInterface::IsVSyncReady() {
    
    return true;
    
    
    //usleep(90000);
    
    double aTimeStamp = CACurrentMediaTime();
    double aFrameTime = (aTimeStamp - mLastTime) * 1000.0f;
    
    
    static int aOutOut = 0;
    
    aOutOut++;
    if (aOutOut >= 60) {
        aOutOut = 0;
        Log("aFrameTime = %f\n", aFrameTime);
    }
    
    if (aFrameTime > 16.7) {
        //Log("VSync is redy\n");
        mLastTime = gMetalView.displayLink.timestamp;
        return true;
    } else {
        //Log("VSync is NOT redy\n");
    }

    
    return false;
 
}
 */

void PlatformGraphicsInterface::SetContext() {
    
}


void PlatformGraphicsInterface::Commit() {
    [gMetalEngine commit];
}

