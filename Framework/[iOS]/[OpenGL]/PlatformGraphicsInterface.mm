//
//  PlatformGraphicsInterface.cpp
//  Apex
//
//  Created by Nicholas Raptis on 12/14/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "PlatformGraphicsInterface.hpp"
#include "FApp.hpp"
#include "OpenGLViewController.h"
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
    Log("PlatformGraphicsInterface::Initialize()");
    
    //mLastTime = gOpenGLView.displayLink.timestamp;
    mLastTime = CACurrentMediaTime();
}

float PlatformGraphicsInterface::GetScale() {
    return mScale;
}

bool PlatformGraphicsInterface::IsReady() {
    if (gOpenGLEngine != NULL) {
        return true;
    }
    return false;
}


void PlatformGraphicsInterface::Kill() {
    
    Log("PlatformGraphicsInterface::Kill()");
    
    
    //[CCDirectorCaller destroy];
    // destroy EAGLView
    //CCEAGLView *eaglview = (CCEAGLView*) _eaglview;
    //[eaglview removeFromSuperview];
    //[eaglview release];
    //release();
}

void PlatformGraphicsInterface::Prerender() {
    if (gOpenGLEngine) {
        gOpenGLEngine->Prerender();
    }
    
    [gOpenGLView setFramebuffer];
    //[gMetalEngine prerender];
}


void PlatformGraphicsInterface::Postrender() {
    if (gOpenGLEngine) {
        gOpenGLEngine->Postrender();
    }
    
    [gOpenGLView presentFramebuffer];
}

//bool PlatformGraphicsInterface::IsVSyncReady() {
//    
//    //usleep(90000);
//    double aTime = CACurrentMediaTime() * 60.0f;
//    double aLinkTime = mLastTime * 60.0f;
//    double aDiff = (aTime - aLinkTime);
//    //Log("---Time[%f] LinkTime[%f]  (%f)\n", aTime, aLinkTime, aDiff);
//    
//    int aFudge = 0;
//    while (aDiff < 1.0f && aFudge < 2000) {
//        usleep(200);
//        aTime = CACurrentMediaTime() * 60.0f;
//        aDiff = (aTime - aLinkTime);
//        //Log(">Time[%f] LinkTime[%f]  (%f)\n", aTime, aLinkTime, aDiff);
//        aFudge++;
//    }
//    if (aFudge > 1) {
//        //Log("Sleeps[%d]\n", aFudge);
//    }
//    
//    
//    mLastTime = CACurrentMediaTime();
//    
//    return true;
//    
//    /*
//    //usleep(90000);
//    
//    double aTimeStamp = CACurrentMediaTime();
//    double aFrameTime = (aTimeStamp - mLastTime) * 1000.0f;
//    
//    
//    static int aOutOut = 0;
//    
//    aOutOut++;
//    if (aOutOut >= 60) {
//        aOutOut = 0;
//        Log("aFrameTime = %f\n", aFrameTime);
//    }
//    
//    if (aFrameTime > 16.7) {
//        //Log("VSync is redy\n");
//        mLastTime = gMetalView.displayLink.timestamp;
//        return true;
//    } else {
//        //Log("VSync is NOT redy\n");
//    }
//
//    
//    return false;
//    */
//}

void PlatformGraphicsInterface::SetContext() {
    [gOpenGLView setContext];
    
}

void PlatformGraphicsInterface::Commit() {
    
    [gOpenGLView commit];
    
    //[gMetalEngine commit];
}

